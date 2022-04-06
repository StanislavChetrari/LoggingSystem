# This function adds a source/header file to the project.
# SRCS_VAR   - is the variable where all source files are written
# PROJ_GROUP - group in the project. For example filters in Visual Studio or other IDE. This group folders must be separated by \\
# FILE_PATH  - file to be added
# Example call AddSrcFile(SRCS YLE\\Src Src/main.c)
function(AddFile SRCS_VAR PROJ_GROUP FILE_PATH)
	#message("source_group(${PROJ_GROUP} FILES ${FILE_PATH})")
	source_group(${PROJ_GROUP} FILES ${FILE_PATH})
	set(${SRCS_VAR} ${${SRCS_VAR}} ${FILE_PATH} PARENT_SCOPE)
endfunction()
