cmake_minimum_required(VERSION 3.3)
project(MED_projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    functions.cpp
    functions.h
    main.cpp menu.cpp menu.h fileUtils.h fileUtils.cpp)

add_executable(MED_projekt ${SOURCE_FILES})