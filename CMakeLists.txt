cmake_minimum_required(VERSION 4.0)
project(Final-project-csc-275)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Final-project-csc-275
        main.cpp
        Vehicle.cpp
        Vehicle.h
        Car.cpp
        Car.h
        Customer.cpp
        Customer.h
        Rental.cpp
        Rental.h
        CarRentalSystem.cpp
        CarRentalSystem.h
)
