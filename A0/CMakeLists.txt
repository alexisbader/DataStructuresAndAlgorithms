cmake_minimum_required(VERSION 3.21)
project(template)

## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# create the main executable
## add additional .cpp files if needed
add_executable(bme122-a0 bme122-a0.cpp)
