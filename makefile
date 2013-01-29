#original makefile used gcc, however since BLCR libraries are not fully ISO99 C compliant i changed it to g++ and this seams to help.  
CC=g++

all:	blcr_static_test.exe blcr_dynamic_test.exe 

blcr_static_test.exe: blcr_memtest.cpp
	${CC} -g -D USE_STATIC -o blcr_static_test.exe blcr_memtest.cpp 

blcr_dynamic_test.exe:	blcr_memtest.cpp
	${CC} -g -o blcr_dynamic_test.exe blcr_memtest.cpp

clean: 
	rm *.exe
