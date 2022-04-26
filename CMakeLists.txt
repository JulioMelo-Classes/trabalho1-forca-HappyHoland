cmake_minimum_required(VERSION 3.5)
project(Forca_testes_e_programa VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 11)
#--------------------------------

### [1] Application target
# configura o diretório contendo os .h, assim você pode incluílos apenas com include "arquivo.h"
include_directories( include )

### [2] Test engine
# includes do test manager

# Cria um executável com nome "program" com base no main.cpp
set( APP_NAME "forca" )
add_executable( ${APP_NAME}
                src/main.cpp
                src/Forca.cpp )

set( TESTS "tests" )
add_executable( ${TESTS}
                tests/main.cpp
                src/Forca.cpp
                test_manager/src/test_manager.cpp )
target_include_directories( ${TESTS} PUBLIC test_manager/include)

# define C++11 standard
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${TESTS} PROPERTY CXX_STANDARD 14)

add_custom_target(
    run_tests
    COMMAND ${TESTS}
    DEPENDS ${TESTS}
)

add_custom_target(
    run
    COMMAND ${APP_NAME} "palavras.txt" "scores.txt"
    DEPENDS ${APP_NAME}
)
