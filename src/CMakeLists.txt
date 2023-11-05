cmake_minimum_required(VERSION 3.5)
project (BARES VERSION 1.0.0 LANGUAGES CXX )

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
#set( PREPROCESSING_FLAGS  "-D PRINT -D DEBUG -D CASE="WORST" -D ALGO="QUAD"')
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#=== Main App ===

#Include dir
include_directories( libs )
add_executable(bares
    "core/bares_manager.cpp"
    "core/calculate.h"
    "core/parser.cpp"
    "core/main.cpp"
    "libs/messages.cpp"
    "libs/tokenizer.cpp"
    # "libs/data_structs.cpp"
    "libs/data_structs.h"

)

target_compile_features( bares PUBLIC cxx_std_17 )