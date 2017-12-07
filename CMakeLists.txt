cmake_minimum_required(VERSION 3.0)
project(Assignment6_belady)

if(CMAKE_COMPILER_IS_GNUCXX)
	set (CMAKE_CXX_FLAGS "-std=c++11 -lpthread -Ofast ${CMAKE_CXX_FLAGS}")
endif()

add_executable(
Assignment6_belady beladyAnomalyFast.cpp
)
