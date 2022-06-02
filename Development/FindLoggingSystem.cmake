# Input variables:
#   LoggingSystem_PATHS - Paths where to search the library in addition to the standard ones.

if(DEFINED ENV{LoggingSystem_PATHS})
    set(LoggingSystem_PATHS "$ENV{LoggingSystem_PATHS};${LoggingSystem_PATHS}")
endif()

set(LoggingSystem_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
	${LoggingSystem_PATHS})

if(NOT LoggingSystem_INCLUDE_DIR)
    find_path(LoggingSystem_INCLUDE_DIR_TEMP lsLogger.hpp
        PATH_SUFFIXES include/LoggingSystem include LoggingSystem
        PATHS ${LoggingSystem_SEARCH_PATHS})

    find_path(LoggingSystem_export_INCLUDE_DIR_TEMP loggingsystem_export.h
        PATH_SUFFIXES include/LoggingSystem include LoggingSystem
        PATHS ${LoggingSystem_SEARCH_PATHS})
endif()

if(NOT LoggingSystem_LIBRARY)
    find_library(LoggingSystem_LIBRARY_TEMP
        NAMES LoggingSystem
        PATH_SUFFIXES lib64 lib
        PATHS ${LoggingSystem_SEARCH_PATHS})
endif()

if(LoggingSystem_INCLUDE_DIR_TEMP AND LoggingSystem_LIBRARY_TEMP)
    # ================================================
    # LoggingSystem_LIBRARY
    # ================================================
    set(LoggingSystem_LIBRARY ${LoggingSystem_LIBRARY_TEMP} CACHE STRING "LoggingSystem library path")

    # ================================================
    # LoggingSystem_INCLUDE_DIR
    # ================================================
    set(LoggingSystem_INCLUDE_DIR ${LoggingSystem_INCLUDE_DIR_TEMP} CACHE STRING "LoggingSystem include path")

    # ================================================
    # LoggingSystem_INCLUDE_DIRS
    # ================================================
    if(LoggingSystem_export_INCLUDE_DIR_TEMP)
        set(LoggingSystem_INCLUDE_DIRS "${LoggingSystem_INCLUDE_DIR_TEMP};${LoggingSystem_export_INCLUDE_DIR_TEMP}" CACHE STRING "LoggingSystem include paths")
    else()
        set(LoggingSystem_INCLUDE_DIRS ${LoggingSystem_INCLUDE_DIR_TEMP} CACHE STRING "LoggingSystem include paths")
    endif()

    # ================================================
    # LoggingSystem_LIBRARIES
    # ================================================
    set(LoggingSystem_LIBRARIES "${LoggingSystem_LIBRARY}" CACHE STRING "LoggingSystem library paths")

endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LoggingSystem REQUIRED_VARS LoggingSystem_INCLUDE_DIR LoggingSystem_LIBRARY)
