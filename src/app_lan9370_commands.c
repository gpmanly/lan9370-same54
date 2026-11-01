/*******************************************************************************
  LAN9370 Register Access Console Command Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_lan9370_commands.c

  Summary:
    Implements the "reg" console command group for LAN9370 register access.

  Description:
    Mirrors the structure of app_mqtt_commands.c: one SYS_CMD_DESCRIPTOR group
    entry registered via SYS_CMD_ADDGRP, dispatching by sub-command string to
    read/write/modify handlers built on app_lan9370_spi.h.
*******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "app_lan9370_commands.h"
#include "app_lan9370_spi.h"
#include "definitions.h"

// local prototypes

static void     Command_Reg(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static void     CmdRegRead(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegWrite(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegModify(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegReadWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegWriteWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegModifyWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void     CmdRegHelp(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static bool     ParseHexArg(const void* cmdIoParam, const SYS_CMD_API* pCmdApi, char* str, unsigned int limit, unsigned int* pRes);

// local data

static const SYS_CMD_DESCRIPTOR    regCmdTbl[] =
{
    {"reg",     Command_Reg,    "LAN9370 register access commands"},
};

typedef void    (*command_reg_fnc)(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
typedef struct
{
    const char*         cmdString;      // string identifying the sub-command
    command_reg_fnc     fnc;            // processing function
    uint16_t            minParams;      // min required number of parameters
    uint16_t            maxParams;      // max number of parameters
    const char*         cmdHelp;        // brief command description
}CMD_REG_PROC_DCPT;

#define     CMD_REG_HELP_READ       "reg read <addr> : reads a byte-wide LAN9370 register. <addr> is hex, 0-0xFFFF. NOTE: GLB_CONTROL0 (reg 7) bit 0x80 (APB_PHY_REG_BLK) defaults to 1 and blocks SPI access to all per-port T1 PHY/TX PHY/VPHY registers - clear it first with 'reg modify 7 80 00'. Example: reg read 0"
#define     CMD_REG_HELP_WRITE      "reg write <addr> <val> : writes a byte-wide LAN9370 register. <addr> is hex 0-0xFFFF, <val> is hex 0-0xFF. Example: reg write 7 80"
#define     CMD_REG_HELP_MODIFY     "reg modify <addr> <mask> <val> : read-modify-writes a byte-wide LAN9370 register. <addr> is hex 0-0xFFFF; <mask> and <val> are hex 0-0xFF; bits set in <mask> are replaced with the corresponding bits of <val>. Example: reg modify 7 80 00 (clears APB_PHY_REG_BLK to unblock per-port PHY register access)"
#define     CMD_REG_HELP_READW      "reg readw <addr> : reads a 16-bit-wide LAN9370 register (e.g. port N T1 PHY SMI registers at (N<<12)|0x100|(SMI_offset<<2)). <addr> is hex, 0-0xFFFF. Example: reg readw 1108"
#define     CMD_REG_HELP_WRITEW     "reg writew <addr> <val> : writes a 16-bit-wide LAN9370 register. <addr> and <val> are hex, 0-0xFFFF. Example: reg writew 1108 0007"
#define     CMD_REG_HELP_MODIFYW    "reg modifyw <addr> <mask> <val> : read-modify-writes a 16-bit-wide LAN9370 register. <addr>, <mask> and <val> are hex, 0-0xFFFF; bits set in <mask> are replaced with the corresponding bits of <val>. Example: reg modifyw 1108 00FF 0007"
#define     CMD_REG_HELP_HELP       "This help command"

static const CMD_REG_PROC_DCPT cmd_reg_proc_dcpt_tbl[] =
{
    // string       // fnc              // minParams    // maxParams    // cmdHelp
    {"read",        CmdRegRead,         3,              3,              CMD_REG_HELP_READ   },
    {"write",       CmdRegWrite,        4,              4,              CMD_REG_HELP_WRITE  },
    {"modify",      CmdRegModify,       5,              5,              CMD_REG_HELP_MODIFY },
    {"readw",       CmdRegReadWord,     3,              3,              CMD_REG_HELP_READW  },
    {"writew",      CmdRegWriteWord,    4,              4,              CMD_REG_HELP_WRITEW },
    {"modifyw",     CmdRegModifyWord,   5,              5,              CMD_REG_HELP_MODIFYW},
    {"help",        CmdRegHelp,         2,              2,              CMD_REG_HELP_HELP   },
};


// API Implementation

bool APP_LAN9370_CommandsInit(void)
{
    // create reg command group
    if (!SYS_CMD_ADDGRP(regCmdTbl, sizeof(regCmdTbl) / sizeof(*regCmdTbl), "reg", ": LAN9370 register commands"))
    {
        SYS_CONSOLE_MESSAGE("Failed to create reg Commands\r\n");
        return false;
    }

    SYS_CONSOLE_MESSAGE("Created the reg Commands\r\n");
    return true;
}


// Local functions implementation

static void Command_Reg(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    if(argc == 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "reg command takes at least one parameter. Try 'reg help'\r\n");
        return;
    }

    int ix;
    const CMD_REG_PROC_DCPT* procDcpt = cmd_reg_proc_dcpt_tbl;

    for(ix = 0; ix < sizeof(cmd_reg_proc_dcpt_tbl) / sizeof(*cmd_reg_proc_dcpt_tbl); ix++, procDcpt++)
    {
        if(strcmp(argv[1], procDcpt->cmdString) == 0)
        {   // found command
            if(argc < procDcpt->minParams || argc > procDcpt->maxParams)
            {
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "reg: command %s takes min %d and max %d parameters.\r\n", procDcpt->cmdString, procDcpt->minParams, procDcpt->maxParams);
            }
            else
            {
                (*procDcpt->fnc)(pCmdIO, argc, argv);
            }
            return;
        }
    }

    (*pCmdIO->pCmdApi->print)(cmdIoParam, "reg: command %s unknown. Try 'reg help'\r\n", argv[1]);
}


// Parses argv[argIx] as hex into *pRes, bounded to [0, limit]. Prints a usage
// message and returns false on malformed or out-of-range input.
static bool ParseHexArg(const void* cmdIoParam, const SYS_CMD_API* pCmdApi, char* str, unsigned int limit, unsigned int* pRes)
{
    unsigned int val;

    if(sscanf(str, "%x", &val) != 1 || val > limit)
    {
        (*pCmdApi->print)(cmdIoParam, "reg: invalid value '%s' (expected hex, 0-0x%X)\r\n", str, limit);
        return false;
    }

    *pRes = val;
    return true;
}

static void CmdRegRead(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr;
    uint8_t      val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!APP_LAN9370_RegRead((uint16_t)addr, &val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg read: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg read: addr 0x%04X = 0x%02X\r\n", addr, val);
}

static void CmdRegWrite(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr, val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[3], 0xFFU, &val))
    {
        return;
    }

    if(!APP_LAN9370_RegWrite((uint16_t)addr, (uint8_t)val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg write: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg write: addr 0x%04X = 0x%02X\r\n", addr, val);
}

static void CmdRegModify(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr, mask, val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[3], 0xFFU, &mask))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[4], 0xFFU, &val))
    {
        return;
    }

    if(!APP_LAN9370_RegModify((uint16_t)addr, (uint8_t)mask, (uint8_t)val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg modify: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg modify: addr 0x%04X, mask 0x%02X, val 0x%02X\r\n", addr, mask, val);
}

static void CmdRegReadWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr;
    uint16_t     val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!APP_LAN9370_RegReadWord((uint16_t)addr, &val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg readw: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg readw: addr 0x%04X = 0x%04X\r\n", addr, val);
}

static void CmdRegWriteWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr, val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[3], 0xFFFFU, &val))
    {
        return;
    }

    if(!APP_LAN9370_RegWriteWord((uint16_t)addr, (uint16_t)val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg writew: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg writew: addr 0x%04X = 0x%04X\r\n", addr, val);
}

static void CmdRegModifyWord(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    const SYS_CMD_API* pCmdApi = pCmdIO->pCmdApi;
    unsigned int addr, mask, val;

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[2], 0xFFFFU, &addr))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[3], 0xFFFFU, &mask))
    {
        return;
    }

    if(!ParseHexArg(cmdIoParam, pCmdApi, argv[4], 0xFFFFU, &val))
    {
        return;
    }

    if(!APP_LAN9370_RegModifyWord((uint16_t)addr, (uint16_t)mask, (uint16_t)val))
    {
        (*pCmdApi->print)(cmdIoParam, "reg modifyw: SPI transfer failed for addr 0x%04X\r\n", addr);
        return;
    }

    (*pCmdApi->print)(cmdIoParam, "reg modifyw: addr 0x%04X, mask 0x%04X, val 0x%04X\r\n", addr, mask, val);
}

static void CmdRegHelp(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    int ix;
    const CMD_REG_PROC_DCPT* procDcpt = cmd_reg_proc_dcpt_tbl;

    for(ix = 0; ix < sizeof(cmd_reg_proc_dcpt_tbl) / sizeof(*cmd_reg_proc_dcpt_tbl); ix++, procDcpt++)
    {
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "%s: %s\r\n", procDcpt->cmdString, procDcpt->cmdHelp);
    }
}
