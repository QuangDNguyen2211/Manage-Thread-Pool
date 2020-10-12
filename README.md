# Project 3 - Designing a Thread Pool

These files are a C++ version of the files that support the POSIX
implementation of the thread pool project from *Operating Systems
Concepts, 10th Edition* by Silberschatz, Galvin, and Gagne.

## Source files:

- `client.cpp` (client program that uses thread pool)

- `threadpool.cpp` (implementation of thread pool)

- `threadpool.h` (header file containing class definition)

## Makefile

To run the make file, enter `make`

To run the example program, enter `./example`

To check for memory leaks, enter `make check-leaks`

To check for race conditions, enter `make check-threads`

To check for both, `make check`

### Tips

1. Note that `make check-threads` reports that there is already a possible
   race condition.

   The code is safe to run as-is, but the conflicts reported should help
   you determine where to apply mutex locks.

2. If you are using WSL, `make check-threads` will fail with a
   segmentation fault. To check thread behavior with Helgrind you will
   need to run the code on a standard Linux virtual machine.

