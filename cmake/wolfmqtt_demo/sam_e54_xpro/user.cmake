# User customizations for Edge Impulse + audio integration
# This file is included AFTER main.cmake, so targets already exist

message(STATUS "Applying user.cmake customizations for Edge Impulse SDK")

# Add include paths for Edge Impulse SDK and dependencies
set(EI_SDK_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app_config/non_gui/16K"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/flatbuffers/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/gemmlowp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/ruy"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/model-parameters"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/tflite-model"
)

# CMSIS-DSP/NN headers (arm_math.h etc.) - required by the CMSIS-DSP .c
# sources pulled in for the Edge Impulse SDK. Only the C compile target
# builds those sources, so this is kept separate from EI_SDK_INCLUDES.
set(EI_CMSIS_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/PrivateInclude"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/NN/Include"
)

# Additional includes needed for main.cpp (MQTT headers)
set(MQTT_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/third_party_adapter/wolfMQTT/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfMQTT"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl/wolfssl"
)

# Apply to C compile target
target_include_directories(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile
    PRIVATE ${EI_SDK_INCLUDES}
    PRIVATE ${EI_CMSIS_INCLUDES})

# CMSIS-DSP lookup-table config (matches the working ei_kws build) - without
# these, arm_common_tables.c never emits the FFT twiddle/bitrev tables that
# arm_cfft_f32.c and friends reference, causing undefined-reference link
# errors. EIDSP_USE_CMSIS_DSP=1 must also be visible to the C target so the
# SDK's own dsp code and the raw CMSIS sources agree on which path to use.
target_compile_definitions(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile
    PRIVATE "ARM_DSP_CONFIG_TABLES"
    PRIVATE "ARM_FAST_ALLOW_TABLES"
    PRIVATE "ARM_ALL_FAST_TABLES"
    PRIVATE "ARM_FFT_ALLOW_TABLES"
    PRIVATE "ARM_TABLE_REALCOEF_F32"
    PRIVATE "ARM_TABLE_TWIDDLECOEF_F32_256"
    PRIVATE "ARM_TABLE_BITREVIDX_FLT_256"
    PRIVATE "ARM_TABLE_TWIDDLECOEF_RFFT_F32_512"
    PRIVATE "__TARGET_CPU_CORTEX_M4"
    PRIVATE "EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW=4"
    PRIVATE "EIDSP_USE_CMSIS_DSP=1")

# The C++ object library only exists when the generated file.cmake lists .cpp
# sources, so guard it instead of failing the configure step.
set(EI_CPP_TARGET wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp)
if(TARGET ${EI_CPP_TARGET})
    # Apply to C++ compile target
    target_include_directories(${EI_CPP_TARGET}
        PRIVATE ${EI_SDK_INCLUDES}
        PRIVATE ${MQTT_INCLUDES})

    # Edge Impulse SDK compile definitions for C++
    target_compile_definitions(${EI_CPP_TARGET}
        PRIVATE "EI_PORTING_RENESASRA65=0"
        PRIVATE "EI_PORTING_POSIX=0"
        PRIVATE "HAVE_CONFIG_H"
        PRIVATE "WOLFSSL_IGNORE_FILE_WARN"
        PRIVATE "__TARGET_CPU_CORTEX_M4"
        PRIVATE "EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW=4"
        PRIVATE "EIDSP_USE_CMSIS_DSP=1")
else()
    message(WARNING "${EI_CPP_TARGET} not generated - no .cpp sources in .generated/file.cmake")
endif()

# Exclude non_gui.c - it's deleted and conflicts with app_audio.c
# Note: This doesn't work retroactively since target is already created
# The file is physically deleted so this just prevents errors if regenerated
set_source_files_properties(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app_config/non_gui/non_gui.c"
    PROPERTIES HEADER_FILE_ONLY TRUE)

# Exclude the Harmony-generated main.c - main.cpp is the real entry point
# (Edge Impulse + wolfMQTT demo). Both define main() otherwise.
set_source_files_properties(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/main.c"
    PROPERTIES HEADER_FILE_ONLY TRUE)

# Exclude deprecated legacy CMSIS-DSP TransformFunctions files that reference
# symbols (twiddleCoef, armBitRevTable) only available with ARM_ALL_FFT_TABLES.
# The working ei_kws project does NOT compile these files. The new API is via
# arm_cfft_init_f32 etc. which use the granular ARM_TABLE_* defines we have.
set(CMSIS_DSP_DEPRECATED_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.c"
)
set_source_files_properties(${CMSIS_DSP_DEPRECATED_FILES}
    PROPERTIES HEADER_FILE_ONLY TRUE)

# Increase heap size for Edge Impulse DSP allocations
# Original: 122960 (120KB), increased to 143360 (140KB)
# cmvnw() was failing with EIDSP_OUT_OF_MEM (-1002)
# The executable target name carries a random suffix that MPLAB X changes on
# every regeneration, so look it up instead of hardcoding it.
get_property(EI_ALL_TARGETS DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt IN LISTS EI_ALL_TARGETS)
    get_target_property(tgt_type ${tgt} TYPE)
    if(tgt_type STREQUAL "EXECUTABLE")
        target_link_options(${tgt}
            PRIVATE "-Wl,--defsym=_min_heap_size=143360")
    endif()
endforeach()

# CMake's Ninja generator rewrites a compiler path containing spaces into its
# 8.3 short form, and xc32-g++.exe exits with code 2 and no message when run
# as XC32-G~1.EXE. Spell out the quoted long path in the C++ rules instead of
# relying on <CMAKE_CXX_COMPILER>.
foreach(rule CMAKE_CXX_COMPILE_OBJECT CMAKE_CXX_LINK_EXECUTABLE)
    string(REPLACE "<CMAKE_CXX_COMPILER>" "\"${CMAKE_CXX_COMPILER}\"" ${rule} "${${rule}}")
endforeach()

message(STATUS "Edge Impulse SDK includes added successfully")
