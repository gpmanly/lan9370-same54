/*******************************************************************************
  Serial Communication Interface Serial Peripheral Interface (SERCOM SPI) Library
  Instance Header File

  Company
    Microchip Technology Inc.

  File Name
    plib_sercom_spi_master_common.h

  Summary
    SERCOM SPI peripheral library interface.

  Description
    This file defines the interface to the SERCOM SPI peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:

*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef PLIB_SERCOM_SPI_MASTER_COMMON_H
#define PLIB_SERCOM_SPI_MASTER_COMMON_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* SERCOM SPI Clock Phase

  Summary:
    Identifies the SPI clock phase.

  Description:
    This enumeration identifies the SPI clock phase.

  Remarks:
    None.
*/

typedef enum
{
    SERCOM_SPI_CLOCK_PHASE_LEADING_EDGE = 0,

    SERCOM_SPI_CLOCK_PHASE_TRAILING_EDGE,

} SERCOM_SPI_CLOCK_PHASE;

// *****************************************************************************
/* SERCOM SPI Clock Polarity

  Summary:
    Identifies the SPI clock polarity.

  Description:
    This enumeration identifies the SPI clock polarity.

  Remarks:
    None.
*/

typedef enum
{
    SERCOM_SPI_CLOCK_POLARITY_IDLE_LOW = 0,

    SERCOM_SPI_CLOCK_POLARITY_IDLE_HIGH,

} SERCOM_SPI_CLOCK_POLARITY;

// *****************************************************************************
/* SERCOM SPI Data Bit Order

  Summary:
    Identifies the SPI data bit order.

  Description:
    This enumeration identifies the SPI data bit order.

  Remarks:
    None.
*/

typedef enum
{
    SERCOM_SPI_DATA_BITS_ORDER_MSB_FIRST = 0,

    SERCOM_SPI_DATA_BITS_ORDER_LSB_FIRST,

} SERCOM_SPI_DATA_BITS_ORDER;

// *****************************************************************************
/* Transaction Request Block

  Summary:
    Transaction Request Block Structure.

  Description:
    This data structure defines the Transaction Request Block.

  Remarks:
    None.
*/

typedef struct
{
    /* SPI Clock speed */
    uint32_t clockFrequency;

    /* SPI clock phase */
    SERCOM_SPI_CLOCK_PHASE clockPhase;

    /* SPI clock polarity */
    SERCOM_SPI_CLOCK_POLARITY clockPolarity;

    /* SPI data bit order */
    SERCOM_SPI_DATA_BITS_ORDER dataBitsOrder;

} SERCOM_SPI_TRANSFER_SETUP;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* PLIB_SERCOM_SPI_MASTER_COMMON_H */
