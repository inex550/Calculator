cmake_minimum_required(VERSION 3.12)

project(NotationLib)

set(NOTATION_PUBLIC_INCLUDES
    includes/notation/leklist.h
    includes/notation/leknode.h
    includes/notation/parser.h
)

set(NOTATION_SOURCES
    src/notation/leklist.cpp
    src/notation/leknode.cpp
    src/notation/parser.cpp
    src/notation/parserUtils.cpp
    src/notation/parserUtils.h
)

add_library(notation_lib STATIC
    ${NOTATION_PUBLIC_INCLUDES}
    ${NOTATION_PRIVATE_INCLUDES}
    ${NOTATION_SOURCES}
)

target_include_directories(notation_lib PUBLIC includes)