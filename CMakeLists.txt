cmake_minimum_required(VERSION 3.29)
project(SimpleBox)


cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT DEFINED ENV{HFS})
    message(FATAL_ERROR "HFS environment variable not set. Please set it to your Houdini installation directory.")
endif()

set(Houdini_PATH "$ENV{HFS}")
set(Houdini_DIR ${Houdini_PATH}/toolkit/cmake)
find_package(Houdini REQUIRED)


add_library(SimpleBox SHARED SimpleBox.cpp )

set_target_properties(SimpleBox PROPERTIES 
    PREFIX ""
    SUFFIX ".dll"
)

target_link_libraries(SimpleBox
    Houdini
)   