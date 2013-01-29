//g++ -o blcr_memtest blcr_memtest.cpp 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

struct point {
  double x; // x coordinate of particle's position
  double y; // y coordinate of particle's position
  double z; // z coordinate of particle's position
  double var1[70]; // A value of 65 or greater causes the test to fail
  //double var1[60]; // This size causes test to work
};

int main()
{
	//Set up a file to use as a flag to terminate the infinate loop
	FILE* fp;
	fp = fopen("still_running", "a");
	fclose(fp);
	int file_exists=1;

	//set up some timers for busy wait
	static clock_t start_time;
	static clock_t end_time;
	static clock_t nested_start_time;
	static struct tms start_cpu;
	static struct tms end_cpu;
	unsigned total_time, nested_time, loop_count = 1;
	float result = rand() % 100 + 1;

	//number of busy wait loops between checking memory flag
	int loops = 10;

	//Allocate a modest size of memory
	size_t M = 8000000; // Total number of particles
	//size_t M = 80000; // Total number of particles
	
//NOTE This "If NOT Defined"
#ifndef USE_STATIC
	//Dynamic allocation of memory
	printf("Using dynamic Memory\n");
	fflush(stdout);
	struct point* Particles = (point *) malloc (M*sizeof(point));
#else	
	//Static allocation of memory 
	printf("Using static Memory\n");
	fflush(stdout);
	struct point Particles[8000000];
	//  struct point Particles[80000];
#endif
	
	//Print out the memory used and demonstrate the overflow of the unsigned int 	
	printf("Memory requested for this test. If these numbers do not agree then the test will fail\n");
	fflush(stdout);
	unsigned int sint=M*((double) sizeof(point));
	printf("uint MEMORY = %zu Bytes\n", sint);
	size_t ssize=M*((double) sizeof(point));
	printf("size MEMORY = %zu Bytes\n", ssize);
	double size=M*((double) sizeof(point))/1000.0/1000.0/1000.0;
	printf("dble MEMORY = %f GB\n", size);
	fflush(stdout);

	//set flag to detect memory error
	//all values for y should be one
	for(int i = 0; i < M; i++)
		Particles[i].y = 1;

	//main loop (does not change values of y) 
	for(int d = 0; d<10; d++)
	{
		printf("TEST STARTING (PASS %d)\n", d);
		printf("************************\n");		
		fflush(stdout);
		
		//busy work that dosn't really do anything	
		{
			//int rand_num;
			for(int i = 0; i < loops; i++)
			{
				printf("Loop %d\n", i);
				fflush(stdout);	
				sleep(3);
			}		
			//result = rand() % 100 + 1;		
		}
		
		//Check y values, they should not have changed from one
		size_t error = 0;
		printf("Checking Memory\n");		
		fflush(stdout);
		for(int i=0; i<M;i++)
		{
			if(Particles[i].y != 1)
				error++;
		}

		//Report errors 
		if(error > 0)
		{
			printf("ERROR, %u of %u, y is not one\n",error,M);
			fflush(stdout);
			exit(110);
		} else {
			printf("PASSED\n");		
			fflush(stdout);
		}
	
		//Check for still_running file
		fp = fopen("still_running", "w");
		fclose(fp);
		if(fp == NULL) {
			printf("Still_running gone---starting to exit");
			break;
		}
	}
	
	//remove the following if doing a static memory test.
#ifndef USE_STATIC
	free(Particles);
#endif
	printf("***still_running has been removed***\n\n");	
	fflush(stdout);
	return 0;
}



