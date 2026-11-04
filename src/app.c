/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "app_mqtt_task.h"
#include "app_audio.h"
#include "app_lan9370_spi.h"
#include "app_lan9370_commands.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

static APP_DATA appData;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* Hardware reset of the LAN9370 (active-low nRST on PC18).
   Done from APP_Initialize(), i.e. before the first SYS_Tasks() pass where the
   PHY driver starts probing, and while interrupts are still disabled (so the
   SYS_TIME delays cannot be used). A DWT cycle counter busy-wait is used instead.
*/
#define APP_SWITCH_RESET_PIN            PORT_PIN_PC18
#define APP_SWITCH_RESET_ASSERT_MS      10U     // nRST held low
#define APP_SWITCH_RESET_RECOVERY_MS    150U    // wait after release before SMI access

/* Port 5 (host RMII) PORT_XMII_CTL1 register, bit 2 ("MII / RMII Modes").
   For RMII, this bit selects which side generates the shared 50 MHz
   REFCLK: 1 = REFCLK is received at the RXC pin, 0 = REFCLK is generated
   from the TXC pin. The LAN9370 defaults to 1 (clock receiver), but the
   SAM E54 Curiosity Ultra's Ethernet PHY header is hardware-wired to also
   receive REFCLK (see its user guide, pin 24: "REFCLK (in)") -- with both
   sides configured as receivers, no 50 MHz RMII reference clock was ever
   actually driven onto the shared line, which silently broke RMII receive
   framing on both ends while leaving transmit mostly unaffected. Clearing
   this bit makes the LAN9370 generate and drive the clock instead. */
#define APP_LAN9370_PORT5_XMII_CTL1_REG             0x5301U
#define APP_LAN9370_PORT5_XMII_CTL1_RMII_CLK_IN_BIT 0x04U

static void APP_DelayMs(uint32_t ms)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = ms * (SYS_TIME_CPU_CLOCK_FREQUENCY / 1000U);

    while((uint32_t)(DWT->CYCCNT - start) < ticks)
    {
    }
}

static void APP_SwitchReset(void)
{
    PORT_PinClear(APP_SWITCH_RESET_PIN);            // drive low before enabling the output
    PORT_PinOutputEnable(APP_SWITCH_RESET_PIN);
    APP_DelayMs(APP_SWITCH_RESET_ASSERT_MS);

    PORT_PinSet(APP_SWITCH_RESET_PIN);              // release reset
    APP_DelayMs(APP_SWITCH_RESET_RECOVERY_MS);
}

/* One-shot SMI/MDIO scan of PHY addresses 0-31 (reads PHYID1, register 2).
   An address answering with anything other than 0xFFFF is reported on the
   console. Non-blocking: advances one step per call.
*/
#define APP_PHY_SCAN_FIRST_ADDR     0U
#define APP_PHY_SCAN_LAST_ADDR      31U
#define APP_PHY_SCAN_REG_PHYID1     2U

