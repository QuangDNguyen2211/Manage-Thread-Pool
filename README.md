This 'README.md' file is based on the source: https://github.com/ProfAvery/cpsc351/tree/main/project3
# Team Members: 
Vinh Tran (Email: kimvinh@csu.fullerton.edu) 
Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
# Course: CPSC 351 - 04
# Professor: Kenytt Avery

# Project 3 - Designing a Thread Pool

This project is to create and manage a thread pool which contains 10 threads to execute tasks submitted to the pool. We implemented
the queue dynamatically by using a linked list. Therefore, its size is full when a memory allocation error occurs. 

## "CPSC-351-Project3.tar.gz" Contents:

- `README.md` (this file)

- `Makefile` (instruct how to compile and run the program)

- `client.cpp` (client program that uses thread pool)

- `threadpool.cpp` (implementation of thread pool)

- `threadpool.h` (header file containing class definition)

## Makefile

To run the make file, enter `make`

To run the example program, enter `./example`

To check for memory leaks, enter `make check-leaks`

To check for race conditions, enter `make check-threads`

To check for both, `make check`
