/*******************************************************************************
  MPLAB Harmony Audio Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_audio.c

  Summary:
    Audio handling for ML keyword spotting integration.

  Description:
    This file implements the audio state machine that captures microphone data
    via WM8904 codec and I2S DMA for keyword classification.
*******************************************************************************/

#include "app_audio.h"

DRV_I2S_DATA __attribute__((aligned(32))) micBuffer[MAX_BUFFERS][MAX_AUDIO_NUM_SAMPLES];

APP_AUDIO_DATA appAudioData;

static DRV_HANDLE tmrHandle;

static uint16_t volumeLevels[VOLUME_STEPS] = {
    0 /* off */, 128, 192, 255
};

static void App_TimerCallback(uintptr_t context)
{
    if (appAudioData.buttonDelay) {
        appAudioData.buttonDelay--;
    }
}

static void _audioCodecDataInitialize(AUDIO_CODEC_DATA* codecData)
{
    codecData->handle = DRV_HANDLE_INVALID;
    codecData->context = 0;
    codecData->bufferHandler =
        (DRV_CODEC_BUFFER_EVENT_HANDLER)Audio_Codec_BufferEventHandler;
    codecData->txbufferObject = (uint8_t*)micBuffer[0];
    codecData->rxbufferObject = (uint8_t*)micBuffer[1];
    codecData->bufferSize = sizeof(micBuffer[0]);
}

void APP_AUDIO_Initialize(void)
{
    appAudioData.state = APP_AUDIO_STATE_INIT;
    appAudioData.bufferReady = false;
    appAudioData.buttonDelay = 0;
    appAudioData.delayEnabled = false;
    appAudioData.volume = volumeLevels[INIT_VOLUME_IDX];
    appAudioData.txBufferIdx = 0;
    appAudioData.rxBufferIdx = 1;

    _audioCodecDataInitialize(&appAudioData.codecData);

    appAudioData.codecData.txbufferObject = (uint8_t*)micBuffer[appAudioData.txBufferIdx];
    appAudioData.codecData.rxbufferObject = (uint8_t*)micBuffer[appAudioData.rxBufferIdx];
}

void APP_AUDIO_Tasks(void)
{
    static APP_AUDIO_STATES lastState = (APP_AUDIO_STATES)-1;
    static uint32_t bufferCount = 0;

    /* Print state changes */
    if (appAudioData.state != lastState) {
        SYS_CONSOLE_PRINT("AUDIO: State %d -> %d\r\n", lastState, appAudioData.state);
        lastState = appAudioData.state;
    }

    switch (appAudioData.state)
    {
        case APP_AUDIO_STATE_INIT:
        {
            tmrHandle = SYS_TIME_CallbackRegisterMS(App_TimerCallback,
                (uintptr_t)0, 1/*ms*/, SYS_TIME_PERIODIC);

            if (SYS_TIME_HANDLE_INVALID != tmrHandle) {
                appAudioData.state = APP_AUDIO_STATE_CODEC_OPEN;
            }
        }
        break;

        case APP_AUDIO_STATE_CODEC_OPEN:
        {
            SYS_STATUS status = DRV_CODEC_Status(sysObjdrvCodec0);
            if (SYS_STATUS_READY == status) {
                SYS_CONSOLE_PRINT("AUDIO: Codec ready, opening...\r\n");
                appAudioData.codecData.handle = DRV_CODEC_Open(DRV_CODEC_INDEX_0,
                    DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_EXCLUSIVE);
                if (appAudioData.codecData.handle != DRV_HANDLE_INVALID) {
                    SYS_CONSOLE_PRINT("AUDIO: Codec opened OK\r\n");
                    DRV_CODEC_VolumeSet(appAudioData.codecData.handle,
                        DRV_CODEC_CHANNEL_LEFT_RIGHT, appAudioData.volume);
                    appAudioData.state = APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER;
                }
            }
        }
        break;

        case APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER:
        {
            DRV_CODEC_BufferEventHandlerSet(appAudioData.codecData.handle,
                appAudioData.codecData.bufferHandler,
                appAudioData.codecData.context);
            SYS_CONSOLE_PRINT("AUDIO: Buffer handler set\r\n");
            appAudioData.state = APP_AUDIO_STATE_CODEC_ADD_BUFFER;
        }
        break;

        case APP_AUDIO_STATE_CODEC_ADD_BUFFER:
        {
            DRV_CODEC_BufferAddWriteRead(appAudioData.codecData.handle,
                &appAudioData.codecData.writeBufHandle,
                appAudioData.codecData.txbufferObject,
                appAudioData.codecData.rxbufferObject,
                appAudioData.codecData.bufferSize);

            if (appAudioData.codecData.writeBufHandle != DRV_CODEC_BUFFER_HANDLE_INVALID) {
                appAudioData.txBufferIdx = 1 - appAudioData.txBufferIdx;
                appAudioData.rxBufferIdx = 1 - appAudioData.txBufferIdx;

                appAudioData.codecData.txbufferObject = (uint8_t*)micBuffer[appAudioData.txBufferIdx];
                appAudioData.codecData.rxbufferObject = (uint8_t*)micBuffer[appAudioData.rxBufferIdx];

                appAudioData.state = APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE;
                appAudioData.bufferReady = true;
                bufferCount++;
                if (bufferCount == 1 || (bufferCount % 100) == 0) {
                    SYS_CONSOLE_PRINT("AUDIO: Buffer %lu complete\r\n", (unsigned long)bufferCount);
                }
            }
        }
        break;

        case APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE:
        {
            static uint32_t waitCount = 0;
            waitCount++;
            if (waitCount == 1 || (waitCount % 500000) == 0) {
                SYS_CONSOLE_PRINT("AUDIO: Waiting for DMA... count=%lu, LRCLK=%lu\r\n",
                    (unsigned long)waitCount, (unsigned long)I2S_LRCLK_Get());
            }
            appAudioData.bufferReady = false;
        }
        break;

        default:
            break;
    }
}

void Audio_Codec_BufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
    DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context)
{
    switch (event)
    {
        case DRV_CODEC_BUFFER_EVENT_COMPLETE:
            appAudioData.state = APP_AUDIO_STATE_CODEC_ADD_BUFFER;
            break;

        case DRV_CODEC_BUFFER_EVENT_ERROR:
        case DRV_CODEC_BUFFER_EVENT_ABORT:
            break;
    }
}