static void APP_PhyScanTask(void)
{
    static DRV_HANDLE                   hMiim;
    static DRV_MIIM_OPERATION_HANDLE    hOp;
    static uint8_t                      scanState = 0;
    static uint8_t                      addr = APP_PHY_SCAN_FIRST_ADDR;
    static uint8_t                      nFound = 0;
    DRV_MIIM_RESULT                     res;
    DRV_MIIM_SETUP                      miimSetup;
    uint32_t                            data;

    switch(scanState)
    {
        case 0:     // open the MIIM driver and set the SMI clock
            hMiim = DRV_MIIM_Open(DRV_MIIM_DRIVER_INDEX_0, DRV_IO_INTENT_SHARED);
            if(hMiim == DRV_HANDLE_INVALID)
            {
                SYS_CONSOLE_MESSAGE("PHY scan: MIIM open failed\r\n");
                scanState = 3;
                break;
            }

            miimSetup.hostClockFreq = (uint32_t)TCPIP_INTMAC_PERIPHERAL_CLK;
            miimSetup.maxBusFreq = 2000000;
            miimSetup.setupFlags = DRV_MIIM_SETUP_FLAG_NONE;
            if(DRV_MIIM_Setup(hMiim, &miimSetup) < 0)
            {
                SYS_CONSOLE_MESSAGE("PHY scan: MIIM setup failed\r\n");
                DRV_MIIM_Close(hMiim);
                scanState = 3;
                break;
            }
            scanState = 1;
            break;

        case 1:     // start the read for the current address
            hOp = DRV_MIIM_Read(hMiim, APP_PHY_SCAN_REG_PHYID1, addr, DRV_MIIM_OPERATION_FLAG_NONE, &res);
            if(res == DRV_MIIM_RES_OK)
            {
                scanState = 2;
            }
            else if(res < 0)
            {
                SYS_CONSOLE_PRINT("PHY scan: read start failed at address %u: %d\r\n", addr, res);
                DRV_MIIM_Close(hMiim);
                scanState = 3;
            }
            break;      // else busy: retry next call

        case 2:     // wait for the read to complete
            res = DRV_MIIM_OperationResult(hMiim, hOp, &data);
            if(res == DRV_MIIM_RES_PENDING)
            {
                break;
            }

            if(res == DRV_MIIM_RES_OK && (data & 0xFFFFU) != 0xFFFFU)
            {
                nFound++;
                SYS_CONSOLE_PRINT("PHY scan: address %u responded, PHYID1 = 0x%04X\r\n", addr, (unsigned int)(data & 0xFFFFU));
            }
            else if(res != DRV_MIIM_RES_OK)
            {
                SYS_CONSOLE_PRINT("PHY scan: address %u read error: %d\r\n", addr, res);
            }

            if(++addr > APP_PHY_SCAN_LAST_ADDR)
            {
                SYS_CONSOLE_PRINT("PHY scan done (addresses %u-%u): %u responded\r\n",
                        APP_PHY_SCAN_FIRST_ADDR, APP_PHY_SCAN_LAST_ADDR, nFound);
                DRV_MIIM_Close(hMiim);
                scanState = 3;
            }
            else
            {
                scanState = 1;
            }
            break;

        default:    // done
            break;
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void )
{
    /* Reset the LAN9370 so it is ready before the PHY driver probes it */
    APP_SwitchReset();

    /* Set up the LAN9370 SPI register access helper and the "reg" console
       command group used to manually read/write/modify its registers. */
    SERCOM0_SPI_Initialize();
    APP_LAN9370_SPI_Initialize();
    APP_LAN9370_CommandsInit();

    /* Fix the RMII clock direction on port 5 -- see the register comment
       above for why this is needed. */
    (void) APP_LAN9370_RegModify(APP_LAN9370_PORT5_XMII_CTL1_REG,
                                  APP_LAN9370_PORT5_XMII_CTL1_RMII_CLK_IN_BIT, 0x00U);

    /* Place the application state machine in its initial state. */
    appData.state = APP_TCPIP_WAIT_INIT;

    /* Initialize audio subsystem for ML keyword spotting */
    APP_AUDIO_Initialize();
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    SYS_STATUS          tcpipStat;
    TCPIP_NET_HANDLE    netH;
    int                 nNets;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int                 i;
    const char          *netName, *netBiosName;

    /* One-shot PHY address scan (see APP_PhyScanTask) */
    APP_PhyScanTask();

    /* Run audio task for ML keyword spotting */
    APP_AUDIO_Tasks();

    switch(appData.state)
    {
        case APP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                SYS_CONSOLE_MESSAGE("APP: TCP/IP stack initialization failed!\r\n");
                appData.state = APP_TCPIP_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                appData.state = APP_TCPIP_READY;
            }

            break;

        case APP_TCPIP_READY:
            // now that the stack is ready we can check the
            // available interfaces and register
            // a Bonjour service

            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for(i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                netName = TCPIP_STACK_NetNameGet(netH);
                netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
                SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
                SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif // defined(TCPIP_STACK_USE_NBNS)
                (void)netName;          // avoid compiler warning 
                (void)netBiosName;      // if SYS_CONSOLE_PRINT is null macro

            }
            appData.state = APP_TCPIP_WAIT_FOR_IP;
            break;

        case APP_TCPIP_WAIT_FOR_IP:

            // wait for the interfaces to be ready
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                if(!TCPIP_STACK_NetIsReady(netH))
                {
                    return;    // interface not ready yet!
                }
            }

            // initialize the MQTT example application
            if(!APP_MQTT_Init())
            {
                appData.state = APP_TCPIP_ERROR;
                break;
            }

            appData.state = APP_TCPIP_TRANSACT;
            break;

        case APP_TCPIP_TRANSACT:
            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for(i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;
                    SYS_CONSOLE_PRINT("%s IP Address: %d.%d.%d.%d \r\n",
                            TCPIP_STACK_NetNameGet(netH),
                            ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                }
            }

            
            // advance the MQTT demo state machine
            APP_MQTT_Task();
            break;

        default:
            break;
    }
}


/*******************************************************************************
 End of File
 */
