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
	void *memLocation;
	memLocation = (void*) 0x00000000
	
}

int check_access (void *memLocation) {
        signal(SIGSEGV, signal_handler);
        int returnValue = -1;
	char var;
        int sig = sigsetjmp(env, 1);        
        if (sig == 0) {
                char var = (char*)memLocation;
		returnValue = 0;
		(char*)memLocation = (char*)memLocation;
		returnValue = 1;
        }
	return returnValue;
}

void signal_handler(int signo) {
        siglongjmp(env, 1);
}

