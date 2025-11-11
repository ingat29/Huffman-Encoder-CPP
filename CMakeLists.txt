cmake_minimum_required(VERSION 3.30)
project(OOPEC2)

set(CMAKE_CXX_STANDARD 20)

add_executable(HuffmanEncoder main.cpp
        Utils.cpp
        Utils.h
        Node.cpp
        Node.h
        PriorityQueue.cpp
        PriorityQueue.h
        BitPath.cpp
        BitPath.h
        Header.cpp
        Header.h
)
add_executable(HuffmanDecoder main2.cpp
        Utils.cpp
        Utils.h
        Node.cpp
        Node.h
        PriorityQueue.cpp
        PriorityQueue.h
        BitPath.cpp
        BitPath.h
        Header.cpp
        Header.h
)
