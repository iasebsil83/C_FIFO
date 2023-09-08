#ifndef QUEUES_H
#define QUEUES_H






// ---------------- IMPORTATIONS ----------------

//boleans
#include <stdbool.h>






// ---------------- DEFINITIONS ----------------

//structures
typedef struct FIFO {
	char   block_size;
	size_t capacity;            //number of blocks allocated inside FIFO  (constant)
	size_t length;              //number of blocks currently used in FIFO (variable)
	size_t pushIndex, popIndex;
	bool   is_full;
	char*  data;
} fifo;






// ---------------- INSTANTIATION ----------------

//create - clear
fifo* fifo_create(char block_size, size_t capacity);
void  fifo_clear(fifo* f);
void  fifo_free(fifo* f);  //to avoid forgetting to free internal fifo data






// ---------------- USE ----------------

//push - pop
void      fifo_push(fifo* f, long long data); //"long long" will be casted into the desired type
long long fifo_pop(fifo* f);                  //same thing, cast result into the desired type






#endif
