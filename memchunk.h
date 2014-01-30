/* Rooshil Patel
 * 1255318
 * Assignment 1
 * CMPUT 379
 */

#include <signal.h>
#include <setjmp.h>

struct memchunk {
        void *start;
        unsigned long length;
        int RW;
};

static void my_handler(int);

int get_mem_layout(struct memchunk *chunk_list, int size);

int check_access(void *memlocation);

void signal_handler(int signo);


