cmake_minimum_required(VERSION 3.5)

project(untitled1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem program_options system )
add_subdirectory(modules/FaceDetection)
#add_subdirectory(modules/simpleDll)

#link_directories(dll/simpledll)
#link_directories(dll/fd)


add_executable(untitled1 main.cpp watcher.h threadpool.h threadpool.cpp)
target_link_libraries(untitled1 PRIVATE ${OpenCV_LIBS} Boost::filesystem Boost::program_options Boost::system )
#target_link_libraries(untitled1 PRIVATE simpleDll faceDetection )
#target_link_libraries(untitled1 PUBLIC simpleDll )
target_link_libraries(untitled1 PUBLIC faceDetection )



#add_executable(untitled1_2 main_2.cpp watcher.h)
#target_link_libraries(untitled1_2  ${OpenCV_LIBS} Boost::filesystem Boost::program_options)
