set(DEPENDENT_MP_BIN2HEXwolfmqtt_demo_sam_e54_xpro_0LfiGjZF "c:/Program Files/Microchip/xc32/v5.10/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFwolfmqtt_demo_sam_e54_xpro_0LfiGjZF ${CMAKE_CURRENT_LIST_DIR}/../../../../out/wolfmqtt_demo/sam_e54_xpro.elf)
set(DEPENDENT_TARGET_DIRwolfmqtt_demo_sam_e54_xpro_0LfiGjZF ${CMAKE_CURRENT_LIST_DIR}/../../../../out/wolfmqtt_demo)
set(DEPENDENT_BYPRODUCTSwolfmqtt_demo_sam_e54_xpro_0LfiGjZF ${DEPENDENT_TARGET_DIRwolfmqtt_demo_sam_e54_xpro_0LfiGjZF}/${sourceFileNamewolfmqtt_demo_sam_e54_xpro_0LfiGjZF}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRwolfmqtt_demo_sam_e54_xpro_0LfiGjZF}/${sourceFileNamewolfmqtt_demo_sam_e54_xpro_0LfiGjZF}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXwolfmqtt_demo_sam_e54_xpro_0LfiGjZF} --image ${DEPENDENT_DEPENDENT_TARGET_ELFwolfmqtt_demo_sam_e54_xpro_0LfiGjZF} --image-generated-c ${sourceFileNamewolfmqtt_demo_sam_e54_xpro_0LfiGjZF}.c --image-generated-h ${sourceFileNamewolfmqtt_demo_sam_e54_xpro_0LfiGjZF}.h --image-copy-mode ${modewolfmqtt_demo_sam_e54_xpro_0LfiGjZF} --image-offset ${addresswolfmqtt_demo_sam_e54_xpro_0LfiGjZF} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRwolfmqtt_demo_sam_e54_xpro_0LfiGjZF}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFwolfmqtt_demo_sam_e54_xpro_0LfiGjZF})
add_custom_target(
    dependent_produced_source_artifactwolfmqtt_demo_sam_e54_xpro_0LfiGjZF 
    DEPENDS ${DEPENDENT_TARGET_DIRwolfmqtt_demo_sam_e54_xpro_0LfiGjZF}/${sourceFileNamewolfmqtt_demo_sam_e54_xpro_0LfiGjZF}.c
    )
