cmake_minimum_required(VERSION 3.12)

project(LoggingSystem
		VERSION 1.0
		DESCRIPTION "Logging system to use in my private projects."
		LANGUAGES CXX)

include(GenerateExportHeader)
include(CMakeUtils/AddFile.cmake)
include(CTest)

AddFile(SOURCE_FILES Src Src/lsLogger.cpp)
AddFile(SOURCE_FILES Src Src/lsConsoleOutput.cpp)
AddFile(SOURCE_FILES Src Src/lsTextFileOutput.cpp)

AddFile(HEADER_FILES Src Src/lsLogger.hpp)
AddFile(HEADER_FILES Src Src/lsIOutput.hpp)
AddFile(HEADER_FILES Src Src/lsConsoleOutput.hpp)
AddFile(HEADER_FILES Src Src/lsTextFileOutput.hpp)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# ===============================================================================
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})
generate_export_header(${CMAKE_PROJECT_NAME})
# ===============================================================================

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_11)

# ===============================================================================
# For the tests to link to the library.
set(LOGGING_SYSTEM_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Src\;${PROJECT_BINARY_DIR}")
set(LOGGING_SYSTEM_TARGET_NAME ${CMAKE_PROJECT_NAME})
# ===============================================================================

# ===============================================================================
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib)

install(FILES Src/lsLogger.hpp DESTINATION include)
install(FILES Src/lsIOutput.hpp DESTINATION include)
install(FILES Src/lsConsoleOutput.hpp DESTINATION include)
install(FILES Src/lsTextFileOutput.hpp DESTINATION include)
# ===============================================================================

if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()
