/*******************************************************************************
  MPLAB Harmony Audio Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_audio.h

  Summary:
    Audio handling for ML keyword spotting integration.

  Description:
    This header file provides prototypes and definitions for the audio
    subsystem that captures microphone data for keyword classification.
*******************************************************************************/

#ifndef APP_AUDIO_H
#define APP_AUDIO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "configuration.h"
#include "definitions.h"
#include "app_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_AUDIO_STATE_INIT = 0,
    APP_AUDIO_STATE_CODEC_OPEN,
    APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER,
    APP_AUDIO_STATE_CODEC_ADD_BUFFER,
    APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE,
} APP_AUDIO_STATES;

typedef struct {
    APP_AUDIO_STATES state;
    AUDIO_CODEC_DATA codecData;
    volatile bool bufferReady;
    uint16_t txBufferIdx;
    uint16_t rxBufferIdx;
    uint8_t volume;
    bool delayEnabled;
    uint32_t buttonDelay;
} APP_AUDIO_DATA;

extern APP_AUDIO_DATA appAudioData;
extern DRV_I2S_DATA __attribute__((aligned(32))) micBuffer[MAX_BUFFERS][MAX_AUDIO_NUM_SAMPLES];

void APP_AUDIO_Initialize(void);
void APP_AUDIO_Tasks(void);
void Audio_Codec_BufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
    DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context);

#ifdef __cplusplus
}
#endif

#endif /* APP_AUDIO_H */
