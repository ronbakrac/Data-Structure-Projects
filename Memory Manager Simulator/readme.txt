Memory manager simulation. Program allows initalizing an amount of memory and allocate chunks from it. Memory model is essentially a linked list where each allocation is a new node in the linked list. Deallocated spaces check left and right pointers to see if space is free and if so then merge the spaces together.

Running the program will print out a series of test initalizations, allocations, deallocations, list printing, etc. You may edit the test cases in main if needed.

Tested on Linux only. Simply call 'make' to create an executable file, or compile all three .cpp files to create application.