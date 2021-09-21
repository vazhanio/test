cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}  "-Wl,--copy-dt-needed-entries")
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)
set(SOURCE_FILES facedetector.cpp
                 facedetector.h)

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(facedetector SHARED facedetector.cpp )
target_link_libraries(facedetector  ${OpenCV_LIBS})

add_executable(test_facedetector main_test.cpp)
target_link_libraries(test_facedetector  facedetector ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY})
set_target_properties( test_facedetector PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

