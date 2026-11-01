/*******************************************************************************
  LAN9370 SPI Register Access Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_lan9370_spi.c

  Summary:
    Byte-wide register read/write/modify helpers for the LAN9370 switch over
    the SERCOM0 SPI master.

  Description:
    See app_lan9370_spi.h. The 4-byte SPI command word format (3-bit opcode,
    24-bit address, 5-bit turnaround) matches the framing used by Microchip's
    reference LAN937x SPI driver (spi_driver.c, spi_read()/spi_write()):
        cmd = (addr << 5) | opcode, opcode in bits [31:29], MSB-first on the wire.
*******************************************************************************/

#include "app_lan9370_spi.h"
#include "definitions.h"

#define LAN9370_CS_PIN              PORT_PIN_PA27

#define LAN9370_SPI_OPCODE_WRITE    (2UL << 29)
#define LAN9370_SPI_OPCODE_READ     (3UL << 29)
#define LAN9370_SPI_OPCODE_MASK     (7UL << 29)
#define LAN9370_SPI_ADDR_SHIFT      5U

static void APP_LAN9370_BuildCmd(uint8_t *cmdBuf, uint16_t addr, uint32_t opcode)
{
    uint32_t cmd = ((uint32_t)addr << LAN9370_SPI_ADDR_SHIFT);

    cmd = (cmd & ~LAN9370_SPI_OPCODE_MASK) | opcode;

    /* MSB-first on the wire. */
    cmdBuf[0] = (uint8_t)(cmd >> 24);
    cmdBuf[1] = (uint8_t)(cmd >> 16);
    cmdBuf[2] = (uint8_t)(cmd >> 8);
    cmdBuf[3] = (uint8_t)(cmd >> 0);
}

void APP_LAN9370_SPI_Initialize(void)
{
    SERCOM_SPI_TRANSFER_SETUP spiSetup;

    PORT_PinSet(LAN9370_CS_PIN);              /* idle high before enabling the output */
    PORT_PinOutputEnable(LAN9370_CS_PIN);

    spiSetup.clockFrequency = 1000000UL;      /* 1 MHz, well within LAN9370 SPI limits */
    spiSetup.clockPhase     = SERCOM_SPI_CLOCK_PHASE_LEADING_EDGE;
    spiSetup.clockPolarity  = SERCOM_SPI_CLOCK_POLARITY_IDLE_LOW;    /* SPI mode 0, matching Microchip's reference LAN937x firmware (CONF_SPI_0_CPOL=0, CPHA=0) */
    spiSetup.dataBitsOrder  = SERCOM_SPI_DATA_BITS_ORDER_MSB_FIRST;

    (void) SERCOM0_SPI_TransferSetup(&spiSetup, 0U);
}

bool APP_LAN9370_RegRead(uint16_t addr, uint8_t *val)
{
    uint8_t cmdBuf[4];
    uint8_t rxBuf[4];
    bool    success;

    APP_LAN9370_BuildCmd(cmdBuf, addr, LAN9370_SPI_OPCODE_READ);

    PORT_PinClear(LAN9370_CS_PIN);
    success = SERCOM0_SPI_Write(cmdBuf, sizeof(cmdBuf));
    if(success)
    {
        success = SERCOM0_SPI_Read(rxBuf, 1U);
    }
    PORT_PinSet(LAN9370_CS_PIN);

    if(success)
    {
        *val = rxBuf[0];
    }

    return success;
}

bool APP_LAN9370_RegWrite(uint16_t addr, uint8_t val)
{
    uint8_t cmdBuf[5];
    bool    success;

    APP_LAN9370_BuildCmd(cmdBuf, addr, LAN9370_SPI_OPCODE_WRITE);
    cmdBuf[4] = val;

    PORT_PinClear(LAN9370_CS_PIN);
    success = SERCOM0_SPI_Write(cmdBuf, sizeof(cmdBuf));
    PORT_PinSet(LAN9370_CS_PIN);

    return success;
}

bool APP_LAN9370_RegModify(uint16_t addr, uint8_t mask, uint8_t val)
{
    uint8_t regval;

    if(!APP_LAN9370_RegRead(addr, &regval))
    {
        return false;
    }

    regval = (uint8_t)((regval & ~mask) | (val & mask));

    return APP_LAN9370_RegWrite(addr, regval);
}

bool APP_LAN9370_RegReadWord(uint16_t addr, uint16_t *val)
{
    uint8_t cmdBuf[4];
    uint8_t rxBuf[2];
    bool    success;

    APP_LAN9370_BuildCmd(cmdBuf, addr, LAN9370_SPI_OPCODE_READ);

    PORT_PinClear(LAN9370_CS_PIN);
    success = SERCOM0_SPI_Write(cmdBuf, sizeof(cmdBuf));
    if(success)
    {
        success = SERCOM0_SPI_Read(rxBuf, sizeof(rxBuf));
    }
    PORT_PinSet(LAN9370_CS_PIN);

    if(success)
    {
        *val = ((uint16_t)rxBuf[0] << 8) | rxBuf[1];
    }

    return success;
}

bool APP_LAN9370_RegWriteWord(uint16_t addr, uint16_t val)
{
    uint8_t cmdBuf[6];
    bool    success;

    APP_LAN9370_BuildCmd(cmdBuf, addr, LAN9370_SPI_OPCODE_WRITE);
    cmdBuf[4] = (uint8_t)(val >> 8);
    cmdBuf[5] = (uint8_t)(val >> 0);

    PORT_PinClear(LAN9370_CS_PIN);
    success = SERCOM0_SPI_Write(cmdBuf, sizeof(cmdBuf));
    PORT_PinSet(LAN9370_CS_PIN);

    return success;
}

bool APP_LAN9370_RegModifyWord(uint16_t addr, uint16_t mask, uint16_t val)
{
    uint16_t regval;

    if(!APP_LAN9370_RegReadWord(addr, &regval))
    {
        return false;
    }

    regval = (uint16_t)((regval & ~mask) | (val & mask));

    return APP_LAN9370_RegWriteWord(addr, regval);
}
