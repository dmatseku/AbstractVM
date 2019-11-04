cmake_minimum_required(VERSION 3.14)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Ofast")

add_executable(AbstractVM main.cpp Factory/Factory.cpp VM/VM.cpp File/File.cpp
        File/File_operations.cpp File/File_other_commands.cpp File/File_arithmetic_commands.cpp)