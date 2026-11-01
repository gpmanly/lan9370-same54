/*
  -v-v-v-v-v-v-v-v-v-v-v-v-v-v-
  GENERATED FILE!  DO NOT EDIT!
  -^-^-^-^-^-^-^-^-^-^-^-^-^-^-
*/

/*
    Copyright (C) 2009 - 2019. Microchip Technology Inc. and its
    subsidiaries (Microchip).  All rights reserved.

    You are permitted to use the software and its derivatives with Microchip
    products. See the license agreement accompanying this software, if any,
    for additional info regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
    WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A
    PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP, OR ITS LICENSORS BE
    LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,
    CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY FOR
    ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO
    ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, OR OTHER
    SIMILAR COSTS. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP AND ITS
    LICENSORS LIABILITY WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
    PAID DIRECTLY TO MICROCHIP TO USE THIS SOFTWARE. MICROCHIP PROVIDES THIS
    SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.
*/

#ifndef SWITCH_REGISTERS_H
#define SWITCH_REGISTERS_H

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>



/*************************************************
    Base types and accessors.
*/

// Convenience macros.
#define BIT(x)  (1UL << x)

#define PORT_SPACE_VALUE_MASK                     0x000F
#define PORT_SPACE_OFFSET                         12
#define PORT_SPACE_MASK                           (PORT_SPACE_VALUE_MASK << PORT_SPACE_OFFSET)
#define FUNCTION_SPACE_VALUE_MASK                 0x000F
#define FUNCTION_SPACE_OFFSET                     8
#define FUNCTION_SPACE_MASK                       (FUNCTION_SPACE_VALUE_MASK << FUNCTION_SPACE_OFFSET)
#define REGISTER_SPACE_VALUE_MASK                 0x00FF
#define REGISTER_SPACE_OFFSET                     0
#define REGISTER_SPACE_MASK                       (REGISTER_SPACE_VALUE_MASK << REGISTER_SPACE_OFFSET)

#define SW_MAX_PHYS                               8
#define SW_MAX_PORTS                              11

#define PHY_VPHY                                  0x00
#define PHY_AFE0                                  0x01
#define PHY_AFE1                                  0x02
#define PHY_AFE2                                  0x03
#define PHY_AFE3                                  0x04
#define PHY_AFE4                                  0x05
#define PHY_AFE5                                  0x06
#define PHY_TX                                    0x07

#define PORT_GLOBAL                               0x00
#define PORT_AFE0                                 0x01
#define PORT_AFE1                                 0x02
#define PORT_AFE2                                 0x03
#define PORT_AFE3                                 0x04
#define PORT_AFE4                                 0x05
#define PORT_AFE5                                 0x06
#define PORT_SGMI                                 0x07
#define PORT_RMII1                                0x08
#define PORT_RMII2                                0x09
#define PORT_TX                                   0x0A

#define PORT_SPACE_GLOBAL                         0x00

#define FUNCTION_SPACE_GLOBAL_OPERATION           0x00
#define FUNCTION_SPACE_GLOBAL_IO                  0x01
#define FUNCTION_SPACE_GLOBAL_PHY                 0x02
#define FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS     0x03
#define FUNCTION_SPACE_GLOBAL_LUE                 0x04
#define FUNCTION_SPACE_GLOBAL_PTP                 0x05
#define FUNCTION_SPACE_GLOBAL_HSR                 0x06
#define FUNCTION_SPACE_GLOBAL_VPHY                0x07
#define FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR    0x08
#define FUNCTION_SPACE_GLOBAL_TX_PHY              0x09
#define FUNCTION_SPACE_GLOBAL_RESERVED_A          0x0A
#define FUNCTION_SPACE_GLOBAL_RESERVED_B          0x0B
#define FUNCTION_SPACE_GLOBAL_RESERVED_C          0x0C
#define FUNCTION_SPACE_GLOBAL_RESERVED_D          0x0D
#define FUNCTION_SPACE_GLOBAL_RESERVED_E          0x0E
#define FUNCTION_SPACE_GLOBAL_RESERVED_F          0x0F

#define FUNCTION_SPACE_PORT_OPERATION             0x00
#define FUNCTION_SPACE_PORT_T1_PHY                0x01
#define FUNCTION_SPACE_PORT_TX_PHY                0x02
#define FUNCTION_SPACE_PORT_SGMII                 0x02
#define FUNCTION_SPACE_PORT_RGMII                 0x03
#define FUNCTION_SPACE_PORT_MAC                   0x04
#define FUNCTION_SPACE_PORT_MIB_COUNTERS          0x05
#define FUNCTION_SPACE_PORT_ACL                   0x06
#define FUNCTION_SPACE_PORT_RESERVED_7            0x07
#define FUNCTION_SPACE_PORT_INGRESS               0x08
#define FUNCTION_SPACE_PORT_EGRESS                0x09
#define FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT      0x0A
#define FUNCTION_SPACE_PORT_LUE                   0x0B
#define FUNCTION_SPACE_PORT_PTP                   0x0C
#define FUNCTION_SPACE_PORT_RESERVED_D            0x0D
#define FUNCTION_SPACE_PORT_RESERVED_E            0x0E
#define FUNCTION_SPACE_PORT_RESERVED_F            0x0F

// Merge fields for Port Space, Function Space, and Register Space into a single register address.
#define mk_sw_reg_addr(_port_space_, _function_space_, _register_space_)                   \
    ((uint16_t)                                                                            \
        (                                                                                  \
            (((_port_space_    ) & PORT_SPACE_VALUE_MASK    ) << PORT_SPACE_OFFSET    ) |  \
            (((_function_space_) & FUNCTION_SPACE_VALUE_MASK) << FUNCTION_SPACE_OFFSET) |  \
            (((_register_space_) & REGISTER_SPACE_VALUE_MASK) << REGISTER_SPACE_OFFSET)    \
        )                                                                                  \
    )                                                                                      \

// Merge port into register address.
#define merge_port_with_addr(_port_space_, _register_space_)                               \
    ((uint16_t)                                                                            \
        (                                                                                  \
            (((_port_space_    ) & PORT_SPACE_VALUE_MASK    ) << PORT_SPACE_OFFSET    ) |  \
            (                                                                              \
                (_register_space_) &                                                       \
                (                                                                          \
                    (FUNCTION_SPACE_VALUE_MASK << FUNCTION_SPACE_OFFSET) |                 \
                    (REGISTER_SPACE_VALUE_MASK << REGISTER_SPACE_OFFSET)                   \
                )                                                                          \
            )                                                                              \
        )                                                                                  \
    )                                                                                      \

// Split a single register address into its fields.
#define get_port_from_addr(_register_address_) \
    (((_register_address_) & PORT_SPACE_MASK) >> PORT_SPACE_OFFSET)

#define get_function_from_addr(_register_address_) \
    (((_register_address_) & FUNCTION_SPACE_MASK) >> FUNCTION_SPACE_OFFSET)

#define get_reg_offset_from_addr(_register_address_) \
    (((_register_address_) & REGISTER_SPACE_MASK) >> REGISTER_SPACE_OFFSET)

#define strip_port_from_addr(_register_address_) \
    ((_register_address_) & (~ PORT_SPACE_MASK))

#define strip_function_from_addr(_register_address_) \
    ((_register_address_) & (~ FUNCTION_SPACE_MASK))

#define strip_offset_from_addr(_register_address_) \
    ((_register_address_) & (~ REGISTER_SPACE_MASK))

// Mappings for phy registers.
#define vphy_smi_addr(_addr_)               mk_sw_reg_addr(PORT_SPACE_GLOBAL,   FUNCTION_SPACE_GLOBAL_VPHY,   ((uint16_t) _addr_))
#define txphy_global_smi_addr(_addr_)       mk_sw_reg_addr(PORT_SPACE_GLOBAL,   FUNCTION_SPACE_GLOBAL_TX_PHY, (((uint16_t) _addr_) << 2))
#define txphy_port_smi_addr(_port_, _addr_) mk_sw_reg_addr(((uint16_t) _port_), FUNCTION_SPACE_PORT_TX_PHY,   (0x80 + (((uint16_t) _addr_) << 2)))
#define t1phy_smi_addr(_port_, _addr_)      mk_sw_reg_addr(((uint16_t) _port_), FUNCTION_SPACE_PORT_T1_PHY,   (((uint16_t) _addr_) << 2))

// Registers vary in their effective byte size.
typedef enum SwitchRegisterAccessSize
{
    REGISTER_BYTE,
    REGISTER_WORD,
    REGISTER_DWORD,
    REGISTER_QWORD,
    REGISTER_DQWORD
} SwRegAccSize_t;

// Modest definitions for register capability sets.
// See register nomenclature, section 2.2 of the HW DOS.
typedef uint16_t SwRegCap_t;

enum SwitchRegisterCapabilities
{
    REGISTER_PORT            = (1 << 0),
    REGISTER_GLOBAL          = (1 << 1),
    REGISTER_READ_CLEAR      = (1 << 2),
    REGISTER_WRITE_ONE_CLEAR = (1 << 3),
    REGISTER_WRITE_ANY_CLEAR = (1 << 4),
    REGISTER_SELF_CLEAR      = (1 << 5),
    REGISTER_SET_ON_READ     = (1 << 6),
    REGISTER_LATCHING        = (1 << 7),
    REGISTER_NASR            = (1 << 8),  // Not affected by SW reset.
    REGISTER_EXTENDED_DATA   = (1 << 9)   // Extended mask data available.
};

// A way to hold information about the registers.
typedef struct SwitchRegisterInformation
{
    const char *       short_name;
    const char *       long_name;
    uint16_t           addr;
    uint16_t           capability;        // Normal Form.  Alternate form.
    SwRegAccSize_t     width;             // Primary:      Primary:         Extension:
    uint32_t           mask_1;            // Reserved.     Reserved.        Write 1 to clear.
    uint32_t           mask_2;            // Read Only.    Read Only.       Write any to clear.
    uint32_t           mask_3;            // Misc.         Self Clear.      Read to clear.
    const char *       description;
} SwRegInfo_t;

// Register extension offsets.
#define get_reg_sub_a(_register_info_) \
    ((_register_info_) + 0)

#define get_reg_sub_b(_register_info_) \
    ((_register_info_) + 1)

#define get_reg_sub_c(_register_info_) \
    ((_register_info_) + 2)

#define get_reg_sub_d(_register_info_) \
    ((_register_info_) + 3)

#define get_reg_ext(_register_info_)                                          \
    (                                                                         \
        (_register_info_) +                                                   \
            (                                                                 \
                ((_register_info_)->width <= REGISTER_DWORD) ? 1 :            \
                    (                                                         \
                        ((_register_info_)->width == REGISTER_QWORD) ? 2 : 4  \
                    )                                                         \
            )                                                                 \
    )                                                                         \

// Simple capability tests.
#define register_is_read_clear(_register_info_) \
    (((_register_info_)->capability & REGISTER_READ_CLEAR) != 0)

#define register_is_write_one_clear(_register_info_) \
    (((_register_info_)->capability & REGISTER_WRITE_ONE_CLEAR) != 0)

#define register_is_write_any_clear(_register_info_) \
    (((_register_info_)->capability & REGISTER_WRITE_ANY_CLEAR) != 0)

#define register_is_self_clear(_register_info_) \
    (((_register_info_)->capability & REGISTER_SELF_CLEAR) != 0)

#define register_is_set_on_read(_register_info_) \
    (((_register_info_)->capability & REGISTER_SET_ON_READ) != 0)

#define register_is_latching(_register_info_) \
    (((_register_info_)->capability & REGISTER_LATCHING) != 0)

#define register_is_nasr(_register_info_) \
    (((_register_info_)->capability & REGISTER_NASR) != 0)

#define register_is_extended(_register_info_) \
    (((_register_info_)->capability & REGISTER_EXTENDED_DATA) != 0)

#define register_is_global(_register_info_) \
    (((_register_info_)->capability & REGISTER_GLOBAL) != 0)

#define register_is_port(_register_info_) \
    (((_register_info_)->capability & REGISTER_PORT) != 0)

#define register_is_shadow(_register_info_) \
    (((_register_info_)->capability & (REGISTER_GLOBAL|REGISTER_PORT)) == 0)

// Simple size tests.
#define register_is_byte(_register_info_) \
    ((_register_info_)->width == REGISTER_BYTE)

#define register_is_word(_register_info_) \
    ((_register_info_)->width == REGISTER_WORD)

#define register_is_dword(_register_info_) \
    ((_register_info_)->width == REGISTER_DWORD)

#define register_is_qword(_register_info_) \
    ((_register_info_)->width == REGISTER_QWORD)

#define register_is_dqword(_register_info_) \
    ((_register_info_)->width == REGISTER_DQWORD)

// Member access.
#define register_short_name(_register_info_) \
    (_register_info_)->short_name

#define register_long_name(_register_info_) \
    (_register_info_)->long_name

#define register_addr(_register_info_) \
    (_register_info_)->addr

#define register_width(_register_info_) \
    (_register_info_)->width

#define register_reserved_mask_sub_a(_register_info_) \
    (get_reg_sub_a(_register_info_))->mask_1

#define register_reserved_mask_sub_b(_register_info_) \
    (get_reg_sub_b(_register_info_))->mask_1

#define register_reserved_mask_sub_c(_register_info_) \
    (get_reg_sub_c(_register_info_))->mask_1

#define register_reserved_mask_sub_d(_register_info_) \
    (get_reg_sub_d(_register_info_))->mask_1

#define register_read_only_mask_sub_a(_register_info_) \
    (get_reg_sub_a(_register_info_))->mask_2

#define register_read_only_mask_sub_b(_register_info_) \
    (get_reg_sub_b(_register_info_))->mask_2

