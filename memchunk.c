/* Rooshil Patel
 * 1255318
 * Assignment 1
 * CMPUT 379
 */

#include <signal.h>
#include <setjmp.h>

#include <stdio.h>

#include "memchunk.h"

static sigjmp_buf env;

struct memchunk {
        void *start;
        unsigned long length;
        int RW;
};

int get_mem_layout (struct memchunk *chunk_list, int size) {
        int pageSize = getpagesize();
        int chunkCount = 0;
	int end = 0xffffffff
	int listIndex = 0
	void *memLocation;
	memLocation = (void*) 0x00000000
	
	while (memLocation < end) {
		int access;
		int lastAccess;
		int chunkSize;
		access = check_access(*memLocation)
		if (access == -1) {
			if (lastAccess == access) {
				continue;
			}
			else {
				chunkCount++
				
		if (access == 0) {
			if (lastAccess == access) {
				chunkSize++;
				chunk_list[listIndex].length += pageSize;
			}
			else {
				if (lastAccess == 1) {
					chunkCount++;
				}
				chunkSize = 1
				listIndex++;
				lastAccess = 0;
				chunk_list[listIndex].*start = *memLocation;
				chunk_list[listIndex].length = 0;
				chunk_list[listIndex].length += pageSize;
				chunk_list[listIndex].RW = 0;
			}
		}

		if (access == 1) {
			if (lastAccess == access) {
				chunkSize++;
				chunk_list[listIndex].length += pageSize;
			}
			else {
				if (lastAccess == 0) {
					chunkCount++;
				}
				chunkSize = 1
				listIndex++;
				lastAccess = 1;
				chunk_list[listIndex].*start = *memLocation;
				chunk_list[listIndex].length = 0;
				chunk_list[listIndex].length += pageSize;
				chunk_list[listIndex].RW = 1;
			}
		}
}



int check_access (void *memLocation) {
        signal(SIGSEGV, signal_handler);
        int returnValue = -1;
	char var;
        int sig = sigsetjmp(env, 1);        
        if (sig == 0) {
		printf("Reading address.");
                char var = (char*)memLocation;
		returnValue = 0;
		printf("Writing to address.");
		(char*)memLocation = (char*)memLocation;
		returnValue = 1;
        }
	return returnValue;
}

void signal_handler(int signo) {
        siglongjmp(env, 1);
}

