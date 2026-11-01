# wolfMQTT Keyword Spotting Demo

**Status: Work in Progress**

Voice-activated MQTT client for SAM E54 Curiosity Ultra with WM8904 audio codec.

## Overview

This firmware integrates:
- **Edge Impulse** keyword spotting (TensorFlow Lite Micro)
- **wolfMQTT** client for IoT messaging
- **Harmony 3** TCP/IP stack with GMAC Ethernet

When the keywords "no" or "yes" are detected via the microphone, the board publishes an MQTT message to control remote devices.

## Current Status

| Component | Status |
|-----------|--------|
| TCP/IP stack + Ethernet | Working |
| WM8904 codec init | Working |
| I2S DMA audio capture | Working |
| Edge Impulse classifier | Working |
| Keyword detection | Partially tested (no microphone connected yet) |
| MQTT publish | Not yet verified end-to-end |

**Known issues:**
- DSP timing is ~3.4 seconds (expected ~100ms) — needs -O2 optimization
- Microphone input not yet tested with actual speech

## Hardware

- **Board:** SAM E54 Curiosity Ultra (ATSAME54P20A)
- **Audio Codec:** WM8904 on X32 audio daughter card
- **Network:** GMAC Ethernet (RMII)

### Required Jumper

Connect **J503 D9 (PB16)** to **J401 pin 2 (MCLK)** with a jumper wire.

This routes the 12.288 MHz master clock from GCLK2 to the WM8904 codec.

## Build

Requires XC32 compiler v5.10+ and Ninja. Run these commands from the repo root (PowerShell, cmd or Git Bash):

```
cmake --preset wolfmqtt_demo_sam_e54_xpro_conf -S cmake/wolfmqtt_demo/sam_e54_xpro

ninja -C _build/wolfmqtt_demo/sam_e54_xpro
```

`./build.sh` (Git Bash) runs both steps.

`cmake/wolfmqtt_demo/sam_e54_xpro/user.cmake` adds the Edge Impulse SDK includes and defines, and works around CMake's Ninja generator rewriting `C:\Program Files\...\2-g++.exe` to an 8.3 short path that the compiler can't run.

The generated CMake in `cmake/.../.generated/` comes from `.vscode/wolfmqtt_demo.mplab.json`. If you add source files, add them to that file's `fileSets` so the MPLAB extension doesn't regenerate a source list that's missing them.

Output: `out/wolfmqtt_demo/sam_e54_xpro.elf`

## Configuration

Edit `src/app_mqtt_task.h`:

| Setting | Default | Description |
|---------|---------|-------------|
| `APP_MQTT_DEFAULT_BROKER` | 192.168.178.20 | MQTT broker IP |
| `APP_MQTT_DEFAULT_BROKER_PORT` | 1883 | Broker port |
| `APP_MQTT_DEFAULT_PUBLISH_TOPIC` | smart_io/mikroe1899/ch1 | Topic to publish to |

## Behavior

| Keyword | Confidence | Action |
|---------|------------|--------|
| "no" | >80% | Publish `"true"` |
| "yes" | >80% | Publish `"false"` |

A 2-second debounce prevents repeated triggers.

## Serial Console

### Connection

Connect a USB cable from your PC to the board's **DEBUG USB** port (the on-board EDBG debugger). This exposes a USB CDC virtual COM port for the console — no separate USB-to-serial adapter is needed.

Windows lists it as **"Atmel Corp. EDBG USB Port (COMxx)"** in Device Manager. If more than one EDBG-based board is connected, match the COM port to the right board by its USB instance path, or disconnect the others.

### Serial settings

| Setting | Value |
|---------|-------|
| Baud rate | 115200 |
| Data bits | 8 |
| Parity | None |
| Stop bits | 1 |
| Flow control | None |

In short: **115200 8N1**, no flow control.

**Note:** some terminal clients default DTR/RTS to deasserted, which can prevent the CDC port from delivering any bytes even though it opens successfully. If the console looks silent, enable DTR and RTS in your terminal's serial settings.

```
=== wolfMQTT + Edge Impulse Keyword Spotting ===
Build: Jul 24 2026 12:00:00
Classifier initialized. Listening for keywords...
Predictions (DSP: 3382 ms., Classification: 393 ms.): 
    no: 0.88
    noise: 0.05
    unknown: 0.06
    yes: 0.00
*** KEYWORD 'no' DETECTED - Publishing 'true' ***
```

## LAN9370 Switch Register Access

The `reg` console command reads, writes, and read-modify-writes LAN9370 registers over SPI (SERCOM0: MOSI=PB24, SCK=PB25, MISO=PC25, nCS=PA27). Run `reg help` for the full command list.

| Command | Width | Example |
|---------|-------|---------|
| `reg read <addr>` | 8-bit | `reg read 0` |
| `reg write <addr> <val>` | 8-bit | `reg write 7 80` |
| `reg modify <addr> <mask> <val>` | 8-bit | `reg modify 7 80 00` |
| `reg readw <addr>` | 16-bit | `reg readw 1108` |
| `reg writew <addr> <val>` | 16-bit | `reg writew 1108 0007` |
| `reg modifyw <addr> <mask> <val>` | 16-bit | `reg modifyw 1108 00ff 0007` |

`<addr>` is hex, 0-0xFFFF. Per-port registers (T1 PHY, TX PHY, VPHY) live at `(port << 12) | 0x100 | (SMI_offset << 2)`, e.g. port 1's `MODE_STATUS` register (SMI offset `0x11`) is at `0x1144`.

**Before accessing any per-port register:** `GLB_CONTROL0` (register `0x07`) bit `0x80` (`APB_PHY_REG_BLK`) defaults to `1` and blocks SPI access to all per-port T1 PHY/TX PHY/VPHY registers. Clear it once after boot:

```
reg modify 7 80 00
```

### Checking link status

Port N's `MODE_STATUS` register (16-bit) reports link state in bit 0 (`Link_Up`: 1 = up, 0 = down). For port 1:

```
reg readw 1144
```

A result with bit 0 set (e.g. `...01`) means the link is up.

## Documentation

## License

Copyright Microchip Technology Inc.
