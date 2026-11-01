#!/bin/bash
# Fix CMake-generated Ninja rules for XC32 C++ compiler path issue
#
# Problem: CMake's Ninja generator converts the C++ compiler path to Windows
# 8.3 short format (XC32-G~1.EXE), which Ninja cannot execute, resulting in
# [code=2] errors with no output.
#
# Solution: Replace the 8.3 path with the quoted full path.
#
# Run this AFTER cmake --preset and BEFORE ninja build.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../_build/wolfmqtt_demo/sam_e54_xpro"
RULES_FILE="$BUILD_DIR/CMakeFiles/rules.ninja"

if [ ! -f "$RULES_FILE" ]; then
    echo "Error: $RULES_FILE not found"
    echo "Run cmake --preset wolfmqtt_demo_sam_e54_xpro_conf first"
    exit 1
fi

echo "Fixing C++ compiler path in $RULES_FILE..."

# Replace 8.3 short name with quoted full path
sed -i 's|c:\\PROGRA~1\\MICROC~1\\xc32\\v5\.10\\bin\\XC32-G~1\.EXE|"c:/Program Files/Microchip/xc32/v5.10/bin/xc32-g++.exe"|g' "$RULES_FILE"

# Verify the fix
if grep -q "XC32-G~1" "$RULES_FILE"; then
    echo "Warning: Some 8.3 paths may remain - check manually"
else
    echo "Fix applied successfully"
fi
