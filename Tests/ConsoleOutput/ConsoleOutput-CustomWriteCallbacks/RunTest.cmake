execute_process(COMMAND ${TEST_EXECUTABLE_PATH} ${FILE_PATH} TIMEOUT 1000 RESULT_VARIABLE exec_status)

if(NOT ${exec_status} STREQUAL "0")
    # Write fatal error to make it stop and return 1 code, otherwise will return 0 code.
    message(FATAL_ERROR "Test failed!")
endif()
