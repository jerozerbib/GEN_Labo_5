cmake_minimum_required(VERSION 3.14)
project(GEN_Labo5)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        GEN_Labo5
        src/main.cpp
        src/Customer.cpp
        src/Customer.h
        src/Movie.cpp
        src/Movie.h
        src/Rental.h
)