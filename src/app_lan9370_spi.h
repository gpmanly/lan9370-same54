/*******************************************************************************
  LAN9370 SPI Register Access Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_lan9370_spi.h

  Summary:
    Byte-wide register read/write/modify helpers for the LAN9370 switch over
    the SERCOM0 SPI master.

  Description:
    This module drives the LAN9370 nCS pin and frames SPI register accesses
    using the 4-byte command word documented for the LAN937x family (opcode
    in the top 3 bits, 24-bit address, 5-bit turnaround), then layers on a
    read-modify-write helper. It is intentionally independent of the larger
    Microchip regacc/ethutil framework so it only needs the SERCOM0 SPI PLIB
    and the PORT PLIB already present in this project.
*******************************************************************************/

#ifndef _APP_LAN9370_SPI_H_
#define _APP_LAN9370_SPI_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Configures the LAN9370 nCS pin and the SERCOM0 SPI transfer parameters.
// Must be called once, after SERCOM0_SPI_Initialize(), before any of the
// register access functions below are used.
void APP_LAN9370_SPI_Initialize(void);

// Reads one byte-wide LAN9370 register at "addr" into "*val".
// Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegRead(uint16_t addr, uint8_t *val);

// Writes "val" to the byte-wide LAN9370 register at "addr".
// Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegWrite(uint16_t addr, uint8_t val);

// Read-modify-write: reads the register at "addr", replaces the bits
// selected by "mask" with the corresponding bits of "val", and writes the
// result back. Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegModify(uint16_t addr, uint8_t mask, uint8_t val);

// Reads one 16-bit-wide LAN9370 register at "addr" into "*val", MSB-first,
// as a single continuous SPI transaction (e.g. the SMI Control and Status
// registers in the per-port T1 PHY register map, which are 16 bits wide).
// Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegReadWord(uint16_t addr, uint16_t *val);

// Writes "val" to the 16-bit-wide LAN9370 register at "addr", MSB-first, as
// a single continuous SPI transaction.
// Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegWriteWord(uint16_t addr, uint16_t val);

// Read-modify-write, 16-bit-wide: reads the register at "addr", replaces the
// bits selected by "mask" with the corresponding bits of "val", and writes
// the result back. Returns true on success, false on SPI transfer failure.
bool APP_LAN9370_RegModifyWord(uint16_t addr, uint16_t mask, uint16_t val);

#ifdef __cplusplus
}
#endif

#endif /* _APP_LAN9370_SPI_H_ */
