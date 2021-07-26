cmake_minimum_required(VERSION 3.20.2)
project(object-detection-project)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(webcam webcam.cpp)
target_link_libraries(webcam ${OpenCV_LIBS})