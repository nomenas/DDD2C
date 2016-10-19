project(CSDK)

file(GLOB SOURCE_FILES src/*.cpp include/CSDK/*.h)

include_directories(../SDK/include)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} SDK)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -std=c++14)