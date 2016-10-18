cmake_minimum_required(VERSION 3.6)
project(CppUser)

file(GLOB SOURCE_FILES *.cpp *.h)

include_directories(../SDK/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -std=c++14)
target_link_libraries(${PROJECT_NAME} SDK)