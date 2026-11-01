/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.cpp

  Summary:
    ML keyword spotting with MQTT trigger.

  Description:
    Integrates Edge Impulse keyword classification with wolfMQTT.
    "no" keyword (>80%) → publish "true" to smart_io/mikroe1899/ch1
    "yes" keyword (>80%) → publish "false" to smart_io/mikroe1899/ch1
*******************************************************************************/

#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <cstddef>
#include <cstdbool>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "definitions.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "edge-impulse-sdk/dsp/numpy.hpp"
#include "model-parameters/model_metadata.h"
#include "app.h"
#include "app_audio.h"
#include "app_mqtt_task.h"

void *ei_malloc(size_t size) {
    return malloc(size);
}

void *ei_calloc(size_t nitems, size_t size) {
    return calloc(nitems, size);
}

void ei_free(void *ptr) {
    free(ptr);
}

EI_IMPULSE_ERROR ei_run_impulse_check_canceled() {
    return EI_IMPULSE_OK;
}

EI_IMPULSE_ERROR ei_sleep(int32_t us) {
    TC2_Timer32bitCounterSet(0);
    while (TC2_Timer32bitCounterGet() < (uint32_t)us) {};
    return EI_IMPULSE_OK;
}

uint64_t ei_read_timer_ms() {
    return TC2_Timer32bitCounterGet() / 1000;
}

uint64_t ei_read_timer_us() {
    return TC2_Timer32bitCounterGet();
}

void ei_printf(const char *format, ...) {
    char buf[256];
    va_list myargs;
    va_start(myargs, format);
    vsnprintf(buf, sizeof(buf), format, myargs);
    va_end(myargs);
    SYS_CONSOLE_PRINT("%s", buf);
}

void ei_printf_float(float f) {
    SYS_CONSOLE_PRINT("%f", f);
}

extern "C" int get_feature_data(size_t offset, size_t length, float *out_ptr) {
    DRV_I2S_DATA *ptr = micBuffer[appAudioData.rxBufferIdx];

    if (offset + length > EI_CLASSIFIER_SLICE_SIZE) {
        return EI_IMPULSE_CANCELED;
    }

    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = ((float)ptr[i + offset].rightData) / 16384.0f;
    }

    return EI_IMPULSE_OK;
}

extern "C" int _open(const char *buf, int flags, int mode) {
    (void)buf;
    (void)flags;
    (void)mode;
    return 0;
}

static void raw_uart_puts(const char* s) {
    for (const char* p = s; *p; p++) {
        while (!(SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk));
        SERCOM1_REGS->USART_INT.SERCOM_DATA = *p;
    }
    while (!(SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk));
}

int main(void)
{
    SYS_Initialize(NULL);

    raw_uart_puts("\r\n\r\n*** BOOT ***\r\n");

    for (volatile int i = 0; i < 100; i++) {
        SYS_Tasks();
        for (volatile int j = 0; j < 10000; j++);
    }

    SYS_CONSOLE_PRINT("\r\n\r\n=== wolfMQTT + Edge Impulse Keyword Spotting ===\r\n");
    SYS_CONSOLE_PRINT("Build: %s %s\r\n", __DATE__, __TIME__);

    for (volatile int i = 0; i < 50; i++) {
        SYS_Tasks();
        for (volatile int j = 0; j < 10000; j++);
    }

    SYS_CONSOLE_PRINT("Initializing Edge Impulse classifier...\r\n");

    TC2_TimerStart();

    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
    signal.get_data = &get_feature_data;

    ei_impulse_result_t result = { 0 };
    EI_IMPULSE_ERROR ei_status = EI_IMPULSE_OK;

    run_classifier_init();
    SYS_CONSOLE_PRINT("Classifier initialized. Listening for keywords...\r\n");

    uint32_t lastPublishTime = 0;
    const uint32_t DEBOUNCE_MS = 2000;

    while (true)
    {
        SYS_Tasks();

        if (!appAudioData.bufferReady) {
            continue;
        }

        // Debug: print audio samples to verify real data
        static uint32_t debugCount = 0;
        if (debugCount < 5 || (debugCount % 50) == 0) {
            DRV_I2S_DATA *ptr = micBuffer[appAudioData.rxBufferIdx];
            int32_t minVal = ptr[0].rightData;
            int32_t maxVal = ptr[0].rightData;
            for (int i = 0; i < 4000; i++) {
                if (ptr[i].rightData < minVal) minVal = ptr[i].rightData;
                if (ptr[i].rightData > maxVal) maxVal = ptr[i].rightData;
            }
            SYS_CONSOLE_PRINT("Audio[%lu] rxIdx=%d: min=%ld max=%ld range=%ld\r\n",
                (unsigned long)debugCount, appAudioData.rxBufferIdx,
                (long)minVal, (long)maxVal, (long)(maxVal - minVal));
            SYS_CONSOLE_PRINT("  Raw: L0=%ld R0=%ld L1=%ld R1=%ld\r\n",
                (long)ptr[0].leftData, (long)ptr[0].rightData,
                (long)ptr[1].leftData, (long)ptr[1].rightData);
        }
        debugCount++;

        ei_status = run_classifier_continuous(&signal, &result, false);
        if (ei_status != EI_IMPULSE_OK) {
            SYS_CONSOLE_PRINT("run_classifier returned: %d\r\n", ei_status);
            break;
        }

        float maxval = 0;
        int maxidx = -1;
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            if (result.classification[ix].value > maxval) {
                maxval = result.classification[ix].value;
                maxidx = ix;
            }
        }

        SYS_CONSOLE_PRINT("Predictions (DSP: %d ms., Classification: %d ms.): \r\n",
            result.timing.dsp, result.timing.classification);
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            SYS_CONSOLE_PRINT("    %s: %.2f\r\n",
                result.classification[ix].label, result.classification[ix].value);
        }

        if (maxval > 0.8f && maxidx >= 0) {
            const char* label = result.classification[maxidx].label;
            const char* payload = NULL;

            if (!strcmp(label, "no")) {
                payload = "true";
            } else if (!strcmp(label, "yes")) {
                payload = "false";
            }

            if (payload != NULL) {
                uint32_t now = SYS_TIME_CountToMS(SYS_TIME_CounterGet());
                if (now - lastPublishTime > DEBOUNCE_MS) {
                    lastPublishTime = now;

                    SYS_CONSOLE_PRINT("*** KEYWORD '%s' DETECTED - Publishing '%s' ***\r\n", label, payload);

                    APP_MQTT_CONTEXT* ctx = APP_MQTT_GetContext();
                    strncpy(ctx->publishMessage, payload, sizeof(ctx->publishMessage) - 1);
                    ctx->publishMessage[sizeof(ctx->publishMessage) - 1] = '\0';
                    ctx->currState = APP_MQTT_STATE_BEGIN;
                    ctx->mqttCommand = APP_MQTT_COMMAND_SUBSCRIBE;
                }
            }
        }
    }

    return EXIT_FAILURE;
}
