cmake_minimum_required(VERSION 3.23)
project(WikiApp)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR /usr/local/include/boost)
set(Boost_LIBRARY_DIR /usr/local/include/boost/libs)

find_package(Boost REQUIRED COMPONENTS thread system)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(WikiApp main.cpp client.h)
target_include_directories(WikiApp PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(WikiApp ${Boost_LIBRARIES} )

