cmake_minimum_required(VERSION 3.10)

project(Barnsley_farn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
	Message( FATAL_ERROR "Source and build directories are identical!")
endif()

set(SRC_FILES main.cpp worker.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
