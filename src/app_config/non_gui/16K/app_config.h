/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_config.h

  Summary:
    Audio configuration for ML keyword spotting.

  Description:
    This header file provides audio buffer and codec definitions for the
    Edge Impulse keyword spotting integration.
*******************************************************************************/

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>
#include <stddef.h>
#include "configuration.h"
#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Audio buffer size - must match Edge Impulse SLICE length (16000/4 = 4000) */
#define MAX_AUDIO_NUM_SAMPLES     4000

/* Ping-pong buffer count for DMA */
#define MAX_BUFFERS               2

/* Volume initialization */
#define INIT_VOLUME_IDX           1
#define VOLUME_STEPS              4

/* Delay settings (not used in keyword spotting mode) */
#define INIT_BUFFER_DELAY_IDX     2
#define DELAY_STEPS               4

/* I2S data structure for 32-bit stereo audio */
typedef struct {
    int32_t leftData;
    int32_t rightData;
} DRV_I2S_DATA32m;

#define DRV_I2S_DATA DRV_I2S_DATA32m

/* Codec data structure */
typedef struct {
    DRV_HANDLE handle;
    DRV_CODEC_BUFFER_HANDLE writeBufHandle;
    DRV_CODEC_BUFFER_EVENT_HANDLER bufferHandler;
    uintptr_t context;
    uint8_t *txbufferObject;
    uint8_t *rxbufferObject;
    size_t bufferSize;
} AUDIO_CODEC_DATA;

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H */
