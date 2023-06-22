cmake_minimum_required(VERSION 3.21)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager main.cpp password.cpp password.h coder.cpp coder.h program.cpp program.h)
