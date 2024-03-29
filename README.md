# AbstractVM #

42 School project.

This is a virtual machine based on storing on the stack and calculating basic arithmetic expressions.

## Compilation ##

Clone this repository and run compilation with cmake:
    
    mkdir build && cd build
    cmake ../
    make
    
## Usage ##

The program can be run without arguments, then reading will come from standard input:

    ./AbstractVM

The program can also be run with arguments:

    ./AbstractVM [-in | *path to file*]...
    
Where -in is a flag that requires reading from standard input.

## Syntax ##

AbstractVM is similar to many assembler languages and is composed of a series of instructions, one instruction per line. However, unlike other languages, it has a limited type system.

Here is a list of available instructions:

Instruction         | Details
--------------------|-----------
push \*type\*(n)    | Pushes the value v at the top of the stack.
pop                 | Unstacks the value from the top of the stack.
dump                | Displays each value of the stack, from the most recent one to the oldest one.
assert \*type\*(n)  | Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction.
print               | Asserts that the value at the top of the stack is an 8-bit integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.
exit                | Terminate the execution of the instructions.
Comments            | Comments start with a ’;’ and finish with a newline.
EOF(in stdin)       | Denoted as ";;"
add sub mul div mod \[\*type\*(n)\]     | Unstacks the first two values on the stack or unstacks the first value on the stack and next one from the argument, then adds/subtracts/multiplies/divides / calculates the modulus and stacks the result.

In this list, \*type\* is one of five types:

Type      | Details 
----------|--------------------
int8(n)   | Creates an 8-bit integer with value n.
int16(n)  | Creates an 16-bit integer with value n.
int32(n)  | Creates an 32-bit integer with value n.
float(n)  | Creates a float with value n.
double(n) | Creates a double with value n.
