set(FILE_PATH ${TEST_EXECUTABLE_DIR_PATH}/testLogFile.txt)

execute_process(COMMAND ${TEST_EXECUTABLE_PATH} ${FILE_PATH} TIMEOUT 1000 RESULT_VARIABLE exec_status)

if(NOT EXISTS ${FILE_PATH})
    # Write fatal error to make it stop and return 1 code, otherwise will return 0 code.
    message(FATAL_ERROR "File was not created!")
endif()

if(EXISTS ${FILE_PATH})
    file(REMOVE ${FILE_PATH})
endif()

if(NOT ${exec_status} STREQUAL "0")
    # Write fatal error to make it stop and return 1 code, otherwise will return 0 code.
    message(FATAL_ERROR "Test failed!")
endif()
