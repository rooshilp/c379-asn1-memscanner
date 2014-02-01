/* Rooshil Patel
 * 1255318
 * Assignment 1
 * CMPUT 379
 */

#include <signal.h>
#include <setjmp.h>

#include <stdio.h>
#include <unistd.h>

#include "memchunk.h"

static sigjmp_buf env;

/*
 * get_mem_layout scans the 32bit memory space for readable or read/writeable
 * chunks of memory, saving the start locations, length and access
 * type of these chunks in memchunk structs within the chunk_list
 * array as well as returning an int of the total number of chunks.
 */

int get_mem_layout (struct memchunk *chunk_list, int size) {
        int pageSize = getpagesize();
        int chunkCount = 0;
	int listIndex = -1;
	void *memLocation;
	memLocation = (void*) pageSize;
	
	/*
	 * As the memory location increments, it will eventually
	 * reach a NULL location, terminating the while loop.
	 */

	while (memLocation != NULL) {
		int access;
		int lastAccess;
		access = check_access(memLocation);

		/*
		 * Using a various amount of nested if and else statements
		 * the memory location currently accessed is identified
		 * and tested to see if it is not part of a chunk,
		 * a continuation of an existing chunk or part of
		 * a new chunk. An index identifier also 
		 * examines if we go out of bounds of 
		 * chunk_list, only incrementing the value of
		 * chunkCount, the return value, instead.
		 */

		if (listIndex + 1 == size) {
			if (access == -1) {
				if (lastAccess == access) {
					memLocation += pageSize;
					continue;
				}
				else {
					chunkCount++;
					lastAccess = -1;
					memLocation += pageSize;
				}
			}
				
			if (access == 0) {
				if (lastAccess == access) {
					memLocation += pageSize;
				}
				else {
					if (lastAccess == 1) {
						chunkCount++;
					}
					lastAccess = 0;
					memLocation += pageSize;
				}
			}	
	
			if (access == 1) {
				if (lastAccess == access) {
					memLocation += pageSize;
				}
				else {
					if (lastAccess == 0) {
						chunkCount++;
					}
					listIndex++;
					lastAccess = 1;
					memLocation += pageSize;
				}
			}
		}

		else {		
			if (access == -1) {
				if (lastAccess == access) {
					memLocation += pageSize;
					continue;
				}
				else {
					chunkCount++;
					lastAccess = -1;
					memLocation += pageSize;
				}
			}
				
			if (access == 0) {
				if (lastAccess == access) {
					chunk_list[listIndex].length += pageSize;
					memLocation += pageSize;
				}
				else {
					if (lastAccess == 1) {
						chunkCount++;
					}
					listIndex++;
					lastAccess = 0;
					chunk_list[listIndex].start = memLocation;
					chunk_list[listIndex].length = 0;
					chunk_list[listIndex].length += pageSize;
					chunk_list[listIndex].RW = 0;
					memLocation += pageSize;
				}
			}	
	
			if (access == 1) {
				if (lastAccess == access) {
					chunk_list[listIndex].length += pageSize;
					memLocation += pageSize;
				}
				else {
					if (lastAccess == 0) {
						chunkCount++;
					}
					listIndex++;
					lastAccess = 1;
					chunk_list[listIndex].start = memLocation;
					chunk_list[listIndex].length = 0;
					chunk_list[listIndex].length += pageSize;
					chunk_list[listIndex].RW = 1;
					memLocation += pageSize;
				}
			}
		}
	}
	return chunkCount -1;
}


/*
 * check_access takes the memory location from get_mem_layout and tests
 * its accessibility. If it's not read or write, it returns a -1, if it's
 * read only, it returns a 0 and if its read and write it returns a 1.
 * This function takes advantage of signals, using segmentation faults
 * to determine access levels.
 */

int check_access (void *memLocation) {
        signal(SIGSEGV, signal_handler);
        int returnValue = -1;
	char var;
        int sig = sigsetjmp(env, 1);        
        if (sig == 0) {
                var = *(char*)memLocation;
		returnValue = 0;
		*(char*)memLocation = *(char*)memLocation;
		returnValue = 1;
        }
	return returnValue;
}

void signal_handler(int signo) {
        siglongjmp(env, 1);
}
