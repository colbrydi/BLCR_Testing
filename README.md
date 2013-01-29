BLCR_Testing
============

We are having trouble with BLCR zeroing out the memory of a program after running.  This example contains a simle program that demonstrates the bug we are seeing.  To run the test type the following:

make
./blcr_static_dynamictest.sh

The test allocates a large memory space and sets a large chunk of the space to 1.  If the program is checkpointed and resatarted then some of the ones turn into zeros.  Running the test as is will fail. Reducing the allocated space of memory will make this work.

 
