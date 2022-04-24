include(../../CMakeUtils/AddFile.cmake)

AddFile(OUTPUT_MSGS_SOURCE_FILES Src Src/Main.cpp)

add_executable(OutputsHaveCorrectMessageTypes ${OUTPUT_MSGS_SOURCE_FILES})
target_link_libraries(OutputsHaveCorrectMessageTypes ${LOGGING_SYSTEM_TARGET_NAME})
target_include_directories(OutputsHaveCorrectMessageTypes PRIVATE ${LOGGING_SYSTEM_INCLUDE_DIRS})
add_test(NAME OutputsHaveCorrectMessageTypes COMMAND OutputsHaveCorrectMessageTypes)
