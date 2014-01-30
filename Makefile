# Rooshil Patel
# 1255318
# Assignment 1
# CMPUT 379

memscantest: memchunk.o memscantest.o
	gcc -Wall -m32 -o memscantest memchunk.o memscantest.o

memchunk.o: memchunk.c memchunk.h
	gcc -Wall -m32 -c memchunk.c

memscantest.o: memscantest.c memchunk.h
	gcc -Wall -m32 -c memscantest.c

clean:
	rm -f *.o memscantest core
