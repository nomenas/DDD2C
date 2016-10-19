cmake_minimum_required(VERSION 3.6)

project(SDK)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp src/*.h)

include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -std=c++14)