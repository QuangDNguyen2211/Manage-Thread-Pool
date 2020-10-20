This 'README.txt' file is based on 'README.md' from the source: https://github.com/ProfAvery/cpsc351/tree/main/project3
# Team Members: 
Vinh Tran (Email: kimvinh@csu.fullerton.edu)  
Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
# Course: CPSC 351 - 04
# Professor: Kenytt Avery

# Project 3 - Designing a Thread Pool

This project is to create and manage a thread pool which contains 10 threads to execute tasks submitted to the pool. We implemented
the queue dynamatically by using a linked list. Therefore, its size is full when a memory allocation error occurs. 

## "CPSC-351-Project3.tar.gz" Contents:

1. README.md         // this file

2. Makefile          // instruct how to compile and run the program

3. client.cpp        // client program that uses thread pool

4. threadpool.cpp    // implementation of thread pool

5. threadpool.h      // header file containing class definition

## Makefile

To run the make file, command: $ make

To run the program, command: $ ./example            // "example" is the executive file

To check for memory leaks, command: $ make check-leaks

To check for race conditions, command: $ make check-threads

To check for both, command: $ make check
