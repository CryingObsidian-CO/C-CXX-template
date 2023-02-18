cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# defines targets and sources
add_subdirectory(DataBase)

# main.cpp                                                                      
SET(SRC_LIST ./main.cpp)        
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})                                           

# 配置可执行文件输出目录
add_executable(Blog ${SRC_LIST})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

target_link_libraries(Blog PRIVATE module_DataBase)