#define register_read_only_mask_sub_c(_register_info_) \
    (get_reg_sub_c(_register_info_))->mask_2

#define register_read_only_mask_sub_d(_register_info_) \
    (get_reg_sub_d(_register_info_))->mask_2

    // This one is in the misc mask either format.
#define register_self_clear_mask_sub_a(_register_info_)                   \
    (! register_is_self_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
    (get_reg_sub_a(_register_info_))->mask_3                              \

#define register_self_clear_mask_sub_b(_register_info_)                   \
    (! register_is_self_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
    (get_reg_sub_b(_register_info_))->mask_3                              \

#define register_self_clear_mask_sub_c(_register_info_)                   \
    (! register_is_self_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
    (get_reg_sub_c(_register_info_))->mask_3                              \

#define register_self_clear_mask_sub_d(_register_info_)                   \
    (! register_is_self_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
    (get_reg_sub_d(_register_info_))->mask_3                              \

#define register_write_one_to_clear_mask_sub_a(_register_info_)           \
    (! register_is_write_one_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_a(get_reg_ext(_register_info_)))->mask_1 :           \
        (get_reg_sub_a(_register_info_))->mask_3)                         \

#define register_write_one_to_clear_mask_sub_b(_register_info_)           \
    (! register_is_write_one_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_b(get_reg_ext(_register_info_)))->mask_1 :           \
        (get_reg_sub_b(_register_info_))->mask_3)                         \

#define register_write_one_to_clear_mask_sub_c(_register_info_)           \
    (! register_is_write_one_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_c(get_reg_ext(_register_info_)))->mask_1 :           \
        (get_reg_sub_c(_register_info_))->mask_3)                         \

#define register_write_one_to_clear_mask_sub_d(_register_info_)           \
    (! register_is_write_one_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_d(get_reg_ext(_register_info_)))->mask_1 :           \
        (get_reg_sub_d(_register_info_))->mask_3)                         \

#define register_write_any_to_clear_mask_sub_a(_register_info_)           \
    (! register_is_write_any_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_a(get_reg_ext(_register_info_)))->mask_2 :           \
        (get_reg_sub_a(_register_info_))->mask_3)                         \

#define register_write_any_to_clear_mask_sub_b(_register_info_)           \
    (! register_is_write_any_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_b(get_reg_ext(_register_info_)))->mask_2 :           \
        (get_reg_sub_b(_register_info_))->mask_3)                         \

#define register_write_any_to_clear_mask_sub_c(_register_info_)           \
    (! register_is_write_any_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_c(get_reg_ext(_register_info_)))->mask_2 :           \
        (get_reg_sub_c(_register_info_))->mask_3)                         \

#define register_write_any_to_clear_mask_sub_d(_register_info_)           \
    (! register_is_write_any_clear(_register_info_)) ? ((uint32_t) 0UL) : \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_d(get_reg_ext(_register_info_)))->mask_2 :           \
        (get_reg_sub_d(_register_info_))->mask_3)                         \

#define register_read_to_clear_mask_sub_a(_register_info_)                \
    (! register_is_read_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_a(get_reg_ext(_register_info_)))->mask_3 :           \
        (get_reg_sub_a(_register_info_))->mask_3)                         \

#define register_read_to_clear_mask_sub_b(_register_info_)                \
    (! register_is_read_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_b(get_reg_ext(_register_info_)))->mask_3 :           \
        (get_reg_sub_b(_register_info_))->mask_3)                         \

#define register_read_to_clear_mask_sub_c(_register_info_)                \
    (! register_is_read_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_c(get_reg_ext(_register_info_)))->mask_3 :           \
        (get_reg_sub_c(_register_info_))->mask_3)                         \

#define register_read_to_clear_mask_sub_d(_register_info_)                \
    (! register_is_read_clear(_register_info_)) ? ((uint32_t) 0UL) :      \
        (register_is_extended(_register_info_) ?                          \
        (get_reg_sub_d(get_reg_ext(_register_info_)))->mask_3 :           \
        (get_reg_sub_d(_register_info_))->mask_3)                         \

#define register_description(_register_info_) \
    (_register_info_)->description


/*************************************************
    The device specific register info table.

    NOTE: Only generated in the "C" file.  The
    register fields are provided in context for
    easier reading.
*/

