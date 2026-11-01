include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(wolfmqtt_demo_sam_e54_xpro_library_list )

# Handle files with suffix s, for group sam_e54_xpro-XC32
if(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_assemble)
add_library(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assemble OBJECT ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_assemble})
    wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assemble_rule(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assemble)
    list(APPEND wolfmqtt_demo_sam_e54_xpro_library_list "$<TARGET_OBJECTS:wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assemble>")

endif()

# Handle files with suffix S, for group sam_e54_xpro-XC32
if(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assembleWithPreprocess OBJECT ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_assembleWithPreprocess})
    wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assembleWithPreprocess_rule(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assembleWithPreprocess)
    list(APPEND wolfmqtt_demo_sam_e54_xpro_library_list "$<TARGET_OBJECTS:wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group sam_e54_xpro-XC32
if(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_compile)
add_library(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile OBJECT ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_compile})
    wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_rule(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile)
    list(APPEND wolfmqtt_demo_sam_e54_xpro_library_list "$<TARGET_OBJECTS:wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile>")

endif()

# Handle files with suffix cpp, for group sam_e54_xpro-XC32
if(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_compile_cpp)
add_library(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp OBJECT ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_compile_cpp})
    wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp_rule(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp)
    list(APPEND wolfmqtt_demo_sam_e54_xpro_library_list "$<TARGET_OBJECTS:wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_compile_cpp>")

endif()

# Handle files with suffix [cC], for group sam_e54_xpro-XC32
if(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_dependentObject)
add_library(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_dependentObject OBJECT ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_dependentObject})
    wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_dependentObject_rule(wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_dependentObject)
    list(APPEND wolfmqtt_demo_sam_e54_xpro_library_list "$<TARGET_OBJECTS:wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_dependentObject>")

endif()


# Main target for this project
add_executable(wolfmqtt_demo_sam_e54_xpro_image_0LfiGjZF ${wolfmqtt_demo_sam_e54_xpro_library_list})

set_target_properties(wolfmqtt_demo_sam_e54_xpro_image_0LfiGjZF PROPERTIES
    OUTPUT_NAME "sam_e54_xpro"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${wolfmqtt_demo_sam_e54_xpro_output_dir}")
target_link_libraries(wolfmqtt_demo_sam_e54_xpro_image_0LfiGjZF PRIVATE ${wolfmqtt_demo_sam_e54_xpro_sam_e54_xpro_XC32_FILE_TYPE_link})
# Add the link options from the rule file.
wolfmqtt_demo_sam_e54_xpro_link_rule( wolfmqtt_demo_sam_e54_xpro_image_0LfiGjZF)

# Add bin2hex target for converting built file to a .hex file.
string(REGEX REPLACE [.]elf$ .hex wolfmqtt_demo_sam_e54_xpro_image_name_hex ${wolfmqtt_demo_sam_e54_xpro_image_name})
add_custom_target(wolfmqtt_demo_sam_e54_xpro_Bin2Hex ALL
    COMMAND ${MP_BIN2HEX} \"${wolfmqtt_demo_sam_e54_xpro_output_dir}/${wolfmqtt_demo_sam_e54_xpro_image_name}\"
    BYPRODUCTS ${wolfmqtt_demo_sam_e54_xpro_output_dir}/${wolfmqtt_demo_sam_e54_xpro_image_name_hex}
    COMMENT "Convert built file to .hex")
add_dependencies(wolfmqtt_demo_sam_e54_xpro_Bin2Hex wolfmqtt_demo_sam_e54_xpro_image_0LfiGjZF)




