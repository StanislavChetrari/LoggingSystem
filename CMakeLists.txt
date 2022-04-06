cmake_minimum_required(VERSION 3.12)

include(GenerateExportHeader)
include(CMakeUtils/AddFile.cmake)

project(LoggingSystem
		VERSION 1.0
		DESCRIPTION "Logging system to use in my private projects."
		LANGUAGES CXX)

AddFile(SOURCE_FILES Src Src/lsLogger.cpp)
AddFile(SOURCE_FILES Src Src/lsConsoleOutput.cpp)
AddFile(SOURCE_FILES Src Src/lsTextFileOutput.cpp)

AddFile(HEADER_FILES Src Src/lsLogger.hpp)
AddFile(HEADER_FILES Src Src/lsIOutput.hpp)
AddFile(HEADER_FILES Src Src/lsConsoleOutput.hpp)
AddFile(HEADER_FILES Src Src/lsTextFileOutput.hpp)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})
generate_export_header(${CMAKE_PROJECT_NAME})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_11)
