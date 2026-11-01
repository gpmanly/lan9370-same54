#!/usr/bin/env bash
# Configure and build. Run from the repo root.
set -euo pipefail

BUILD_DIR=_build/wolfmqtt_demo/sam_e54_xpro

cmake --preset wolfmqtt_demo_sam_e54_xpro_conf -S cmake/wolfmqtt_demo/sam_e54_xpro
ninja -C "$BUILD_DIR"
