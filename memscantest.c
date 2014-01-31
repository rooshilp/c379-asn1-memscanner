/* Rooshil Patel
 * 1255318
 * Assignment 1
 * CMPUT 379
 */

#include <stdio.h>

#include "memchunk.h"


int size;
int chunkCount;

int main()
{
	struct memchunk chunk_list[20];
	size = 20;
	chunkCount = get_mem_layout(&chunk_list, size);
	printf("%d\n", chunkCount);
	int i;
	for (i = 0;i < chunkCount; i++) {
		printf("%p - %d - %d\n", chunk_list[i].start, chunk_list[i].length, chunk_list[i].RW);
	}
}
