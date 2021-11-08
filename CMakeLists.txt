cmake_minimum_required(VERSION 3.10)

project(HA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CIMG_H_PATH ${PROJECT_SOURCE_DIR})

if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
    Message( FATAL_ERROR "Source and build directories are identical!")
endif()

set(SRC_FILES main.cpp Worker.cpp RealProducer.cpp RealConsumer.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} pthread)

# Just change the default value if you want to disable the interactive window based on X11 library
option(YOU_NEED_X "Activates usage of X11 library"  ON)

# Just change the default value if CImg should not use libpng but the default ImageMagick
# (I had problems with ImageMagick, hence the alternative based on libpng)
option(YOU_NEED_PNG "Activates usage of png library" ON)

if(${YOU_NEED_PNG})
    message(STATUS "Looking for libpng ...")

    # Define a prepro variable to control the c++ code
    add_definitions(-DYOU_NEED_PNG)

    # Flags for Cool Image to enable native support for PNG image files, using the PNG library.
    set(CIMG_PNG_CCFLAGS  -Dcimg_use_png)

    # More details in third lecture
    find_package(PNG REQUIRED)

    #
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${PNG_LIBRARY})
    target_compile_definitions(${PROJECT_NAME} PRIVATE cimg_use_png=1)
endif()

if(${YOU_NEED_X})
    message(STATUS "Looking for libx11 ...")

    add_definitions(-DYOU_NEED_X)
    find_package(X11)
    target_link_libraries(${PROJECT_NAME} X11)

endif()