/*******************************************************************************
  SERCOM Serial Peripheral Interface(SPI) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_sercom0_spi_master.c

  Summary
    SPI peripheral library interface.

  Description
    This file defines the interface to the SPI peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.
*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "plib_sercom0_spi_master.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/* SERCOM0 SPI baud value for 500000 Hz baud rate */
#define SERCOM0_SPI_INT_BAUD_VALUE            (119U)

static volatile bool sercom0SPIBusyStatus = false;

// *****************************************************************************
// *****************************************************************************
// Section: SERCOM0 SPI Interface Routines
// *****************************************************************************
// *****************************************************************************

void SERCOM0_SPI_Initialize(void)
{
    /* Reset the module */
    SERCOM0_REGS->SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_SWRST_Msk;

    /* Wait for synchronization */
    while((SERCOM0_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    /*
     * Configures Data Out Pinout  : DOPO - PB24(PAD0) is DO, PB25(PAD1) is SCK
     * Configures Data In Pinout   : DIPO - PC25(PAD3) is DI
     * Configures Standby Mode
     * Configures Clock Phase, Polarity and Data Order
     */
    SERCOM0_REGS->SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_MODE_SPI_MASTER
                                     | SERCOM_SPIM_CTRLA_DOPO_PAD0
                                     | SERCOM_SPIM_CTRLA_DIPO_PAD3
                                     | SERCOM_SPIM_CTRLA_FORM_SPI_FRAME
                                     | SERCOM_SPIM_CTRLA_CPHA_LEADING_EDGE
                                     | SERCOM_SPIM_CTRLA_CPOL_IDLE_LOW
                                     | SERCOM_SPIM_CTRLA_DORD_MSB;

    /* Configure Baud Rate */
    SERCOM0_REGS->SPIM.SERCOM_BAUD = (uint8_t)SERCOM_SPIM_BAUD_BAUD(SERCOM0_SPI_INT_BAUD_VALUE);

    /*
     * Configures RXEN
     */
    SERCOM0_REGS->SPIM.SERCOM_CTRLB = SERCOM_SPIM_CTRLB_RXEN_Msk | SERCOM_SPIM_CTRLB_CHSIZE(0UL);

    /* Wait for sync */
    while((SERCOM0_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    /* Enable the SPI after the configurations */
    SERCOM0_REGS->SPIM.SERCOM_CTRLA |= SERCOM_SPIM_CTRLA_ENABLE_Msk;

    /* Wait for sync */
    while((SERCOM0_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    sercom0SPIBusyStatus = false;
}

static uint32_t SERCOM0_SPI_CalculateBaudValue(uint32_t spiSourceClock, uint32_t spiClock)
{
    return (uint32_t)(((spiSourceClock / (2U * spiClock))) - 1U);
}

bool SERCOM0_SPI_TransferSetup(SERCOM_SPI_TRANSFER_SETUP* setup, uint32_t spiSourceClock)
{
    uint32_t baudValue;

    if(setup == NULL)
    {
        return false;
    }

    if(spiSourceClock == 0U)
    {
        spiSourceClock = 120000000UL;
    }

    baudValue = SERCOM0_SPI_CalculateBaudValue(spiSourceClock, setup->clockFrequency);

    /* Disable the SPI before configurations */
    SERCOM0_REGS->SPIM.SERCOM_CTRLA &= ~SERCOM_SPIM_CTRLA_ENABLE_Msk;

    /* Wait for sync */
    while((SERCOM0_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    SERCOM0_REGS->SPIM.SERCOM_CTRLA = (SERCOM0_REGS->SPIM.SERCOM_CTRLA
                                        & ~(SERCOM_SPIM_CTRLA_CPHA_Msk | SERCOM_SPIM_CTRLA_CPOL_Msk | SERCOM_SPIM_CTRLA_DORD_Msk))
                                        | SERCOM_SPIM_CTRLA_CPHA((uint32_t)setup->clockPhase)
                                        | SERCOM_SPIM_CTRLA_CPOL((uint32_t)setup->clockPolarity)
                                        | SERCOM_SPIM_CTRLA_DORD((uint32_t)setup->dataBitsOrder);

    SERCOM0_REGS->SPIM.SERCOM_BAUD = (uint8_t)SERCOM_SPIM_BAUD_BAUD(baudValue);

    /* Re-enable the SPI after configurations */
    SERCOM0_REGS->SPIM.SERCOM_CTRLA |= SERCOM_SPIM_CTRLA_ENABLE_Msk;

    /* Wait for sync */
    while((SERCOM0_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    return true;
}

bool SERCOM0_SPI_WriteRead(void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize)
{
    uint8_t* pTxBuffer = (uint8_t*)pTransmitData;
    uint8_t* pRxBuffer = (uint8_t*)pReceiveData;
    size_t txCount = 0U;
    size_t rxCount = 0U;
    size_t dummySize = (txSize > rxSize) ? txSize : rxSize;
    bool isSuccess = false;

    if(sercom0SPIBusyStatus == false)
    {
        sercom0SPIBusyStatus = true;

        while((txCount < dummySize) || (rxCount < dummySize))
        {
            if((txCount < dummySize) && ((SERCOM0_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk) != 0U))
            {
                uint8_t wrByte = (txCount < txSize) ? pTxBuffer[txCount] : 0xFFU;

                SERCOM0_REGS->SPIM.SERCOM_DATA = wrByte;

                txCount++;
            }

            if((rxCount < dummySize) && ((SERCOM0_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_RXC_Msk) != 0U))
            {
                uint8_t rdByte = (uint8_t)SERCOM0_REGS->SPIM.SERCOM_DATA;

                if(rxCount < rxSize)
                {
                    pRxBuffer[rxCount] = rdByte;
                }

                rxCount++;
            }
        }

        sercom0SPIBusyStatus = false;

        isSuccess = true;
    }

    return isSuccess;
}

bool SERCOM0_SPI_Write(void* pTransmitData, size_t txSize)
{
    return SERCOM0_SPI_WriteRead(pTransmitData, txSize, NULL, 0U);
}

bool SERCOM0_SPI_Read(void* pReceiveData, size_t rxSize)
{
    return SERCOM0_SPI_WriteRead(NULL, 0U, pReceiveData, rxSize);
}

bool SERCOM0_SPI_IsBusy(void)
{
    return sercom0SPIBusyStatus;
}
