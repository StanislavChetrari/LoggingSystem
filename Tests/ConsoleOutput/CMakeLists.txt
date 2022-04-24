include(../../CMakeUtils/AddFile.cmake)

AddFile(CONSOLE_OUTPUT_SOURCE_FILES Src Src/Main.cpp)

add_executable(ConsoleOutput ${CONSOLE_OUTPUT_SOURCE_FILES})
target_link_libraries(ConsoleOutput ${LOGGING_SYSTEM_TARGET_NAME})
target_include_directories(ConsoleOutput PRIVATE ${LOGGING_SYSTEM_INCLUDE_DIRS})
add_test(NAME ConsoleOutput COMMAND ConsoleOutput)
