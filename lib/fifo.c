// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//for memcpy()
#include <string.h>

//own header
#include "fifo.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIFO [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                 FIFOs by I.A.

        FIFO is an utility program that allows you to create and manipulate
    FIFO structures of any type (but same type inside FIFO).

        NO ALLOCATION IS MADE WHEN PUSHING ITEMS. You can push any sort of
    data inside : char, short, int, int*... (precising its block_size of course)
    but the result will be stored AS IS inside FIFO.

        If you stored an int, the raw data is stored and can be popped (casted
    in "long long" however). If you stored a pointer, the raw pointer will be
    stored but the targetted data will remain unchanged.

    08/07/2023 > [0.1.0] :
    - Created fifo.c/.h.

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
******************************************************************************************

    LICENSE :

    C_FIFO
    Copyright (C) 2023 Sebastien SILVANO

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- INSTANTIATION ----------------

//create - clear
fifo* fifo_create(char block_size, size_t capacity) {

	//error cases
	if(block_size == 0){
		puts("RUNTIME ERROR > fifo.c : fifo_create() : Could not create FIFO with 0 bytes of block size.");
		return NULL;
	}
	if(capacity == 0){
		puts("RUNTIME ERROR > fifo.c : fifo_create() : Could not create FIFO with 0 blocks.");
		return NULL;
	}

	//create fifo
	fifo* f = malloc(sizeof(fifo));
	if(f == NULL){
		puts("FATAL ERROR > fifo.c : fifo_create() : Computer refuses to give more memory.");
		exit(EXIT_FAILURE);
	}

	//set initial values
	f->block_size = block_size;
	f->capacity   = capacity;
	f->length     = 0;
	f->pushIndex  = 0;
	f->popIndex   = 0;
	f->is_full    = false;
	f->data       = malloc(capacity * block_size);
	if(f->data == NULL){
		puts("FATAL ERROR > fifo.c : fifo_create() : Computer refuses to give more memory.");
		exit(EXIT_FAILURE);
	}

	return f;
}

void fifo_clear(fifo* f){
	if(f == NULL){
		puts("RUNTIME ERROR > fifo.c : fifo_clear() : FIFO is NULL.");
		return;
	}

	//reset values
	f->length    = 0;
	f->pushIndex = 0;
	f->popIndex  = 0;
	f->is_full   = false;
}

void fifo_free(fifo* f) {
	if(f == NULL){
		puts("RUNTIME ERROR > fifo.c : fifo_free() : FIFO is NULL.");
		return;
	}
	free(f->data);
	free(f);
}








// ---------------- USE ----------------

//push - pop
void fifo_push(fifo* f, long long data){
	if(f == NULL){
		puts("RUNTIME ERROR > fifo.c : fifo_push() : FIFO is NULL.");
		return;
	}

	//full
	if(f->is_full){
		puts("RUNTIME ERROR > fifo.c : fifo_push() : FIFO is full.");
		return;
	}

	//set element at current pushIndex
	char* fifoData_ref = f->data + (f->block_size * (f->pushIndex));
	char* data_ref     = (char*)&data;
	memcpy(fifoData_ref, data_ref, f->block_size);

	//increase pushIndex (modulo capacity)
	f->pushIndex++;
	if(f->pushIndex >= f->capacity){
		f->pushIndex = 0;
	}

	//last element reached
	if(f->pushIndex == f->popIndex){
		f->is_full = true;
	}

	//increase length
	f->length++;
}

long long fifo_pop(fifo* f){
	if(f == NULL){
		puts("RUNTIME ERROR > fifo.c : fifo_pop() : FIFO is NULL.");
		return 0L;
	}

	//was full => no longer
	if(f->is_full){
		f->is_full = false;
	}

	//check emptiness
	else if(f->pushIndex == f->popIndex){
		puts("RUNTIME ERROR > fifo.c : fifo_pop() : FIFO is empty.");
		return 0L;
	}

	//pop element
	char*     fifoData_ref = f->data + (f->block_size * (f->popIndex));
	long long result       = 0L;
	memcpy((char*)&result, fifoData_ref, f->block_size);

	//increase popIndex (modulo capacity)
	f->popIndex++;
	if(f->popIndex >= f->capacity){
		f->popIndex = 0;
	}

	//decrease length
	f->length--;

	return result;
}
