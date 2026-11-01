# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/a19356/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assemble_rule target)
    set(options
        "-g"
        "${ASSEMBLER_PRE}"
        "-mprocessor=ATSAME54P20A"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1"
        "-g,-I${CMAKE_CURRENT_SOURCE_DIR}/../../../sam_e54_xpro.X"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "__DEBUG=1")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../sam_e54_xpro.X")
endfunction()
function(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "-g"
        "${MP_EXTRA_AS_PRE}"
        "${DEBUGGER_NAME_AS_MACRO}"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234"
        "-mprocessor=ATSAME54P20A"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-I${CMAKE_CURRENT_SOURCE_DIR}/../../../sam_e54_xpro.X")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "XPRJ_sam_e54_xpro=sam_e54_xpro")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../sam_e54_xpro.X")
endfunction()
function(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "-x"
        "c"
        "-c"
        "-mprocessor=ATSAME54P20A"
        "-ffunction-sections"
        "-fdata-sections"
        "-O1"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "ARM_ALL_FAST_TABLES"
        PRIVATE "ARM_DSP_CONFIG_TABLES"
        PRIVATE "ARM_FAST_ALLOW_TABLES"
        PRIVATE "ARM_FFT_ALLOW_TABLES"
        PRIVATE "ARM_TABLE_BITREVIDX_FLT_256"
        PRIVATE "ARM_TABLE_REALCOEF_F32"
        PRIVATE "ARM_TABLE_TWIDDLECOEF_F32_256"
        PRIVATE "ARM_TABLE_TWIDDLECOEF_RFFT_F32_512"
        PRIVATE "EIDSP_USE_CMSIS_DSP=1"
        PRIVATE "EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW=4"
        PRIVATE "HAVE_CONFIG_H"
        PRIVATE "WOLFSSL_IGNORE_FILE_WARN"
        PRIVATE "__TARGET_CPU_CORTEX_M4"
        PRIVATE "XPRJ_sam_e54_xpro=sam_e54_xpro")
    target_include_directories(${target}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app_config/non_gui/16K"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src/common"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/third_party_adapter/wolfMQTT/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/DSP/PrivateInclude"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/CMSIS/NN/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/model-parameters"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/ATSAME54P20A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/tflite-model"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfMQTT"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl/wolfssl"
        PRIVATE "${PACK_REPO_PATH}/ARM/CMSIS/5.8.0/CMSIS/Core/Include")
endfunction()
function(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "${DEBUGGER_NAME_AS_MACRO}"
        "-mprocessor=ATSAME54P20A"
        "-frtti"
        "-fexceptions"
        "-fno-check-new"
        "-fenforce-eh-specs"
        "-ffunction-sections"
        "-O1"
        "-fno-common"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG"
        PRIVATE "__TARGET_CPU_CORTEX_M4"
        PRIVATE "EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW=4"
        PRIVATE "EIDSP_USE_CMSIS_DSP=1"
        PRIVATE "XPRJ_sam_e54_xpro=sam_e54_xpro")
    target_include_directories(${target}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app_config/non_gui/16K"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/library/tcpip/src/common"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/config/sam_e54_xpro/third_party_adapter/wolfMQTT/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/flatbuffers/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/gemmlowp"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/edge-impulse-sdk/third_party/ruy"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/model-parameters"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/ATSAME54P20A_DFP"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/CMSIS"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/packs/CMSIS/CMSIS/Core/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/tflite-model"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfMQTT"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/third_party/wolfssl/wolfssl"
        PRIVATE "${PACK_REPO_PATH}/ARM/CMSIS/5.8.0/CMSIS/Core/Include")
endfunction()
function(wolfmqtt_demo_sam_e54_xpro_dependentObject_rule target)
    set(options
        "-mprocessor=ATSAME54P20A"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
endfunction()
function(wolfmqtt_demo_sam_e54_xpro_link_rule target)
    set(options
        "-g"
        "${MP_EXTRA_LD_PRE}"
        "${DEBUGGER_OPTION_TO_LINKER}"
        "${DEBUGGER_NAME_AS_MACRO}"
        "-mprocessor=ATSAME54P20A"
        "-mno-device-startup-code"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST},--script=${wolfmqtt_demo_sam_e54_xpro_LINKER_SCRIPT},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=122960,--gc-sections,-L${CMAKE_CURRENT_SOURCE_DIR}/../../../sam_e54_xpro.X,-Map=mem.map,--memorysummary,memoryfile.xml"
        "-mdfp=${PACK_REPO_PATH}/Microchip/SAME54_DFP/3.8.234")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_sam_e54_xpro=sam_e54_xpro")
endfunction()