#ifdef SWITCH_REGISTERS_C
#define define_sw_reg(_index_, _name_, _function_space_, _register_space_, _width_, _capability_, _mask_1_, _mask_2_, _mask_3_, _description_) \
    {                                                                                     \
         .short_name      = (#_index_),                                                   \
         .long_name       = (_name_),                                                     \
         .addr            = mk_sw_reg_addr(0, (_function_space_), (_register_space_)),    \
         .capability      = (_capability_),                                               \
         .width           = (_width_),                                                    \
         .mask_1          = (_mask_1_),                                                   \
         .mask_2          = (_mask_2_),                                                   \
         .mask_3          = (_mask_3_),                                                   \
         .description     = (_description_)                                               \
    }                                                                                     \

#else
#define define_sw_reg(_index_, _name_, _function_space_, _register_space_, _width_, _capability_, _mask_1__, _mask_2_, _mask_3_, _description_) \
    _index_                                                                                                     \

#endif

#ifdef SWITCH_REGISTERS_C
const SwRegInfo_t SwRegTbl[] =
{
#else
extern const SwRegInfo_t SwRegTbl[];

typedef enum SwitchRegisterTableIndecies
{
#endif

    define_sw_reg(
        GLB_CHID0, "Global Chip ID 0",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0000,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "The 4 byte manufacturer's chip identity code."
    ),

    define_sw_reg(
        GLB_CHID1, "Global Chip ID 1",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0001,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "The 4 byte manufacturer's chip identity code."
    ),

    define_sw_reg(
        GLB_CHID2, "Global Chip ID 2",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0002,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "The 4 byte manufacturer's chip identity code."
    ),

    define_sw_reg(
        GLB_CHID3, "Global Chip ID 3",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0003,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x0F, // Reserved mask.
        0xF0, // Read only mask.
        0x00, // Misc mask.
        "The 4 byte manufacturer's chip identity code."
    ),

    define_sw_reg(
        GLB_CONTROL0, "Global Control 0",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0007,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x73, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "SPI access to PHY registers."
    ),

    define_sw_reg(
        GLB_BOND_OPT, "Global Bonding Option",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x000F,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xF8, // Reserved mask.
        0x07, // Read only mask.
        0x00, // Misc mask.
        "Reads back the bond pads."
    ),

    define_sw_reg(
        GLB_INT_STS, "Global Interrupt Status",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0010,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0x01FFFFFF, // Reserved mask.
        0xFC000000, // Read only mask.
        0x02000000, // Misc mask.
        "IRQn status at the top node of the interrupt source tree."
    ),

    define_sw_reg(
        GLB_INT_MSK, "Global Interrupt Mask",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0014,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x01FFFFFF, // Reserved mask.
        0x02000000, // Read only mask.
        0x00000000, // Misc mask.
        "IRQn mask for the top node of the interrupt source tree."
    ),

    define_sw_reg(
        GLB_PINT_STS, "Global Port Interrupt Status",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0018,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFF00, // Reserved mask.
        0x000000FF, // Read only mask.
        0x00000000, // Misc mask.
        "IRQn status for the ports node of the interrupt source tree."
    ),

    define_sw_reg(
        GLB_PINT_MSK, "Global Port Interrupt Mask",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x001C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "IRQn mask for the ports node of the interrupt source tree."
    ),

    define_sw_reg(
        GLB_FPGA_MAJOR, "Global FPGA Major",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0020,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Major number for the pre-silicon RTL build."
    ),

    define_sw_reg(
        GLB_FPGA_MINOR, "Global FPGA Minor",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0024,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Minor number for the pre-silicon RTL build."
    ),

    define_sw_reg(
        GLB_CASCADE_MODE_CTL, "Global Cascade Mode Control",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0030,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFF6FF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Switch cascading information and control."
    ),

    define_sw_reg(
        GLB_PART_NET_CFG, "Global Partial Network Enable",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0034,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Enable for port based partial networks, one bit per port."
    ),

    define_sw_reg(
        GLB_SPARE0, "Global Spare 0",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0050,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Scratch register for addressing field errata."
    ),

    define_sw_reg(
        GLB_SPARE1, "Global Spare 1",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0054,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Scratch register for addressing field errata."
    ),

    define_sw_reg(
        GLB_SPARE2, "Global Spare 2",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x0058,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Scratch register for addressing field errata."
    ),

    define_sw_reg(
        GLB_SPARE3, "Global Spare 3",
        FUNCTION_SPACE_GLOBAL_OPERATION, 0x005C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Scratch register for addressing field errata."
    ),

    define_sw_reg(
        GLB_SER_IO_CTL, "Global Serial I/O Control",
        FUNCTION_SPACE_GLOBAL_IO, 0x0000,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x08, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configuration for MDIO, SPI access and Endianness."
    ),

    define_sw_reg(
        GLB_OUT_CLK_CTL, "Global Output Clock",
        FUNCTION_SPACE_GLOBAL_IO, 0x0003,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Clock enables for 125MHz and 25MHz clocks."
    ),

    define_sw_reg(
        GLB_IBA_CTL, "Global In-Band Management (IBA) Control",
        FUNCTION_SPACE_GLOBAL_IO, 0x0004,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x1E380000, // Reserved mask.
        0x00000000, // Read only mask.
        0x20000000, // Misc mask.
        "Configuration for in-band management (IBA)."
    ),

    define_sw_reg(
        GLB_APB_TO_ADDR, "Global IO APB Timeout Address",
        FUNCTION_SPACE_GLOBAL_IO, 0x0008,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0x7FFF0000, // Reserved mask.
        0x0000FFFF, // Read only mask.
        0x80000000, // Misc mask.
        "Holds the internal address that caused the APB access timeout."
    ),

    define_sw_reg(
        GLB_IO_DRV_STR, "Global I/O Drive Strength",
        FUNCTION_SPACE_GLOBAL_IO, 0x000D,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFCCC, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Sets the drive strength in mA for the xMII pads."
    ),

    define_sw_reg(
        GLB_IO_RGMII_SLEW, "Global I/O RGMII Slew Rate",
        FUNCTION_SPACE_GLOBAL_IO, 0x000F,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "configures slew rate for RGMII pads."
    ),

    define_sw_reg(
        GLB_IBA_OP_STS1, "Global In-Band Management (IBA) Operation Status 1",
        FUNCTION_SPACE_GLOBAL_IO, 0x0010,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x1FFF8380, // Reserved mask.
        0xE0007C7F, // Read only mask.
        0x00000000, // Misc mask.
        "Reads IBA error infromation."
    ),

    define_sw_reg(
        GLB_IBA_OP_STS2, "Global In-Band Management (IBA) Operation Status 2",
        FUNCTION_SPACE_GLOBAL_IO, 0x0014,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x03800000, // Reserved mask.
        0xFC7FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Reads IBA Status Information."
    ),

    define_sw_reg(
        GLB_IBA_ACC, "Global In-Band Management (IBA) Access Result",
        FUNCTION_SPACE_GLOBAL_IO, 0x0018,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00FFFFC0, // Reserved mask.
        0xFF00003F, // Read only mask.
        0x00000000, // Misc mask.
        "IBA command execution count and retry count"
    ),

    define_sw_reg(
        GLB_LED_OVR, "Global LED Override",
        FUNCTION_SPACE_GLOBAL_IO, 0x0020,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFC00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        ""
    ),

    define_sw_reg(
        GLB_LED_SRC, "Global LED Source",
        FUNCTION_SPACE_GLOBAL_IO, 0x0028,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF3, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Led Configuration."
    ),

    define_sw_reg(
        GLB_SGMII_CTL, "Global SGMII Control",
        FUNCTION_SPACE_GLOBAL_IO, 0x002C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFE0FFFF, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Wait cycles before ending SPI Access."
    ),

    define_sw_reg(
        GLB_VDDIO_PAD_TUNE, "Global VDDIO Pad Tune",
        FUNCTION_SPACE_GLOBAL_IO, 0x0030,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x3000, // Reserved mask.
        0x0FC0, // Read only mask.
        0x8000, // Misc mask.
        "Controls VDIO segment of Pad ring."
    ),

    define_sw_reg(
        GLB_RGMII1_PAD_TUNE, "Global RGMII 1 Pad Tune",
        FUNCTION_SPACE_GLOBAL_IO, 0x0034,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x3000, // Reserved mask.
        0x0FC0, // Read only mask.
        0x8000, // Misc mask.
        "Controls the RGMII segment of pad ring for logical port 5."
    ),

    define_sw_reg(
        GLB_RGMII2_PAD_TUNE, "Global RGMII 2 Pad Tune",
        FUNCTION_SPACE_GLOBAL_IO, 0x0038,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x3000, // Reserved mask.
        0x0FC0, // Read only mask.
        0x8000, // Misc mask.
        "Controls the RGMII segment of pad ring for logical port 6."
    ),

    define_sw_reg(
        GLB_LED_T1_SEL, "Global LED T1 Select",
        FUNCTION_SPACE_GLOBAL_IO, 0x003C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xC0000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Configures T1 AFE LED MUX select."
    ),

    define_sw_reg(
        GLB_LED_TX_SEL, "Global LED 100TX PHY Select",
        FUNCTION_SPACE_GLOBAL_IO, 0x0040,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xF0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures T1 AFE LED override enable and MUX select."
    ),

    define_sw_reg(
        GLB_PIO_INT_STS, "Global PIO Interrupt Status",
        FUNCTION_SPACE_GLOBAL_IO, 0x0042,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0xFC00, // Reserved mask.
        0x0000, // Read only mask.
        0x03FF, // Misc mask.
        "Global PIO Interrupt Status."
    ),

    define_sw_reg(
        GLB_PIO_INT_MSK, "Global PIO Interrupt Mask",
        FUNCTION_SPACE_GLOBAL_IO, 0x0044,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFC00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures Global PIO Interrupt mask."
    ),

    define_sw_reg(
        GLB_PIO_STS, "Global PIO Status",
        FUNCTION_SPACE_GLOBAL_IO, 0x0046,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFC00, // Reserved mask.
        0x03FF, // Read only mask.
        0x0000, // Misc mask.
        "Reads Global PIO Status."
    ),

    define_sw_reg(
        GLB_PIO_DEB_EN, "Global PIO De-bounce Enable",
        FUNCTION_SPACE_GLOBAL_IO, 0x0048,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFF00000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Configures PIO De-bounce enable."
    ),

    define_sw_reg(
        GLB_PIO_DEB_STS, "Global PIO De-bounce Status",
        FUNCTION_SPACE_GLOBAL_IO, 0x004C,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFE, // Reserved mask.
        0x01, // Read only mask.
        0x00, // Misc mask.
        "Reads Global PIO De-bounce Status"
    ),

    define_sw_reg(
        GLB_PIO_DEB_1US_CNT, "PIO Debounce Count One Microsecond",
        FUNCTION_SPACE_GLOBAL_IO, 0x004D,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "1 us PIO De-bounce counter status."
    ),

    define_sw_reg(
        GLB_PIO_DEB_1MS_CNT, "Global PIO Debounce Count One Millisecond",
        FUNCTION_SPACE_GLOBAL_IO, 0x004E,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "1 ms PIO De-bounce counter status."
    ),

    define_sw_reg(
        GLB_PIO_DEB_TEST, "Global PIO De-bounce Test",
        FUNCTION_SPACE_GLOBAL_IO, 0x004F,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO De-bounce counters to single system clock cycle (for test and verification purposes only)."
    ),

    define_sw_reg(
        GLB_CFG_PIO0, "Global Configure PIO0",
        FUNCTION_SPACE_GLOBAL_IO, 0x0050,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO0."
    ),

    define_sw_reg(
        GLB_CFG_PIO1, "Global Configure PIO1",
        FUNCTION_SPACE_GLOBAL_IO, 0x0051,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO1."
    ),

    define_sw_reg(
        GLB_CFG_PIO2, "Global Configure PIO2",
        FUNCTION_SPACE_GLOBAL_IO, 0x0052,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO2."
    ),

    define_sw_reg(
        GLB_CFG_PIO3, "Global Configure PIO3",
        FUNCTION_SPACE_GLOBAL_IO, 0x0053,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO3."
    ),

    define_sw_reg(
        GLB_CFG_PIO4, "Global Configure PIO4",
        FUNCTION_SPACE_GLOBAL_IO, 0x0054,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO4."
    ),

    define_sw_reg(
        GLB_CFG_PIO5, "Global Configure PIO5",
        FUNCTION_SPACE_GLOBAL_IO, 0x0055,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO5."
    ),

    define_sw_reg(
        GLB_CFG_PIO6, "Global Configure PIO6",
        FUNCTION_SPACE_GLOBAL_IO, 0x0056,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO6."
    ),

    define_sw_reg(
        GLB_CFG_PIO7, "Global Configure PIO7",
        FUNCTION_SPACE_GLOBAL_IO, 0x0057,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO7."
    ),

    define_sw_reg(
        GLB_CFG_PIO8, "Global Configure PIO8",
        FUNCTION_SPACE_GLOBAL_IO, 0x0058,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO8."
    ),

    define_sw_reg(
        GLB_CFG_PIO9, "Global Configure PIO9",
        FUNCTION_SPACE_GLOBAL_IO, 0x0059,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures PIO9."
    ),

    define_sw_reg(
        CFG_STRAP_VAL, "Global Configuration Strap Value",
        FUNCTION_SPACE_GLOBAL_PHY, 0x0010,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFF0000, // Reserved mask.
        0x0000FFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Lists the loaded configuration strap values."
    ),

    define_sw_reg(
        CFG_STRAP_OVR, "Global Configuration Strap Override",
        FUNCTION_SPACE_GLOBAL_PHY, 0x0014,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x7FFFFFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Lists the loaded configuration strap values."
    ),

    define_sw_reg(
        GLB_SW_CONTROL0, "Global Switch Control 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0000,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x02, // Misc mask.
        "Enables Double tagging, Soft Hardware reset."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR0, "Global Switch MAC Address 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0002,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR1, "Global Switch MAC Address 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0003,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR2, "Global Switch MAC Address 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0004,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR3, "Global Switch MAC Address 3",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0005,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR4, "Global Switch MAC Address 4",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0006,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_MAC_ADDR5, "Global Switch MAC Address 5",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0007,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "6 Byte Switch MAC Address."
    ),

    define_sw_reg(
        GLB_SW_ISP_TPID, "Global Switch ISP TPID",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x000A,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures switch ISP TPID."
    ),

    define_sw_reg(
        GLB_SW_HSR_TPID, "Global Switch HSR TPID",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x000C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures switch HSR TPID"
    ),

    define_sw_reg(
        GLB_SW_SHP_STR, "Global AVB Credit Based Shaper Strategy",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x000E,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFFFC, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures Shaping and Policing Strategy."
    ),

    define_sw_reg(
        GLB_SW_LUE_CTL0, "Global Switch Lookup Engine Control 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0010,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Enables VLAN and configures Lookup options."
    ),

    define_sw_reg(
        GLB_SW_LUE_CTL1, "Global Switch Lookup Engine Control 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0011,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x30, // Misc mask.
        "Configures learning options."
    ),

    define_sw_reg(
        GLB_SW_LUE_CTL2, "Global Switch Lookup Engine Control 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0012,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x40, // Read only mask.
        0x00, // Misc mask.
        "Configures lookup and filtering options."
    ),

    define_sw_reg(
        GLB_SW_LUE_CTL3, "Global Switch Lookup Engine Control 3",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0013,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures Lower 8 bits of 20 bits age period."
    ),

    define_sw_reg(
        GLB_SW_LUE_INT_STS, "Global Switch Lookup Engine Interrupt",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0014,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0xFA, // Reserved mask.
        0x00, // Read only mask.
        0x05, // Misc mask.
        "Learning and CPU Write fail to dynamic MAC table interrupts."
    ),

    define_sw_reg(
        GLB_SW_LUE_INT_MASK, "Global Switch Lookup Engine Interrupt Mask",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0015,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFA, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Learning and CPU Write fail to dynamic MAC table interrupt masks."
    ),

    define_sw_reg(
        GLB_SW_LUE_INDEX0, "Global Switch Lookup Engine Entry Index 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0016,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFC00, // Reserved mask.
        0x03FF, // Read only mask.
        0x0000, // Misc mask.
        "Address of CPU Indirect Write Location."
    ),

    define_sw_reg(
        GLB_SW_LUE_INDEX1, "Global Switch Lookup Engine Entry Index 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0018,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x00FF, // Read only mask.
        0x0000, // Misc mask.
        "CPU Indirect Static MAC Address table Access Index."
    ),

    define_sw_reg(
        GLB_SW_LUE_INDEX2, "Global Switch Lookup Engine Entry Index 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x001A,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x00FF, // Read only mask.
        0x0000, // Misc mask.
        "CPU Indirect Dynamic MAC Address table Access Index."
    ),

    define_sw_reg(
        GLB_SW_ALU2_AVAIL_ENTRY, "Global Switch ALU2 Available Entry",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x001C,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x7E007E00, // Reserved mask.
        0x01FF01FF, // Read only mask.
        0x80000000, // Misc mask.
        "Static table information."
    ),

    define_sw_reg(
        GLB_SW_LUE_AGE, "Global Switch LUE Age Period",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0020,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xF000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Upper 12 bits of 20 bits Aging period."
    ),

    define_sw_reg(
        GLB_SW_LUE_UNK0, "Global Switch LUE Unknown Control 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0022,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x7F80, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures the Unknown Unicast packet forward behavior."
    ),

    define_sw_reg(
        GLB_SW_LUE_UNK1, "Global Switch LUE Unknown Control 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0024,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x7F80, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures the Unknown Multicast packet forward behavior."
    ),

    define_sw_reg(
        GLB_SW_LUE_UNK2, "Global Switch LUE Unknown Control 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0026,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x7F80, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Configures the Unknown VID packet forward behavior."
    ),

    define_sw_reg(
        GLB_SW_VLAN_FLUSH, "Global Switch VLAN Flush",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0028,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x7F80FF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x80000000, // Misc mask.
        "Configures VLAN Flush Parameters."
    ),

    define_sw_reg(
        GLB_SW_ALU2_ENTRY_LMT, "Global Switch ALU2 Entry Limit",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x002C,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SET_ON_READ,
        0x0000FE00, // Reserved mask.
        0x00000000, // Read only mask.
        0xFFFF0000, // Misc mask.
        "Configures the ALU2 learn limit and learn fail count."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL0, "Global Switch MAC Control 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0030,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x6C, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Enables back off mode, Truncate MAC Control frames and Flow Control Packet Drop."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL1, "Global Switch MAC Control 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0031,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x06, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Configures back pressure mode,Flow control mode and Multicast storm protection."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL2, "Global Switch MAC Control 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0032,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xF0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Null VID Replacement with Default VID, Broadcast Strom Rate(last 3 bits of 11 bits)."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL3, "Global Switch MAC Control 3",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0033,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Broadcast Storm Protection Rate first 8 bits of 11 bits."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL4, "Global Switch Mac Control 4",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0034,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Pass Flow Control packets."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL5, "Global Switch MAC Control 5",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0035,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x87, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress Rate limit period and Egress Rate limit enable."
    ),

    define_sw_reg(
        GLB_SW_MAC_CTL6, "Global Switch MAC Control 6",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0036,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x3F, // Reserved mask.
        0x00, // Read only mask.
        0x80, // Misc mask.
        "Flush and Freeze MIB Counters."
    ),

    define_sw_reg(
        GLB_SW_PRI_MAP0, "Global 802.1p Priority Mapping 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0038,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Priority Mapping Information."
    ),

    define_sw_reg(
        GLB_SW_PRI_MAP1, "Global 802.1p Priority Mapping 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0039,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Priority Mapping Information."
    ),

    define_sw_reg(
        GLB_SW_PRI_MAP2, "Global 802.1p Priority Mapping 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x003A,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Priority Mapping Information."
    ),

    define_sw_reg(
        GLB_SW_PRI_MAP3, "Global 802.1p Priority Mapping 3",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x003B,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Priority Mapping Information."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_EN, "Global DiffServ Priority Enable",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x003E,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Diffserv Priority Remap."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP0, "Global DiffServ Priority Mapping 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0040,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP1, "Global DiffServ Priority Mapping 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0041,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP2, "Global DiffServ Priority Mapping 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0042,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP3, "Global DiffServ Priority Mapping 3",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0043,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP4, "Global DiffServ Priority Mapping 4",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0044,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP5, "Global DiffServ Priority Mapping 5",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0045,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP6, "Global DiffServ Priority Mapping 6",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0046,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP7, "Global DiffServ Priority Mapping 7",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0047,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP8, "Global DiffServ Priority Mapping 8",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0048,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP9, "Global DiffServ Priority Mapping 9",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0049,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP10, "Global DiffServ Priority Mapping 10",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004A,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP11, "Global DiffServ Priority Mapping 11",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004B,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP12, "Global DiffServ Priority Mapping 12",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004C,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP13, "Global DiffServ Priority Mapping 13",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004D,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP14, "Global DiffServ Priority Mapping 14",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004E,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP15, "Global DiffServ Priority Mapping 15",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x004F,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP16, "Global DiffServ Priority Mapping 16",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0050,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP17, "Global DiffServ Priority Mapping 17",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0051,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP18, "Global DiffServ Priority Mapping 18",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0052,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP19, "Global DiffServ Priority Mapping 19",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0053,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP20, "Global DiffServ Priority Mapping 20",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0054,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP21, "Global DiffServ Priority Mapping 21",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0055,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP22, "Global DiffServ Priority Mapping 22",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0056,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP23, "Global DiffServ Priority Mapping 23",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0057,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP24, "Global DiffServ Priority Mapping 24",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0058,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP25, "Global DiffServ Priority Mapping 25",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0059,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP26, "Global DiffServ Priority Mapping 26",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005A,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP27, "Global DiffServ Priority Mapping 27",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005B,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP28, "Global DiffServ Priority Mapping 28",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005C,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP29, "Global DiffServ Priority Mapping 29",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005D,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP30, "Global DiffServ Priority Mapping 30",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005E,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        GLB_SW_DIFFSV_PRI_MAP31, "Global DiffServ Priority Mapping 31",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x005F,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x88, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Diffserv Priority Mapping."
    ),

    define_sw_reg(
        MBIST_ENB, "MBIST Enable",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0060,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Enable."
    ),

    define_sw_reg(
        MBIST_STATUS_C1, "MBIST Controller C1 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0061,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Status for IBA, Cut Through and ALU2 (Static) Table."
    ),

    define_sw_reg(
        MBIST_STATUS_C2, "MBIST Controller C2 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0062,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST status for Dynamic table and HSR RAM."
    ),

    define_sw_reg(
        MBIST_STATUS_C3, "MBIST Controller C3 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0063,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST status for TXQ_LLT and PM_LLT."
    ),

    define_sw_reg(
        MBIST_STATUS_C4, "MBIST Controller C4 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0064,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Status for PM."
    ),

    define_sw_reg(
        MBIST_STATUS_C5, "MBIST Controller C5 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0065,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Status for VLAN."
    ),

    define_sw_reg(
        MBIST_STATUS_C6, "MBIST Controller C6 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0066,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Status for MIB."
    ),

    define_sw_reg(
        MBIST_STATUS_C7, "MBIST Controller C7 Status",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0067,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFC, // Reserved mask.
        0x03, // Read only mask.
        0x00, // Misc mask.
        "Memory BIST Status for QCI, ACL and TAS."
    ),

    define_sw_reg(
        GLB_SW_PORT_MIR_SNP_CTL, "Global Port Mirroring and Snooping Control",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0070,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xB2, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Global Controls for port ring, IGMP and MLD Snooping."
    ),

    define_sw_reg(
        GLB_SW_MRI_CTL1, "Global Switch MRI Control 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0074,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x7F800000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Class D Ip Multicast forwarding behavior."
    ),

    define_sw_reg(
        GLB_SW_MRI_CTL2, "Global Switch MRI Control 2",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0078,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xC0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "DSCP values to Policing color mapping."
    ),

    define_sw_reg(
        GLB_SW_PTP_EVT_PRI, "Global PTP Event Message Priority",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x007C,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x78, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "PTP Event Message Priority."
    ),

    define_sw_reg(
        GLB_SW_PTP_NON_EVT_PRI, "Global PTP Non-Event Message Priority",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x007D,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x78, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "PTP Non Event Message priority."
    ),

    define_sw_reg(
        GLB_SW_MTI_DBG, "Global Switch MTI Debug",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0080,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFF0000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "CPU Debug Tag."
    ),

    define_sw_reg(
        GLB_QUE_MGT_CTL0, "Global Queue Management Control 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0090,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFFD, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Unicast Port VLAN Membership Discard."
    ),

    define_sw_reg(
        GLB_PM_PRT_SEQ_IDX, "Global Packet Port Sequence Entry Index",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0094,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFFC, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Packet Port Entry Sequence Index."
    ),

    define_sw_reg(
        GLB_PM_PRT_SEQ, "Global Packet Port Sequence",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x0098,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xF0F0F0F0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Packet Port Sequence."
    ),

    define_sw_reg(
        GLB_PM_WATER_MARK, "Global Packet Memory PM Water Mark Register",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00A4,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xF800F800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "High Water Mark and Low Water Mark for Flow control."
    ),

    define_sw_reg(
        GLB_TXQ_WATER_MARK, "Global Packet Memory TX Queue Water Mark",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00A8,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xF800F800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Tx Queue High and Low Water Mark for Flow control."
    ),

    define_sw_reg(
        GLB_PM_AVAIL_BLK_CNT, "Global Packet Memory Available Block Count",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00AC,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xF000F800, // Reserved mask.
        0x0FFF07FF, // Read only mask.
        0x00000000, // Misc mask.
        "Packet Memory Available block Count."
    ),

    define_sw_reg(
        GLB_LINK_LIST_CHK_EN0, "Global Linked List Check Enable 0",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00B0,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xF800F800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Hard Ceiling for Available block count and Number of packet in queue."
    ),

    define_sw_reg(
        GLB_LINK_LIST_CHK_EN1, "Global Linked List Check Enable 1",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00B4,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0xFFFFFE00, // Reserved mask.
        0x00000000, // Read only mask.
        0x000000FF, // Misc mask.
        "Tx Queue based list check, Packet memory based list check for available block count."
    ),

    define_sw_reg(
        GLB_RSV_MAC_CTL, "Global RSV MAC Control",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00E0,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00E0E0E0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Tx IPG Configuration."
    ),

    define_sw_reg(
        GLB_CRS_BCK_PRES_CTL, "Global CRS Back Pressure Control",
        FUNCTION_SPACE_GLOBAL_BASIC_FUNCTIONS, 0x00E8,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x400000FF, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Back Pressure Configuration."
    ),

    define_sw_reg(
        GLB_SW_LUE_VLAN_ENTRY0, "Global VLAN Table Entry 0",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0000,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x70FF8F80, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "VLAN settings."
    ),

    define_sw_reg(
        GLB_SW_LUE_VLAN_ENTRY1, "Global VLAN Table Entry 1",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0004,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFF000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Untag policy for Egress ports."
    ),

    define_sw_reg(
        GLB_SW_LUE_VLAN_ENTRY2, "Global VLAN Table Entry 2",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0008,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFF000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "VLAN forwarding port membership."
    ),

    define_sw_reg(
        GLB_SW_LUE_VLAN_INDEX, "Global VLAN Table Index",
        FUNCTION_SPACE_GLOBAL_LUE, 0x000C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xF000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "VLAN Index."
    ),

    define_sw_reg(
        GLB_SW_LUE_VLAN_CTRL, "Global ALU VLAN Table Access Control",
        FUNCTION_SPACE_GLOBAL_LUE, 0x000E,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x7C, // Reserved mask.
        0x00, // Read only mask.
        0x80, // Misc mask.
        "VLAN Table Action."
    ),

    define_sw_reg(
        GLB_ALU_INDEX0, "Global ALU Table Index 0",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0010,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFF800000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "MAC Address and FID to hash index the lookup table."
    ),

    define_sw_reg(
        GLB_ALU_INDEX1, "Global ALU Table Index 1",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0014,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Lower 32 bits of MAC address used to hash index Look up tables."
    ),

    define_sw_reg(
        GLB_ALU_ACCESS_CTRL, "Global ALU Table Access",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0018,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR | REGISTER_SET_ON_READ | REGISTER_EXTENDED_DATA,
        0xC000FF18, // Reserved mask.
        0x3FFF0020, // Read only mask.
        0x00000080, // Self clearing mask.
        "ALU Table Parameters."
    ),

    define_sw_reg(
        GLB_ALU_ACCESS_CTRL_ext, NULL,  // Extension.
        0, 0,
        0,
        0,
        0x00000000, // Write 1 to clear mask.
        0x00000000, // Write any to clear mask.
        0x00000040, // Read to clear mask.
        NULL
    ),

    define_sw_reg(
        GLB_STATIC_MCAST_CTL, "Global Static and Reserved Table Control",
        FUNCTION_SPACE_GLOBAL_LUE, 0x001C,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0xE00F0000, // Reserved mask.
        0x1FF00020, // Read only mask.
        0x000000C0, // Misc mask.
        "ALU Table Parameters."
    ),

    define_sw_reg(
        GLB_ALU_TBL_ENT1, "Global ALU Table Entry 1",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0020,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x03FFFFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Address Table Filters, Age count, MSTP ID."
    ),

    define_sw_reg(
        GLB_ALU_TBL_ENT2, "Global ALU Table Entry 2",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0024,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x23FFFF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Port forwarding map for dynamic table."
    ),

    define_sw_reg(
        GLB_ALU_TBL_ENT3, "Global ALU Table Entry 3",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0028,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFF800000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "FID value and higher 16 bits of MAC address."
    ),

    define_sw_reg(
        GLB_ALU_TBL_ENT4, "Global ALU Table Entry 4",
        FUNCTION_SPACE_GLOBAL_LUE, 0x002C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Lower 32 bits of MAC Address in entry."
    ),

    define_sw_reg(
        GLB_LRN_FAIL_CTL, "Global ALU Learn Fail Control",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0030,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x30, // Reserved mask.
        0x4F, // Read only mask.
        0x80, // Misc mask.
        "Learn Fail Valid, Learn Fail Source, Learn Fail Port."
    ),

    define_sw_reg(
        GLB_ONE_SHOT_CTL, "Global ALU Learn Fail One Shot Control",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0031,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "One Shot Mode."
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR0, "Global ALU Learn Fail Address 0",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0032,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  (47:40)"
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR1, "Global ALU Learn Fail Address 1",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0033,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  (39:32)"
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR2, "Global ALU Learn Fail Address 2",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0034,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  (31:24)"
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR3, "Global ALU Learn Fail Address 3",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0035,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  23:16"
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR4, "Global ALU Learn Fail Address 4",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0036,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  (15:8)"
    ),

    define_sw_reg(
        GLB_LEARN_FAIL_ADDR5, "Global ALU Learn Fail Address 5",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0037,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "Learn Fail Address  (7:0)"
    ),

    define_sw_reg(
        GLB_HSR_ALU_INDEX0, "Global HSR ALU Value Index",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0040,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Higher 32 bits of Destination MAC used to hash the Index Table."
    ),

    define_sw_reg(
        GLB_HSR_ALU_INDEX1, "Global HSR ALU Value Index 1",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0044,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Lower 16 bits of Destination MAC and Lower 16 bits of Source MAC used to hash the Index Table."
    ),

    define_sw_reg(
        GLB_HSR_ALU_INDEX2, "Global HSR ALU Value Index 2",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0048,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Lower 32 bits of Source MAc address to hash the index table."
    ),

    define_sw_reg(
        GLB_HSR_ALU_INDEX3, "Global HSR ALU Value Index 3",
        FUNCTION_SPACE_GLOBAL_LUE, 0x004C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Path Index to hash the index table."
    ),

    define_sw_reg(
        GLB_HSR_ALU_CTL, "Global HSR ALU Access Control",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0050,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0xC000FF18, // Reserved mask.
        0x00000020, // Read only mask.
        0x3FFF00C0, // Misc mask.
        "HSR ALU table duplicate frames sequence information."
    ),

    define_sw_reg(
        GLB_HSR_ALU_VAL_A, "Global HSR ALU Value A",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0054,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x63FFFFF0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "HSR Path, Entry and Age count fields."
    ),

    define_sw_reg(
        GLB_HSR_ALU_VAL_B, "Global HSR ALU Value B",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0058,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Destination MAC Address bits for indexing."
    ),

    define_sw_reg(
        DLB_HSR_ALU_VAL_C, "Global HSR ALU Value C",
        FUNCTION_SPACE_GLOBAL_LUE, 0x005C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Destination and Source MAC Address bits for indexing."
    ),

    define_sw_reg(
        DLB_HSR_ALU_VAL_D, "Global HSR ALU Value D",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0060,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Source MAC Address  bits for indexing."
    ),

    define_sw_reg(
        DLB_HSR_ALU_VAL_E, "Global HSR ALU Value E",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0064,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Start Sequence number information."
    ),

    define_sw_reg(
        DLB_HSR_ALU_VAL_F, "Global HSR ALU Value E",
        FUNCTION_SPACE_GLOBAL_LUE, 0x0068,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Expected Sequence Number information."
    ),

    define_sw_reg(
        DLB_HSR_ALU_VAL_G, "Global HSR ALU Value G",
        FUNCTION_SPACE_GLOBAL_LUE, 0x006C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Out of sequence count information."
    ),

    define_sw_reg(
        GLB_SW_PTP_CTL, "Global Switch PTP Control",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0000,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x3F80, // Reserved mask.
        0x0000, // Read only mask.
        0x4059, // Misc mask.
        "PTP Clock settings."
    ),

    define_sw_reg(
        GLB_SW_RTC_PHASE, "Global Switch PTP RTC Clock Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0002,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFFF8, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Real time clock phase settings."
    ),

    define_sw_reg(
        GLB_SW_RTC_NAN_HW, "Global Switch PTP RTC Clock Nanosecond High Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0004,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Real time clock ns value."
    ),

    define_sw_reg(
        GLB_SW_RTC_NAN_LW, "Global Switch PTP RTC Clock Nanosecond Low Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0006,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Real time clock ns value."
    ),

    define_sw_reg(
        GLB_SW_RTC_SEC_HW, "Global Switch PTP RTC Clock Second High Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0008,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP real time clock seconds value."
    ),

    define_sw_reg(
        GLB_SW_RTC_SEC_LW, "Global Switch PTP RTC Clock Second Low Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x000A,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP real time clock seconds value."
    ),

    define_sw_reg(
        GLB_SW_RTC_SUB_HW, "Global PTP Clock Sub-Nanosecond Rate High Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x000C,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x4000, // Misc mask.
        "PTP clock Sub ns Rate value."
    ),

    define_sw_reg(
        GLB_SW_RTC_SUB_LW, "Global PTP Clock Sub-Nanosecond Rate Low Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x000E,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP clock Sub ns Rate value."
    ),

    define_sw_reg(
        GLB_SW_RTC_TMP_HW, "Global PTP Clock Temp Adjustment Duration High Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0010,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP clock temporary adjustment duration."
    ),

    define_sw_reg(
        GLB_SW_RTC_TMP_LW, "Global PTP Clock Temp Adjustment Duration Low Word",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0012,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP clock temporary adjustment duration."
    ),

    define_sw_reg(
        GLB_SW_PTP_MSG_CFG1, "Global PTP Message Configuration 1",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0014,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Mode select."
    ),

    define_sw_reg(
        GLB_SW_PTP_MSG_CFG2, "Global PTP Message Configuration 2",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0016,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xE448, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Message parameters."
    ),

    define_sw_reg(
        GLB_SW_PTP_DOM_VER, "Global PTP Domain and Version",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0018,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x1000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "PTP Version and Domain."
    ),

    define_sw_reg(
        GLB_SW_PTP_INDEX, "Global Switch PTP Unit Index",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0020,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFF0FEFC, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP GPIO, Trigger, Time stamp index pointers."
    ),

    define_sw_reg(
        GLB_SW_GPIO_STS_MON0, "Global GPIO Status Monitor 0",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0024,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0xFFF8FFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00070007, // Misc mask.
        "Event Trigger Output Status."
    ),

    define_sw_reg(
        GLB_SW_GPIO_STS_MON1, "Global GPIO Status Monitor 1",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0028,
        REGISTER_DWORD,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0xFFF8FFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00070007, // Misc mask.
        "Trigger Output and Time stamp unit interrupt status."
    ),

    define_sw_reg(
        GLB_SW_TS_CTL1, "Global Time stamp Status and Control 1",
        FUNCTION_SPACE_GLOBAL_PTP, 0x002C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFC00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Time stamp Status."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_NS, "Global Trigger Output Unit Target Time Nanosecond",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0030,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xC0000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output time in ns."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_SEC, "Global Trigger Output Unit Target Time Second",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0034,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger output in secs."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_CTL1, "Global Trigger Output Unit Control 1",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0038,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x30000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output unit parameters."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_CTL2, "Global Trigger Output Unit Control 2",
        FUNCTION_SPACE_GLOBAL_PTP, 0x003C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output unit parameters."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_CTL3, "Global Trigger Output Unit Control 3",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0040,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output unit parameters."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_CTL4, "Global Trigger Output Unit Control 4",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0044,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output unit parameters."
    ),

    define_sw_reg(
        GLB_SW_TRG_OUT_CTL5, "Global Trigger Output Unit Control 5",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0048,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFF000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger Output unit parameters."
    ),

    define_sw_reg(
        GLB_SW_TS_CTL2, "Global Time stamp Status and Control2",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0050,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFE0F01C, // Reserved mask.
        0x001F0000, // Read only mask.
        0x00000000, // Misc mask.
        "Time stamp event count, input unit, Rising/Falling Edge Detection settings and status."
    ),

    define_sw_reg(
        GLB_SW_TS1_SAMP_NS, "Global Timestamp 1st Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0054,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "First Sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS1_SAMP_SEC, "Global Timestamp 1st Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0058,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "First Sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS1_SAMP_PHS, "Global Timestamp 1st Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x005C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "First sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS2_SAMP_NS, "Global Timestamp 2nd Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0060,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Second sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS2_SAMP_SEC, "Global Timestamp 2nd Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0064,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Second sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS2_SAMP_PHS, "Global Timestamp 2nd Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0068,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Second sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS3_SAMP_NS, "Global Timestamp 3rd Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x006C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Third sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS3_SAMP_SEC, "Global Timestamp 3rd Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0070,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Third sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS3_SAMP_PHS, "Global Timestamp 3rd Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0074,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Third sample time for time stamp inn sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS4_SAMP_NS, "Global Timestamp 4th Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0078,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Fourth sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS4_SAMP_SEC, "Global Timestamp 4th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x007C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Fourth sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS4_SAMP_PHS, "Global Timestamp 4th Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0080,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Fourth sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS5_SAMP_NS, "Global Timestamp 5th Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0084,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Fifth sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS5_SAMP_SEC, "Global Timestamp 5th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0088,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Fifth sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS5_SAMP_PHS, "Global Timestamp 5th Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x008C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Fifth sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS6_SAMP_NS, "Global Timestamp 6th Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0090,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Sixth sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS6_SAMP_SEC, "Global Timestamp 6th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0094,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Sixth sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS6_SAMP_PHS, "Global Timestamp 6th Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x0098,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Sixth sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS7_SAMP_NS, "Global Timestamp 7th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x009C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Seventh sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS7_SAMP_SEC, "Global Timestamp 7th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00A0,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Seventh sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS7_SAMP_PHS, "Global Timestamp 7th Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00A4,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Seventh sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_TS8_SAMP_NS, "Global Timestamp 8th Sample Time Nanoseconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00A8,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x80000000, // Reserved mask.
        0x7FFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Eighth sample time for time stamp in ns."
    ),

    define_sw_reg(
        GLB_SW_TS8_SAMP_SEC, "Global Timestamp 8th Sample Time Seconds",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00AC,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Eighth sample time for time stamp in seconds."
    ),

    define_sw_reg(
        GLB_SW_TS8_SAMP_PHS, "Global Timestamp 8th Sample Time Phase",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00B0,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFFF8, // Reserved mask.
        0x00000007, // Read only mask.
        0x00000000, // Misc mask.
        "Eighth sample time for time stamp in sub ns."
    ),

    define_sw_reg(
        GLB_SW_PTP_SDOID, "Global PTP One Step Port SDOID",
        FUNCTION_SPACE_GLOBAL_PTP, 0x00B4,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x000F0000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP One step Sdoid."
    ),

    define_sw_reg(
        GLB_HSR_MAP, "Global HSR Map",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0040,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFFFFFF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Ports part of HSR Network."
    ),

    define_sw_reg(
        GLB_HSR_AME_CTL0, "Global HSR AME Control 0",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0044,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x40, // Reserved mask.
        0x80, // Read only mask.
        0x00, // Misc mask.
        "HSR Learning and lookup Parameters."
    ),

    define_sw_reg(
        GLB_HSR_AME_CTL1, "Global HSR AME Control 1",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0045,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x58, // Reserved mask.
        0x00, // Read only mask.
        0x20, // Misc mask.
        "HSR learning and lookup parameters."
    ),

    define_sw_reg(
        GLB_HSR_AME_AGE, "Global HSR AME Period Age",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0048,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xFE000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Age period for HSR lookup entry."
    ),

    define_sw_reg(
        GLB_HSR_AME_INT_STS, "Global HSR AME Interrupt Status",
        FUNCTION_SPACE_GLOBAL_HSR, 0x004C,
        REGISTER_BYTE,
        REGISTER_GLOBAL | REGISTER_WRITE_ONE_CLEAR,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x07, // Misc mask.
        "Learn fail, Full, Write fail Interrupt status."
    ),

    define_sw_reg(
        GLB_HSR_AME_INT_MSK, "Global HSR AME Interrupt Mask",
        FUNCTION_SPACE_GLOBAL_HSR, 0x004D,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Learn fail, full, write fail interrupt mask."
    ),

    define_sw_reg(
        GLB_HSR_AME_ENT_IDX0, "Global HSR AME Entry Index 0",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0050,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFC00, // Reserved mask.
        0x03FF, // Read only mask.
        0x0000, // Misc mask.
        "Entry address of ALU write/Address of Failed ALU write."
    ),

    define_sw_reg(
        GLB_HSR_AME_ENT_IDX1, "Global HSR AME Entry Index 1",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0052,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x00FF, // Read only mask.
        0x0000, // Misc mask.
        "Address that caused learning failure."
    ),

    define_sw_reg(
        GLB_HSR_AME_ENT_IDX2, "Global HSR AME Entry Index 2",
        FUNCTION_SPACE_GLOBAL_HSR, 0x0054,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFF00, // Reserved mask.
        0x00FF, // Read only mask.
        0x0000, // Misc mask.
        "CPU accessed  entry address."
    ),

    define_sw_reg(
        VPHY_BASIC_CTRL, "Virtual PHY Basic Control",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0000,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x003F, // Reserved mask.
        0x0000, // Read only mask.
        0x8200, // Misc mask.
        "PHY basic configurations, speed, duplex, etc"
    ),

    define_sw_reg(
        VPHY_BASIC_STATUS, "Virtual PHY Basic Status",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0004,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x0080, // Reserved mask.
        0x7F7F, // Read only mask.
        0x8000, // Misc mask.
        "PHY basic status, speed, duplex, etc"
    ),

    define_sw_reg(
        VPHY_PHY_ID_MSB, "Virtual PHY Identification MSB Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0008,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "PHY OUI MSB"
    ),

    define_sw_reg(
        VPHY_PHY_ID_LSB, "Virtual PHY Identification LSB Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x000C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "PHY OUI LSB"
    ),

    define_sw_reg(
        VPHY_PHY_AUTONEG_ADVT, "Virtual PHY Auto-Negotiation Advertisement",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0010,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x5000, // Reserved mask.
        0xA200, // Read only mask.
        0x0000, // Misc mask.
        "PHY autoneg advertisement info"
    ),

    define_sw_reg(
        VPHY_PHY_AUTONEG_LINK_PARTNER_BASE_PAGE_ABILITY, "Virtual PHY Auto-Negotiation Link Partner Base Page Ability Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0014,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x1000, // Reserved mask.
        0xEFFF, // Read only mask.
        0x0000, // Misc mask.
        "PHY autoneg link partner ability info"
    ),

    define_sw_reg(
        VPHY_PHY_AUTONEG_EXPANSION, "Virtual PHY Auto-Negotiation Expansion Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0018,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0xFFC0, // Reserved mask.
        0x003F, // Read only mask.
        0x0000, // Misc mask.
        "PHY autoneg expansion info"
    ),

    define_sw_reg(
        VPHY_PHY_MASTER_SLAVE_CTRL, "Virtual PHY Master Slave Control Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0024,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x00FF, // Reserved mask.
        0xE100, // Read only mask.
        0x0000, // Misc mask.
        "PHY master slave control"
    ),

    define_sw_reg(
        VPHY_PHY_MASTER_SLAVE_STATUS, "Virtual PHY Master Slave Status Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0028,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0600, // Reserved mask.
        0xF8FF, // Read only mask.
        0x0000, // Misc mask.
        "PHY master slave status"
    ),

    define_sw_reg(
        VPHY_PHY_EXTENDED_STATUS, "Virtual PHY Extended Status Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x003C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0FFF, // Reserved mask.
        0xF000, // Read only mask.
        0x0000, // Misc mask.
        "PHY extended status info"
    ),

    define_sw_reg(
        VPHY_PHY_DEVAD_CFG0, "Virtual PHY DEVAD Configuration 0 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0040,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x6060, // Reserved mask.
        0x0000, // Read only mask.
        0x8080, // Misc mask.
        "PHY DEVAD configuration 0"
    ),

    define_sw_reg(
        VPHY_PHY_DEVAD_CFG1, "Virtual PHY DEVAD Configuration 1 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0044,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x6060, // Reserved mask.
        0x0000, // Read only mask.
        0x8080, // Misc mask.
        "PHY DEVAD configuration 1"
    ),

    define_sw_reg(
        VPHY_PHY_DEVAD_CFG2, "Virtual PHY DEVAD Configuration 2 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0048,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0x6060, // Reserved mask.
        0x0000, // Read only mask.
        0x8080, // Misc mask.
        "PHY DEVAD configuration 2"
    ),

    define_sw_reg(
        VPHY_PHY_DEVAD_CFG3, "Virtual PHY DEVAD Configuration 3 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x004C,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0xFF30, // Reserved mask.
        0x0000, // Read only mask.
        0x0080, // Misc mask.
        "PHY DEVAD configuration 3"
    ),

    define_sw_reg(
        VPHY_SMI_ADDR, "Virtual PHY SMI Address Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0050,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "SMI indirect address"
    ),

    define_sw_reg(
        VPHY_SMI_DATA0, "Virtual PHY SMI Data0 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0054,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "SMI indirect data0"
    ),

    define_sw_reg(
        VPHY_SMI_DATA1, "Virtual PHY SMI Data0 Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0058,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "SMI indirect data1"
    ),

    define_sw_reg(
        VPHY_IND_ADDR, "Virtual PHY Indirect Address Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x005C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "VPHY indirect address"
    ),

    define_sw_reg(
        VPHY_IND_DATA, "Virtual PHY Indirect Data Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0060,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "VPHY indirect data"
    ),

    define_sw_reg(
        VPHY_IND_CTRL, "Virtual PHY Indirect Control Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x0068,
        REGISTER_WORD,
        REGISTER_GLOBAL | REGISTER_SELF_CLEAR,
        0xFFFC, // Reserved mask.
        0x0000, // Read only mask.
        0x0001, // Misc mask.
        "VPHY indirect control"
    ),

    define_sw_reg(
        VPHY_PHY_SPECIAL_CTRL, "Virtual PHY Special Control Status Register",
        FUNCTION_SPACE_GLOBAL_VPHY, 0x007C,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0C63, // Reserved mask.
        0x031C, // Read only mask.
        0x0000, // Misc mask.
        "VPHY special control"
    ),

    define_sw_reg(
        GLB_SW_PG_CTL0, "Global Switch Packet Generator Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0000,
        REGISTER_BYTE,
        REGISTER_GLOBAL,
        0x1F, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Packet Generator enable and start, Loop back enable."
    ),

    define_sw_reg(
        GLB_SW_PG_CRC, "Global Switch Packet Generator CRC Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0002,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x7F00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "CRC error insertion enable, CRC error frequency."
    ),

    define_sw_reg(
        GLB_SW_PG_LEN, "Global Switch Packet Generator Length",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0004,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0xC000FF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Packet size."
    ),

    define_sw_reg(
        GLB_SW_PG_NUM, "Global Switch Packet Generator Number",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0008,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Number of packets to generate."
    ),

    define_sw_reg(
        GLB_SW_PG_IPG, "Global Switch Packet Generator IPG",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x000C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x3F000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "IPG settings."
    ),

    define_sw_reg(
        GLB_SW_PG_DA_CTL0, "Global Switch Packet Generator DA Control 0",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0010,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Destination Address settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_DA_CTL1, "Global Switch Packet Generator DA Control 1",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0014,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Destination address settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_SA_CTL0, "Global Switch Packet Generator SA Control 0",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0018,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Source address settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_SA_CTL1, "Global Switch Packet Generator SA Control 1",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x001C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Source Address settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_VLAN_CTL, "Global Switch Packet Generator VLAN Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0020,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x700000C0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "VLAN configuration for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_TYPE_LEN_CTL, "Global Switch Packet Generator Type/Length Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0024,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x000000FF, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Ethertype configuration for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_CTL, "Global Switch Packet Generator L3 Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0028,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x38FF0000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DATA0, "Global Switch Packet Generator L3 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x002C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 Data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DATA1, "Global Switch Packet Generator L3 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0030,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DATA2, "Global Switch Packet Generator L3 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0034,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DATA3, "Global Switch Packet Generator L3 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0038,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DATA4, "Global Switch Packet Generator L3 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x003C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L3 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_DIP, "Global Switch Packet Generator IP Destination Address",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0040,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "IPv4 Destination address for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_SIP, "Global Switch Packet Generator IP Source Address",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0044,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "IPv4 Source Address for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L3_INC_CNT, "Global Switch Packet Generator L3 Incremental Count",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0048,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Source IP, Destination IP, TOS, IP protocol increment count."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_CTL, "Global Switch Packet Generator L4 Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x004C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x38FE00F0, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 settings for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DATA0, "Global Switch Packet Generator L4 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0050,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DATA1, "Global Switch Packet Generator L4 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0054,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DATA2, "Global Switch Packet Generator L4 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0058,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DATA3, "Global Switch Packet Generator L4 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x005C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DATA4, "Global Switch Packet Generator L4 Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0060,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "L4 data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_DPORT, "Global Switch Packet Generator L4 Destination Port",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0064,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "L4 destination port number for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_SPORT, "Global Switch Packet Generator L4 Source Port",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0066,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "L4 Source port number for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_L4_INC_CNT, "Global Switch Packet Generator L4 Incremental Count",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0068,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "L4 source port, destination port increment number."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_CTL, "Global Switch Packet Generator Payload Control",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x006A,
        REGISTER_WORD,
        REGISTER_GLOBAL,
        0x1FC0, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Payload mode and size configuration."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA0, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x006C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Payload data for  generated  packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA1, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0070,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA2, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0074,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA3, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0078,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA4, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x007C,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA5, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0080,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data  for generated  packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA6, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0084,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        GLB_SW_PG_PL_DATA7, "Global Switch Packet Generator Payload Manual Data",
        FUNCTION_SPACE_GLOBAL_PACKET_GENERATOR, 0x0088,
        REGISTER_DWORD,
        REGISTER_GLOBAL,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "payload data for generated packet."
    ),

    define_sw_reg(
        PORT_DEF_TAG0, "Port Default Tag 0",
        FUNCTION_SPACE_PORT_OPERATION, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port Default VLAN Tag."
    ),

    define_sw_reg(
        PORT_DEF_TAG1, "Port Default Tag 1",
        FUNCTION_SPACE_PORT_OPERATION, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port Default VLAN Tag."
    ),

    define_sw_reg(
        PORT_AVB_SR_CL1_T0, "Port AVB SR Class 1 Tag 0",
        FUNCTION_SPACE_PORT_OPERATION, 0x0004,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "AVB SR Class 1 VLAN Tag."
    ),

    define_sw_reg(
        PORT_AVB_SR_CL1_T1, "Port AVB SR Class 1 Tag 1",
        FUNCTION_SPACE_PORT_OPERATION, 0x0005,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "AVB SR Class 1 VLAN Tag."
    ),

    define_sw_reg(
        PORT_AVB_SR_CL2_T0, "Port AVB SR Class 2 Tag 0",
        FUNCTION_SPACE_PORT_OPERATION, 0x0006,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "AVB SR Class 2 VLAN tag."
    ),

    define_sw_reg(
        PORT_AVB_SR_CL2_T1, "Port AVB SR Class 2 Tag 1",
        FUNCTION_SPACE_PORT_OPERATION, 0x0007,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "AVB SR Class 2 VLAN Tag"
    ),

    define_sw_reg(
        PORT_AVB_CL1_TYPE, "Port AVB SR Class 1 Type",
        FUNCTION_SPACE_PORT_OPERATION, 0x0008,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "SR class 1 Type."
    ),

    define_sw_reg(
        PORT_AVB_CL2_TYPE, "Port AVB SR Class 2 Type",
        FUNCTION_SPACE_PORT_OPERATION, 0x000A,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "SR Class 2 Type."
    ),

    define_sw_reg(
        PORT_INT_STS, "Port Interrupt Status",
        FUNCTION_SPACE_PORT_OPERATION, 0x001B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xC0, // Reserved mask.
        0x3F, // Read only mask.
        0x00, // Misc mask.
        "Port interrupts."
    ),

    define_sw_reg(
        PORT_INT_MSK, "Port Interrupt Mask",
        FUNCTION_SPACE_PORT_OPERATION, 0x001F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xC0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port interrupt mask."
    ),

    define_sw_reg(
        PORT_OP_CTL0, "Port Operation Control 0",
        FUNCTION_SPACE_PORT_OPERATION, 0x0020,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x08, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Loopback, timestamp insertion, tail tag and egress queue split controls."
    ),

    define_sw_reg(
        PORT_OP_CTL1, "Port Operation Control 1",
        FUNCTION_SPACE_PORT_OPERATION, 0x0021,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFC, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "SRP enable."
    ),

    define_sw_reg(
        PORT_OP_STS, "Port Operation Status",
        FUNCTION_SPACE_PORT_OPERATION, 0x0030,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xE0, // Reserved mask.
        0x1F, // Read only mask.
        0x00, // Misc mask.
        "Port speed, Duplex, Flow control status."
    ),

    define_sw_reg(
        PORT_PART_NET, "Port Partial Network",
        FUNCTION_SPACE_PORT_OPERATION, 0x0040,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port partial network configuration."
    ),

    define_sw_reg(
        PORT_SGMII_ADDR, "Port SGMII Address",
        FUNCTION_SPACE_PORT_SGMII, 0x0000,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFF600000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "SGMII Address."
    ),

    define_sw_reg(
        PORT_SGMII_DATA, "Port SGMII Data",
        FUNCTION_SPACE_PORT_SGMII, 0x0004,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFF0000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "SGMII Data."
    ),

    define_sw_reg(
        PORT_XMII_CTL0, "Port XMII Control 0",
        FUNCTION_SPACE_PORT_RGMII, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x04, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "MAC Port Speed,Duplex and Flow control configuration. "
    ),

    define_sw_reg(
        PORT_XMII_CTL1, "Port XMII Control 1",
        FUNCTION_SPACE_PORT_RGMII, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress/Egress Internal delay, MII Mode and interface select."
    ),

    define_sw_reg(
        PORT_XMII_CTL2, "Port XMII Control 2",
        FUNCTION_SPACE_PORT_RGMII, 0x0002,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "RGMII Rx Status."
    ),

    define_sw_reg(
        PORT_XMII_CTL3, "Port XMII Control 3",
        FUNCTION_SPACE_PORT_RGMII, 0x0003,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF0, // Reserved mask.
        0x0F, // Read only mask.
        0x00, // Misc mask.
        "Duplex, Link status and Clock speed."
    ),

    define_sw_reg(
        PORT_XMII_CTL4, "Port XMII Control 4",
        FUNCTION_SPACE_PORT_RGMII, 0x0004,
        REGISTER_WORD,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x8000, // Misc mask.
        "Rx DLL and Tune settings."
    ),

    define_sw_reg(
        PORT_XMII_CTL5, "Port XMII Control 5",
        FUNCTION_SPACE_PORT_RGMII, 0x0006,
        REGISTER_WORD,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x8000, // Misc mask.
        "Tx DLL and Tune settings."
    ),

    define_sw_reg(
        MAC_CTL0, "Port MAC Control 0",
        FUNCTION_SPACE_PORT_MAC, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Frame Length check, Jumbo enable and Broadcast storm protection enable."
    ),

    define_sw_reg(
        MAC_CTL1, "Port MAC Control 1",
        FUNCTION_SPACE_PORT_MAC, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF6, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Back pressure and Pass bad frames enable."
    ),

    define_sw_reg(
        EEE_CTL0, "Port Energy Efficient Ethernet Control 0",
        FUNCTION_SPACE_PORT_MAC, 0x0002,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x3F, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "100BT and 1000BT Energy efficient ethernet disable."
    ),

    define_sw_reg(
        RLIMT_CTL, "Port Rate Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0003,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress rate limiting parameters."
    ),

    define_sw_reg(
        MAX_FR_SIZE, "Port Receive Maximum Frame Size",
        FUNCTION_SPACE_PORT_MAC, 0x0004,
        REGISTER_WORD,
        REGISTER_PORT,
        0xC000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Maximum Frame Length."
    ),

    define_sw_reg(
        EEE_CTL1, "Port Energy Efficient Ethernet Control 1",
        FUNCTION_SPACE_PORT_MAC, 0x0008,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "CRS Mode enable, PHY EEE LPI recovery time."
    ),

    define_sw_reg(
        PRI0_IN_RLIMIT_CTL, "Port Priority 0 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0010,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 0 frames."
    ),

    define_sw_reg(
        PRI1_IN_RLIMIT_CTL, "Port Priority 1 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0011,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 1 frames."
    ),

    define_sw_reg(
        PRI2_IN_RLIMIT_CTL, "Port Priority 2 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0012,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 2 frames. "
    ),

    define_sw_reg(
        PRI3_IN_RLIMIT_CTL, "Port Priority 3 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0013,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 3 frames."
    ),

    define_sw_reg(
        PRI4_IN_RLIMIT_CTL, "Port Priority 4 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0014,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 4 frames."
    ),

    define_sw_reg(
        PRI5_IN_RLIMIT_CTL, "Port Priority 5 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0015,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 5 frames."
    ),

    define_sw_reg(
        PRI6_IN_RLIMIT_CTL, "Port Priority 6 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0016,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 6 frames."
    ),

    define_sw_reg(
        PRI7_IN_RLIMIT_CTL, "Port Priority 7 Ingress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0017,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Ingress data rate limit for priority 7 frames."
    ),

    define_sw_reg(
        QUE0_EG_RLIMIT_CTL, "Port Queue 0 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0020,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 0 frames."
    ),

    define_sw_reg(
        QUE1_EG_RLIMIT_CTL, "Port Queue 1 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0021,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 1 frames."
    ),

    define_sw_reg(
        QUE2_EG_RLIMIT_CTL, "Port Queue 2 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0022,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 2 frames."
    ),

    define_sw_reg(
        QUE3_EG_RLIMIT_CTL, "Port Queue 3 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0023,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 3 frames. "
    ),

    define_sw_reg(
        QUE4_EG_RLIMIT_CTL, "Port Queue 4 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0024,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 4 frames."
    ),

    define_sw_reg(
        QUE5_EG_RLIMIT_CTL, "Port Queue 5 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0025,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 5 frames."
    ),

    define_sw_reg(
        QUE6_EG_RLIMIT_CTL, "Port Queue 6 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0026,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit for queue 6 frames."
    ),

    define_sw_reg(
        QUE7_EG_RLIMIT_CTL, "Port Queue 7 Egress Limit Control",
        FUNCTION_SPACE_PORT_MAC, 0x0027,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Egress data rate limit  for queue 7 frames."
    ),

    define_sw_reg(
        MIB_CTL_STS, "Port MIB Control and Status",
        FUNCTION_SPACE_PORT_MIB_COUNTERS, 0x0000,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x3C00FFF0, // Reserved mask.
        0xC000000F, // Read only mask.
        0x02000000, // Misc mask.
        "MIB Counter Overflow status, Read enable, Flush and Freeze enable, MIB Index."
    ),

    define_sw_reg(
        MIB_DATA, "Port MIB Data",
        FUNCTION_SPACE_PORT_MIB_COUNTERS, 0x0004,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "MIB Counter value."
    ),

    define_sw_reg(
        ADR0, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR1, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR2, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0002,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR3, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0003,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR4, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0004,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR5, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0005,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR6, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0006,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR7, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0007,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR8, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0008,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR9, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0009,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR10, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR11, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR12, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR13, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR14, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR15, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x000F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR16, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0010,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR17, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0011,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR18, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0012,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR19, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0013,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR20, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0014,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR21, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0015,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR22, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0016,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR23, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0017,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR24, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0018,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR25, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0019,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR26, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR27, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR28, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR29, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR30, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR31, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x001F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR32, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0020,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR33, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0021,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR34, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0022,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR35, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0023,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR36, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0024,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR37, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0025,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR38, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0026,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR39, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0027,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR40, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0028,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR41, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0029,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR42, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR43, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR44, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR45, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR46, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR47, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x002F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Mask."
    ),

    define_sw_reg(
        ADR48, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0030,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR49, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0031,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR50, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0032,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR51, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0033,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR52, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0034,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR53, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0035,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR54, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0036,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR55, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0037,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR56, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0038,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR57, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0039,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR58, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR59, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR60, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR61, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR62, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR63, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x003F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR64, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0040,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR65, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0041,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR66, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0042,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR67, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0043,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR68, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0044,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR69, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0045,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR70, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0046,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR71, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0047,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR72, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0048,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR73, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0049,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR74, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR75, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR76, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR77, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR78, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR79, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x004F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR80, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0050,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR81, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0051,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR82, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0052,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR83, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0053,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR84, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0054,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR85, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0055,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR86, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0056,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR87, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0057,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR88, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0058,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR89, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x0059,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR90, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR91, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR92, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR93, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR94, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        ADR95, "Port ACL Data",
        FUNCTION_SPACE_PORT_ACL, 0x005F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Data."
    ),

    define_sw_reg(
        AAR0, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0060,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR1, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0061,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR2, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0062,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR3, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0063,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR4, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0064,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR5, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0065,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x7F, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR6, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0066,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFF, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR7, "Port ACL Action",
        FUNCTION_SPACE_PORT_ACL, 0x0067,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFF, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR, "Port ACL Action",  // Part a.
        FUNCTION_SPACE_PORT_ACL, 0x0060,
        REGISTER_QWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Value programmed into Action RAM."
    ),

    define_sw_reg(
        AAR_b, NULL,  // Part b.
        0, 0,
        0,
        0,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        NULL
    ),

    define_sw_reg(
        ABER0, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0068,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER1, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0069,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER2, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006A,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER3, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006B,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER4, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER5, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006D,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER6, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006E,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER7, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x006F,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER8, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0070,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER9, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0071,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER10, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0072,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER11, "Port ACl Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0073,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER12, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0074,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ABER13, "Port ACL Byte Enable",
        FUNCTION_SPACE_PORT_ACL, 0x0075,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Byte Enable."
    ),

    define_sw_reg(
        ARACR, "Port ACL Access Control",
        FUNCTION_SPACE_PORT_ACL, 0x0078,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0xE0100000, // Reserved mask.
        0x00002000, // Read only mask.
        0x08000000, // Misc mask.
        "ACL Rule shift, Flush and Rule Valid bit enable."
    ),

    define_sw_reg(
        PCTRL, "Port ACL Parser Control",
        FUNCTION_SPACE_PORT_ACL, 0x007C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x0000000F, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "ACL Key format, Key Type, Frame Field to be extracted."
    ),

    define_sw_reg(
        FR_COUNT0, "Port ACL Frame Counterx",
        FUNCTION_SPACE_PORT_ACL, 0x0080,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0xFFFFFFFF, // Misc mask.
        "ACL Rule Match Counter 0."
    ),

    define_sw_reg(
        FR_COUNT1, "Port ACL Frame Counterx",
        FUNCTION_SPACE_PORT_ACL, 0x0084,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0xFFFFFFFF, // Misc mask.
        "ACL Rule Match Counter 1."
    ),

    define_sw_reg(
        FR_COUNT2, "Port ACL Frame Counterx",
        FUNCTION_SPACE_PORT_ACL, 0x0088,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0xFFFFFFFF, // Misc mask.
        "ACL Rule Match Counter 2."
    ),

    define_sw_reg(
        FR_COUNT3, "Port ACL Frame Counterx",
        FUNCTION_SPACE_PORT_ACL, 0x008C,
        REGISTER_DWORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0xFFFFFFFF, // Misc mask.
        "ACL Rule Match Counter 3."
    ),

    define_sw_reg(
        NMATCH_HIGH, "Port ACL Negative Rule Match",
        FUNCTION_SPACE_PORT_ACL, 0x0094,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Inverts the TCAM lookup result output."
    ),

    define_sw_reg(
        NMATCH_LOW, "Port ACL Negative Rule Match",
        FUNCTION_SPACE_PORT_ACL, 0x0098,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Inverts the TCAM lookup result output."
    ),

    define_sw_reg(
        NMATCH, "Port ACL Negative Rule Match",  // Part a.
        FUNCTION_SPACE_PORT_ACL, 0x0094,
        REGISTER_QWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Inverts the TCAM lookup result output."
    ),

    define_sw_reg(
        NMATCH_b, NULL,  // Part b.
        0, 0,
        0,
        0,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        NULL
    ),

    define_sw_reg(
        ACL_INT_STS, "Port ACL Interrupt Status",
        FUNCTION_SPACE_PORT_ACL, 0x00A0,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xE0, // Reserved mask.
        0x00, // Read only mask.
        0x1F, // Misc mask.
        "ACL Counters Overflow and Operation done Interrupt."
    ),

    define_sw_reg(
        ACL_INT_MASK, "Port ACL Interrupt Mask",
        FUNCTION_SPACE_PORT_ACL, 0x00A2,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xE0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Counters Overflow and Operation done Interrupt Mask."
    ),

    define_sw_reg(
        PORT_SPARE, "Port Spare",
        FUNCTION_SPACE_PORT_ACL, 0x00C0,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Spare Register."
    ),

    define_sw_reg(
        TCAM_BIST0, "PORT TCAM BIST 0",
        FUNCTION_SPACE_PORT_ACL, 0x00D0,
        REGISTER_WORD,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x0030, // Reserved mask.
        0xF9C0, // Read only mask.
        0x0001, // Misc mask.
        "ACL BIST settings."
    ),

    define_sw_reg(
        TCAM_BIST1, "PORT TCAM BIST 1",
        FUNCTION_SPACE_PORT_ACL, 0x00D2,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xC0, // Reserved mask.
        0x3F, // Read only mask.
        0x00, // Misc mask.
        "ACL BIST settings."
    ),

    define_sw_reg(
        TCAM_BIST2, "PORT TCAM BIST 2",
        FUNCTION_SPACE_PORT_ACL, 0x00D3,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "ACL BIST settings."
    ),

    define_sw_reg(
        TCAM_BIST3, "PORT TCAM BIST 3",
        FUNCTION_SPACE_PORT_ACL, 0x00D4,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xC0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL BIST settings."
    ),

    define_sw_reg(
        TCAM_BITMAP, "PORT TCAM BIST BITMAP",  // Part a.
        FUNCTION_SPACE_PORT_ACL, 0x00E0,
        REGISTER_DQWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Data Comparison Result."
    ),

    define_sw_reg(
        TCAM_BITMAP_b, NULL,  // Part b.
        0, 0,
        0,
        0,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        NULL
    ),

    define_sw_reg(
        TCAM_BITMAP_c, NULL,  // Part c.
        0, 0,
        0,
        0,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        NULL
    ),

    define_sw_reg(
        TCAM_BITMAP_d, NULL,  // Part d.
        0, 0,
        0,
        0,
        0x00000000, // Reserved mask.
        0xFFFFFFFF, // Read only mask.
        0x00000000, // Misc mask.
        NULL
    ),

    define_sw_reg(
        PORT_RX_MIRROR_CTL, "Port Receive Mirroring Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x9D, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Transmit/ Receive Monitoring and Monitor Port controls."
    ),

    define_sw_reg(
        PORT_RX_PRI_CTL, "Port Receive Priority Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x20, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Priority Classification settings."
    ),

    define_sw_reg(
        PORT_RX_MAC_CTL, "Port Receive MAC Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0002,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x40, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "VLAN Hopping Detection, Discard Untagged/Tagged packets, Port Default Priority settings."
    ),

    define_sw_reg(
        PORT_RX_AUTH_CTL, "Port Receive Authentication Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0003,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "ACL Enable."
    ),

    define_sw_reg(
        PORT_RX_MAC_CTL2, "Port Receive MAC Control2",
        FUNCTION_SPACE_PORT_INGRESS, 0x0004,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "When set the RX MAC drops priority tagged frames."
    ),

    define_sw_reg(
        PORT_RX_TC_MAP, "Port Receive Traffic Class Map",
        FUNCTION_SPACE_PORT_INGRESS, 0x0008,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Priority to Queue Mapping."
    ),

    define_sw_reg(
        PORT_MRI_PSFP_COLOR_REMAP_0, "Port MRI PSFP Color Remap X",
        FUNCTION_SPACE_PORT_INGRESS, 0x0010,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PSFP Color Remap configuration."
    ),

    define_sw_reg(
        PORT_MRI_PSFP_COLOR_REMAP_1, "Port MRI PSFP Color Remap X",
        FUNCTION_SPACE_PORT_INGRESS, 0x0014,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PSFP Color Remap configuration."
    ),

    define_sw_reg(
        PORT_MRI_PSFP_COLOR_REMAP_2, "Port MRI PSFP Color Remap X",
        FUNCTION_SPACE_PORT_INGRESS, 0x0018,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PSFP Color Remap configuration."
    ),

    define_sw_reg(
        PORT_MRI_PSFP_COLOR_REMAP_3, "Port MRI PSFP Color Remap X",
        FUNCTION_SPACE_PORT_INGRESS, 0x001C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PSFP Color Remap configuration."
    ),

    define_sw_reg(
        PORT_RX_QCI_PTR, "Port Receive Qci Pointer",
        FUNCTION_SPACE_PORT_INGRESS, 0x0050,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "QCI Gate/Meter ID."
    ),

    define_sw_reg(
        PORT_RX_PSFP, "Port Receive PSFP",
        FUNCTION_SPACE_PORT_INGRESS, 0x0054,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFFC4, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Color Remap Enable, Counter Reset and PSFP Enable."
    ),

    define_sw_reg(
        PORT_RX_QCI_METER_CTL, "Port Receive Qci Metering Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0060,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFC005, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Remap Priority settings."
    ),

    define_sw_reg(
        PORT_RX_QCI_METER_SR, "Port Receive Qci Metering Stream Rate",
        FUNCTION_SPACE_PORT_INGRESS, 0x0064,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Committed information Rate and Peak information rate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_METER_BS, "Port Receive Qci Metering Burst Size Rate",
        FUNCTION_SPACE_PORT_INGRESS, 0x0068,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Committed burst size and peak burst size for  the queue pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_CTL, "Port Receive Qci Filtering Stream Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0070,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x0000E005, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "QCI settings."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FM, "Port Receive Qci Filtering Stream Frames Matched",
        FUNCTION_SPACE_PORT_INGRESS, 0x0074,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Frames match count for the stream filter pointed by the QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FPG, "Port Receive Qci Filtering Stream Frames Passed Gate",
        FUNCTION_SPACE_PORT_INGRESS, 0x0078,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Frames passed count for a stream gate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FNPG, "Port Receive Qci Filtering Stream Frames Not Passed Gate",
        FUNCTION_SPACE_PORT_INGRESS, 0x007C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Frames Not passed count for a stream gate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FPMAX, "Port Receive Qci Filtering Stream Frames Passed Max SDU",
        FUNCTION_SPACE_PORT_INGRESS, 0x0080,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Frames passed Max SDU  for a stream gate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FNPMAX, "Port Receive Qci Filtering Stream Frames Not Passed Max SDU",
        FUNCTION_SPACE_PORT_INGRESS, 0x0084,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Frames Not passed Max SDU  for a stream gate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_RX_QCI_FS_FD, "Port Receive Qci Filtering Stream Frames Dropped",
        FUNCTION_SPACE_PORT_INGRESS, 0x0088,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFF00000, // Reserved mask.
        0x000FFFFF, // Read only mask.
        0x00000000, // Misc mask.
        "Number of dropped frames count for a stream gate pointed by QCI ID."
    ),

    define_sw_reg(
        PORT_STREAM_CNT_STS, "Port Receive Stream Counter Overflow Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x008C,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xC0, // Reserved mask.
        0x00, // Read only mask.
        0x3F, // Misc mask.
        "QCI Overflow status."
    ),

    define_sw_reg(
        PORT_RX_GCTRL, "Port Receive Gate Control",
        FUNCTION_SPACE_PORT_INGRESS, 0x0090,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x55, // Reserved mask.
        0x00, // Read only mask.
        0x80, // Misc mask.
        "QCI Gate control list configuration."
    ),

    define_sw_reg(
        PORT_RX_GATE_ST_NS, "Port Receive Gate Control Start Time Nanosecond",
        FUNCTION_SPACE_PORT_INGRESS, 0x0094,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xC0000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "QCI Cycle Start time in ns."
    ),

    define_sw_reg(
        PORT_RX_GATE_ST_SEC, "Port Receive Gate Control Start Time Second",
        FUNCTION_SPACE_PORT_INGRESS, 0x0098,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "QCI Cycle start time in seconds."
    ),

    define_sw_reg(
        PORT_RX_GATE_CYC_TIME, "Port Receive Gate Control Cycle Time",
        FUNCTION_SPACE_PORT_INGRESS, 0x009C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "QCI Cycle time for the gate."
    ),

    define_sw_reg(
        PORT_RX_GLIST_LIDX, "Port Receive Gate Control List Last Index",
        FUNCTION_SPACE_PORT_INGRESS, 0x00A0,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xE0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Last gate index."
    ),

    define_sw_reg(
        PORT_RX_GLIST_EVNT_IDX, "Port Receive Gate Control List Event Index",
        FUNCTION_SPACE_PORT_INGRESS, 0x00A4,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xE0, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Current QCI Event Index."
    ),

    define_sw_reg(
        PORT_RX_GLIST_EVNT, "Port Receive Gate Control List Event",
        FUNCTION_SPACE_PORT_INGRESS, 0x00A8,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Internal priority value configuration."
    ),

    define_sw_reg(
        PORT_RX_CNT_OVR_INT_STS, "Port Stream Counter Overflow Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00C1,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0xFF, // Read only mask.
        0x00, // Misc mask.
        "QCI Counter overflow status for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_RX_CNT_OVR_INT_MSK, "Port Stream Counter Overflow Interrupt Mask",
        FUNCTION_SPACE_PORT_INGRESS, 0x00C2,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Counter overflow interrupt mask for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_METER_RED_INT_STS, "Port Meter Mark Red Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00C3,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0xFF, // Misc mask.
        "QCI Meter red interrupt status for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_METER_RED_INT_MSK, "Port Meter Mark Red Interrupt Mask",
        FUNCTION_SPACE_PORT_INGRESS, 0x00C7,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Meter Red interrupt mask for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_OVR_FR_INT_STS, "Port Stream Oversize Frame Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00CB,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0xFF, // Misc mask.
        "QCI Oversize frame interrupt status for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_OVR_FR_INT_MSK, "Port Stream Oversize Frame Interrupt Mask",
        FUNCTION_SPACE_PORT_INGRESS, 0x00CF,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Oversize frame interrupt status for streams 0 to 7."
    ),

    define_sw_reg(
        PORT_GATE_IVLD_RX_INT_STS, "Port Gate Invalid RX Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00D3,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x01, // Misc mask.
        "QCI invalid frames received interrupt status for gate 0."
    ),

    define_sw_reg(
        PORT_GATE_IVLD_RX_INT_MSK, "Port Gate Invalid RX Interrupt Mask",
        FUNCTION_SPACE_PORT_INGRESS, 0x00D7,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Invalid frames received interrupt mask for gate 0."
    ),

    define_sw_reg(
        PORT_GATE_OCT_EXCD_INT_STS, "Port Gate Octets Exceed RX Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00DB,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x01, // Misc mask.
        "QCI Octets exceeded interrupt status for gate 0."
    ),

    define_sw_reg(
        PORT_GATE_OCT_EXCD_INT_MSK, "Port Gate Octets Exceeded Interrupt Mask",
        FUNCTION_SPACE_PORT_INGRESS, 0x00DF,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "QCI Octets exceeded interrupt mask for gate 0."
    ),

    define_sw_reg(
        PORT_GATE_CFG_ERR_INT_STS, "Port Gate Configuration Error Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00E3,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x01, // Misc mask.
        "QCI Configuration error interrupt status."
    ),

    define_sw_reg(
        PORT_GATE_CFG_ERR_INT_MSK, "Port Gate Configuration Error Interrupt Status",
        FUNCTION_SPACE_PORT_INGRESS, 0x00E7,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0xFE, // Reserved mask.
        0x00, // Read only mask.
        0x01, // Misc mask.
        "QCI Configuration error interrupt status for gate 0."
    ),

    define_sw_reg(
        PORT_TX_QUE_IDX, "Port Transmit Queue Index",
        FUNCTION_SPACE_PORT_EGRESS, 0x0000,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Queue Index for configuration."
    ),

    define_sw_reg(
        PORT_TX_PVID_CTL, "Port Transmit PVID",
        FUNCTION_SPACE_PORT_EGRESS, 0x0004,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFFFC, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Replace VID by Port Default VID at egress, CPU debug Tag enable."
    ),

    define_sw_reg(
        PORT_TX_QUE_CTL0, "Port Transmit Queue Control 0",
        FUNCTION_SPACE_PORT_EGRESS, 0x0014,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x0F, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Scheduler mode, Shaper enable."
    ),

    define_sw_reg(
        PORT_TX_QUE_CTL1, "Port Transmit Queue Control 1",
        FUNCTION_SPACE_PORT_EGRESS, 0x0015,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x80, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Queue Weight for WRR Scheduling."
    ),

    define_sw_reg(
        PORT_TX_QUE_CTL2, "Port Transmit Queue Control 2",
        FUNCTION_SPACE_PORT_EGRESS, 0x0016,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Port Queue Credit High Water Mark."
    ),

    define_sw_reg(
        PORT_TX_QUE_CTL3, "Port Transmit Queue Control 3",
        FUNCTION_SPACE_PORT_EGRESS, 0x0018,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Port Queue Credit Low Water Mark."
    ),

#ifdef SETUP_A0
    define_sw_reg(
        PORT_TX_QUE_CTL4_H, "Port Transmit Queue Control 4",
        FUNCTION_SPACE_PORT_EGRESS, 0x001A,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Port Queue Credit increment."
    ),

    define_sw_reg(
        PORT_TX_QUE_CTL4_L, "Port Transmit Queue Control 4",
        FUNCTION_SPACE_PORT_EGRESS, 0x001C,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port Queue Credit increment."
    ),
#else
    define_sw_reg(
        PORT_TX_QUE_CTL4, "Port Transmit Queue Control 4",
        FUNCTION_SPACE_PORT_EGRESS, 0x001C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Port Queue Credit increment."
    ),
#endif /* SETUP_A0 */

    define_sw_reg(
        PORT_TAS_CTL, "Port Transmit TAS Control",
        FUNCTION_SPACE_PORT_EGRESS, 0x0020,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x7F, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Cut Through Mode Enable."
    ),

    define_sw_reg(
        PORT_TAS_EVNT_IDX, "Port Transmit TAS Event Index",
        FUNCTION_SPACE_PORT_EGRESS, 0x0023,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x00, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "TAS Event Index."
    ),

    define_sw_reg(
        PORT_TAS_EVNT, "Port Transmit TAS Event",
        FUNCTION_SPACE_PORT_EGRESS, 0x0024,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Gate Status of each Queue, Cycle count of system clock."
    ),

    define_sw_reg(
        PORT_PTP_TRG_ST_NS, "Port PTP Trigger Start Time Nanosecond",
        FUNCTION_SPACE_PORT_EGRESS, 0x0028,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xC0000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger start time in ns."
    ),

    define_sw_reg(
        PORT_PTP_TRG_ST_SEC, "Port PTP Trigger Start Time Second",
        FUNCTION_SPACE_PORT_EGRESS, 0x002C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger start time in seconds."
    ),

    define_sw_reg(
        PORT_PTP_CYC_TIME, "Port PTP Cycle Time",
        FUNCTION_SPACE_PORT_EGRESS, 0x0030,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "PTP Trigger output cycle time."
    ),

    define_sw_reg(
        PORT_TAS_GLIST_LIDX, "Port TAS Gate Control List Last Index",
        FUNCTION_SPACE_PORT_EGRESS, 0x0034,
        REGISTER_WORD,
        REGISTER_PORT,
        0xFF00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Last index of Gate control list."
    ),

    define_sw_reg(
        PORT_TAS_GCTRL, "Port TAS Gate Control",
        FUNCTION_SPACE_PORT_EGRESS, 0x0036,
        REGISTER_BYTE,
        REGISTER_PORT | REGISTER_SELF_CLEAR,
        0x1F, // Reserved mask.
        0x00, // Read only mask.
        0x80, // Misc mask.
        "Gate Enable, Configuration change indicator."
    ),

    define_sw_reg(
        PORT_TAS_MAX_SDU, "Port TAS Maximum SDU",
        FUNCTION_SPACE_PORT_EGRESS, 0x0038,
        REGISTER_WORD,
        REGISTER_PORT,
        0x8000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "TAS Max SDU, SDU Length check enable."
    ),

    define_sw_reg(
        PORT_TAS_CUR_STATE, "Port TAS Current Gate State",
        FUNCTION_SPACE_PORT_EGRESS, 0x003A,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Current GCL Index and Current GCL State."
    ),

    define_sw_reg(
        PORT_TAS_OVR_CNT, "Port TAS Overrun Counter",
        FUNCTION_SPACE_PORT_EGRESS, 0x003C,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "TAS Gate Overrun counter."
    ),

    define_sw_reg(
        PORT_TAS_INT_MASK, "Port TAS Interrupt Mask",
        FUNCTION_SPACE_PORT_EGRESS, 0x0040,
        REGISTER_WORD,
        REGISTER_PORT,
        0x3F80, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "TAS Configuration Change, error and Overrun Interrupt mask."
    ),

    define_sw_reg(
        PORT_TAS_INT_STATUS, "Port TAS Interrupt Status",
        FUNCTION_SPACE_PORT_EGRESS, 0x0044,
        REGISTER_WORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x3E00, // Reserved mask.
        0x0100, // Read only mask.
        0xC0FF, // Misc mask.
        "TAS Configuration Change, Error and Overrun Interrupt Status."
    ),

    define_sw_reg(
        PORT_CTL0, "Port Control 0",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0000,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFFF8, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Packet drop configuration during congestion."
    ),

    define_sw_reg(
        PORT_CTL1, "Port Control 1",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0004,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFFF00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Port VLAN Membership. "
    ),

    define_sw_reg(
        PORT_BURST_RSV_VAL, "Port Burst Size and Reserved Space",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0008,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xF8FFF800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Port Burst size and Minimum Reserved block size."
    ),

    define_sw_reg(
        PORT_WATER_MARK, "Port Queue Water Mark",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x000C,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xF800F800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Queue High Water Mark and Low Water Mark."
    ),

    define_sw_reg(
        PORT_TXQ_BLK_CNT0, "Port TX Queue Block Count 0",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0010,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xFFFFF800, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Number of Blocks used by the Queue."
    ),

    define_sw_reg(
        PORT_TXQ_BLK_CNT1, "Port TX Queue Block Count 1",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0014,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xF800FC00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Available block count for the queue."
    ),

    define_sw_reg(
        PORT_TXQ_BLK_CNT2, "Port TX Queue Block Count 2",
        FUNCTION_SPACE_PORT_QUEUE_MANAGEMENT, 0x0018,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xF8FFFC00, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Maximum Queue fill count."
    ),

    define_sw_reg(
        PORT_LUE_CONTROL, "Port LUE Learn Control",
        FUNCTION_SPACE_PORT_LUE, 0x0000,
        REGISTER_BYTE,
        REGISTER_PORT,
        0x07, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "MAC Based 802.1X Authentication Enable, Ingress VLAN Filtering, Discard Non PVID Packet, Self Address filtering Enable."
    ),

    define_sw_reg(
        PORT_LUE_MSTP_POINTER, "Port LUE MSTP Pointer",
        FUNCTION_SPACE_PORT_LUE, 0x0001,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "MSTP Pointer."
    ),

    define_sw_reg(
        PORT_LUE_MSTP_STATE, "Port LUE MSTP State",
        FUNCTION_SPACE_PORT_LUE, 0x0004,
        REGISTER_BYTE,
        REGISTER_PORT,
        0xF8, // Reserved mask.
        0x00, // Read only mask.
        0x00, // Misc mask.
        "Port Transmit/ Receive Enable, Port Learning Disable."
    ),

    define_sw_reg(
        PORT_LUE_LEARN_LIMIT, "Port LUE Learn Limit",
        FUNCTION_SPACE_PORT_LUE, 0x0008,
        REGISTER_DWORD,
        REGISTER_PORT,
        0xF800F800, // Reserved mask.
        0x07FF0000, // Read only mask.
        0x00000000, // Misc mask.
        "Number of addresses learnt by the port and Port lean limit."
    ),

    define_sw_reg(
        PORT_SW_LUE_UNK_CTL0, "Port Switch LUE Unknown Control 0",
        FUNCTION_SPACE_PORT_LUE, 0x000E,
        REGISTER_WORD,
        REGISTER_PORT,
        0x7F00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Unknown Unicast Packet Forward and Port Map."
    ),

    define_sw_reg(
        PORT_SW_LUE_UNK_CTL1, "Port Switch LUE Unknown Control 1",
        FUNCTION_SPACE_PORT_LUE, 0x0010,
        REGISTER_WORD,
        REGISTER_PORT,
        0x7F00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Unknown Multicast Packet Forward and Port Map."
    ),

    define_sw_reg(
        PORT_SW_LUE_UNK_CTL2, "Port Switch LUE Unknown Control 2",
        FUNCTION_SPACE_PORT_LUE, 0x0014,
        REGISTER_WORD,
        REGISTER_PORT,
        0x7F00, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Unknown VID Forward and Port map."
    ),

    define_sw_reg(
        PORT_PTP_RX_LAT, "Port PTP Receive Latency",
        FUNCTION_SPACE_PORT_PTP, 0x0000,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Fixed PTP receive delay in ns."
    ),

    define_sw_reg(
        PORT_PTP_TX_LAT, "Port PTP Transmit Latency",
        FUNCTION_SPACE_PORT_PTP, 0x0002,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Fixed PTP Transmit delay in ns."
    ),

    define_sw_reg(
        PORT_PTP_ASYM, "Port PTP Asymmetry Correction",
        FUNCTION_SPACE_PORT_PTP, 0x0004,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Magnitude of correction, Fixed correction value for ingress sync and egress delay/ Pdelay request."
    ),

    define_sw_reg(
        PORT_XDLY_REQ_TS_HI, "Port PTP Egress TS for Request and Delay High Word",
        FUNCTION_SPACE_PORT_PTP, 0x0008,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for Pdelay_Req / Delay_Req frames in ns."
    ),

    define_sw_reg(
        PORT_XDLY_REQ_TS_LO, "Port PTP Egress TS for Request and Delay Low Word",
        FUNCTION_SPACE_PORT_PTP, 0x000A,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for Pdelay_Req / Delay_Req frames in ns."
    ),

    define_sw_reg(
        PORT_SYNC_TS_HI, "Port PTP Egress TS for Sync High Word",
        FUNCTION_SPACE_PORT_PTP, 0x000C,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for sync frames in ns."
    ),

    define_sw_reg(
        PORT_SYNC_TS_LO, "Port Sync Timestamp Low",
        FUNCTION_SPACE_PORT_PTP, 0x000E,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for sync frames in ns."
    ),

    define_sw_reg(
        PORT_PTP_PDLY_TS_HI, "Port PTP Egress TS for PDELAY Response High Word",
        FUNCTION_SPACE_PORT_PTP, 0x0010,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for Pdelay_resp frames in ns."
    ),

    define_sw_reg(
        PORT_PTP_PDLY_TS_LO, "Port PTP Egress TS for PDELAY Response Low Word",
        FUNCTION_SPACE_PORT_PTP, 0x0012,
        REGISTER_WORD,
        REGISTER_PORT,
        0x0000, // Reserved mask.
        0xFFFF, // Read only mask.
        0x0000, // Misc mask.
        "Egress Timestamp for Pdelay_resp frames in ns."
    ),

    define_sw_reg(
        PORT_PTP_TS_INT_STS, "Port PTP TS Interrupt Status",
        FUNCTION_SPACE_PORT_PTP, 0x0014,
        REGISTER_WORD,
        REGISTER_PORT | REGISTER_WRITE_ONE_CLEAR,
        0x1FFF, // Reserved mask.
        0x0000, // Read only mask.
        0xE000, // Misc mask.
        "Sync frame, Pdelay_req, Delay_Req, Pdelay_Resp frames Interrupt status."
    ),

    define_sw_reg(
        PORT_PTP_TS_INT_EN, "Port PTP TS Interrupt Status",
        FUNCTION_SPACE_PORT_PTP, 0x0016,
        REGISTER_WORD,
        REGISTER_PORT,
        0x1FFF, // Reserved mask.
        0x0000, // Read only mask.
        0x0000, // Misc mask.
        "Sync frame, Pdelay_req, Delay_Req, Pdelay_Resp frames Interrupt Enable."
    ),

    define_sw_reg(
        PORT_PTP_LINK_DLY, "Port PTP Link Delay",
        FUNCTION_SPACE_PORT_PTP, 0x0018,
        REGISTER_DWORD,
        REGISTER_PORT,
        0x00000000, // Reserved mask.
        0x00000000, // Read only mask.
        0x00000000, // Misc mask.
        "Link Delay value from the port to link partner port in ns."
    ),

#ifdef SWITCH_REGISTERS_C
};
#else
    SW_REG_IDX_LAST
} SwRegIdx_t;
#endif

#endif  /* SWITCH_REGISTERS_H */
