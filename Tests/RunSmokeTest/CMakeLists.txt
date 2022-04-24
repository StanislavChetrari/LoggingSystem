include(../../CMakeUtils/AddFile.cmake)

AddFile(SMOKE_TEST_SOURCE_FILES Src Src/Main.cpp)

add_executable(RunSmokeTest ${SMOKE_TEST_SOURCE_FILES})
target_link_libraries(RunSmokeTest ${LOGGING_SYSTEM_TARGET_NAME})
target_include_directories(RunSmokeTest PRIVATE ${LOGGING_SYSTEM_INCLUDE_DIRS})
add_test(NAME RunSmokeTest COMMAND RunSmokeTest)
