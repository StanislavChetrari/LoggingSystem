set(FILE_PATH ${TEST_EXECUTABLE_DIR_PATH}/testLogFile.txt)
file(WRITE ${FILE_PATH} "Already existing content")

set(FILE_SIZE_1 "")
file(SIZE ${FILE_PATH} FILE_SIZE_1)

execute_process(COMMAND ${TEST_EXECUTABLE_PATH} ${FILE_PATH} TIMEOUT 1000 RESULT_VARIABLE exec_status)

set(FILE_SIZE_2 "")
file(SIZE ${FILE_PATH} FILE_SIZE_2)

if(${FILE_SIZE_2} LESS_EQUAL ${FILE_SIZE_1})
    # Write fatal error to make it stop and return 1 code, otherwise will return 0 code.
    message(FATAL_ERROR "There was nothing appended to the file!")
endif()

if(EXISTS ${FILE_PATH})
    file(REMOVE ${FILE_PATH})
endif()

if(NOT ${exec_status} STREQUAL "0")
    # Write fatal error to make it stop and return 1 code, otherwise will return 0 code.
    message(FATAL_ERROR "Test failed!")
endif()
