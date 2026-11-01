/*******************************************************************************
  LAN9370 Register Access Console Command Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_lan9370_commands.h

  Summary:
    Registers the "reg" console command group for LAN9370 register access.

  Description:
    Mirrors the structure of app_mqtt_task.h / app_mqtt_commands.c for the
    "mqtt" command group.
*******************************************************************************/

#ifndef _APP_LAN9370_COMMANDS_H_
#define _APP_LAN9370_COMMANDS_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Registers the "reg" command group ("reg read/write/modify") with the
// system command service. Returns true on success.
bool APP_LAN9370_CommandsInit(void);

#ifdef __cplusplus
}
#endif

#endif /* _APP_LAN9370_COMMANDS_H_ */
