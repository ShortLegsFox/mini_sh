cmake_minimum_required(VERSION 3.10)
project(mini_sh C)

set(CMAKE_C_STANDARD 99)
add_compile_definitions(_POSIX_C_SOURCE=200809L)

# Directories
set(SRC_DIR src)
set(INC_DIR include)
set(BIN_DIR bin)
set(DOC_DIR doc)
set(GCOV_DIR gcov)

# Compiler and Flags
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-O0 --coverage -Wall -g")

# Include directories
include_directories(${INC_DIR})

# Source files
file(GLOB SRC_FILES ${SRC_DIR}/*.c)
file(GLOB BUILTINS_FILES ${SRC_DIR}/builtins/*.c)
file(GLOB EXECUTORS_FILES ${SRC_DIR}/executor/*.c)
file(GLOB PARSERS_FILES ${SRC_DIR}/parser/*.c)

# Combine the source files into one list
list(APPEND SRC_FILES ${BUILTINS_FILES})
list(APPEND SRC_FILES ${EXECUTORS_FILES})
list(APPEND SRC_FILES ${PARSERS_FILES})

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR})

# Add Executable
add_executable(mini_sh ${SRC_FILES}
        src/utils/utils.c
        src/builtins/export.c)
target_compile_options(mini_sh PRIVATE -Wall)
target_include_directories(mini_sh PRIVATE ${INC_DIR})

# GCov Target
add_executable(mini_sh_cov ${SRC_FILES}
        src/builtins/export.c)
target_compile_options(mini_sh_cov PRIVATE --coverage -O0 -Wall -g)
target_link_libraries(mini_sh_cov gcov)

# Doxygen Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/${DOC_DIR})
    set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/${DOC_DIR})
    configure_file(${DOC_DIR}/doxygen.conf ${CMAKE_BINARY_DIR}/doxygen.conf @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxygen.conf
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

# Clean Up
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${GCOV_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOC_DIR}/latex
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOC_DIR}/html
    COMMENT "Cleaning up build artifacts"
)

# Packaging
add_custom_target(package
    COMMAND ${CMAKE_COMMAND} -E tar cfv archive_mini_sh.tar.gz ${SRC_DIR} ${INC_DIR} ${DOC_DIR}
    COMMENT "Packaging project"
)
