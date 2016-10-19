cmake_minimum_required(VERSION 3.6)
project(ClientC)

file(GLOB SOURCE_FILES *.c)

include_directories(../CSDK/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} CSDK)