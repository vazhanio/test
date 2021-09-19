cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED)
set(SOURCE_FILES fd.cpp
                 fd.h)
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(simpleDll SHARED ${SOURCE_FILES})
target_link_libraries(simpleDll  ${OpenCV_LIBS})

