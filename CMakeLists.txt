cmake_minimum_required(VERSION 3.17)
project(CNN)
set(CMAKE_CXX_STANDARD 17)

#include_directories("D:/Environment/OpenCV/opencv/build/include")
set(CMAKE_PREFIX_PATH   D:\\Environment\\OpenCV\\opencv)
set(OpenCV_DIR D:\\Environment\\OpenCV\\opencv\\x64\\vc15\\lib)

find_package(OpenCV REQUIRED)
# 有时候写find_package(OpenCV4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
#如果cmake找不到库就把上面一条换为下面的语句
# include_directories(G:\\opencv\\build\\include\\opencv2})





add_executable(CNN main.cpp Pool.h Conv.h Matrix.h Input.h Full.h Layer.h Processor.h)

target_link_libraries(CNN ${OpenCV_LIBS})