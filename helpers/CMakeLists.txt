cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem program_options system thread )

add_library(poolwraper threadpoolwraper.cpp)
target_link_libraries(poolwraper Boost::system Boost::thread)

add_library(facesaver facesaver.h facesaver.cpp )
target_link_libraries(facesaver Boost::filesystem Boost::system ${OpenCV_LIBS} )
