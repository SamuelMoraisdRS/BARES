
# BARES

This project is an implementation of a simple arithmetic expression evaluator made as a part of my Programming I course, under the guidance of professor Selan Rodrigues do Santos.

# About the Program

The BARES CLI application aims to solve simple arithmetic expressions. The program supports:

* The **+**, **-**, __*__, **/**, **^** and **%** operations, accounting for their due precedences.
* Operations with integer values between -32.768 and 32.767. 

# What was learned

The making of this project involved the usage of these attributes:

* OOP;
* Implementation and usage of the *queue* and *stack* data structures;
* String formatting and manipulation;
* Extensive exception handling;
* Recursive chain of methods to correctly convert the expressions to their postfix representation and to spot syntactical errors, according to the [EBNF Grammar](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form).

# Compiling and running
 This project can be compiled with the [CMake build tool](https://cmake.org/). To do so, follow the steps:

1. From the `/src` directory (which contains the CMake script), insert this command line into the terminal to configurate the project:

    `cmake -S . -B build`

2. Afterwards, you can compile by inserting:

    `cmake --build build`

3. Now, from the new `build` directory, you can run the executable by only using the command:

    `./bares`
--------

