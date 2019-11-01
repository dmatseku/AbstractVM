cmake_minimum_required(VERSION 3.14)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Ofast")

add_executable(AbstractVM main.cpp Operand/eOperandType.hpp Operand/Operand.hpp Operand/Operand.inl
        Operand/IOperand.hpp Factory/Factory.cpp Factory/Factory.hpp VM/VM.cpp VM/VM.hpp File/File.cpp
        File/File.hpp File/File_operations.cpp File/File_commands.cpp)