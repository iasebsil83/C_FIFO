// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//to add text elements
#include <string.h>

//fifo utility
#include "../lib/fifo.h"






/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        fifo.h demonstration program

        Blablabla about the subject.

    DD/MM/YYYY > [V.V.V] :
    - Added something.
    - Added something else.

    DD/MM/YYYY > [V.V.V] :
    - Added something that wasn't before.
    - Fixed a bug.
    - Added something else.
    - Added something else again.

    BUGS : Active bugs in last version.
    NOTES : Notes.

    Contact     : ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */






// ---------------- EXECUTION ----------------

//main
int main(){

	//presentation
	puts("I.A. > This is an example of using FIFOs in C with \"fifo.c/.h\".\n");



	//CREATE

	//create a FIFO
	printf("I.A. > Creating a fifo...\n");
	fifo* myFIFO = fifo_create(sizeof(char*), 3);
	printf("I.A. > FIFO of %lu elements maximum created (length %lu).\n\n", myFIFO->capacity, myFIFO->length);



	//PUSH ELEMENTS

	//pushing strings into FIFO ("delta" should not work because capacity of FIFO is only 3 elements)
	char *greek_letter[] = { "alpha", "beta", "gamma", "delta" };
	for(size_t g=0; g < 4; g++){

		//try pushing letters
		printf("I.A. > Pushing string \"%s\" to FIFO.\n", greek_letter[g]);
		fifo_push(myFIFO, (long long)greek_letter[g]);

		//print length
		printf("I.A. > FIFO has length : %lu\n\n", myFIFO->length);
	}



	//POP ELEMENTS

	//popping first string
	char* res = (char*)fifo_pop(myFIFO);
	printf("I.A. > Popping first string : \"%s\".\n", res);

	//poping second string
	res = (char*)fifo_pop(myFIFO);
	printf("I.A. > Popping second string : \"%s\".\n", res);

	//print length
	printf("I.A. > FIFO has length : %lu\n", myFIFO->length);

	//pushing a fourth string now ("delta")
	printf("I.A. > Now trying again to push the fourth one \"%s\".\n", greek_letter[3]);
	fifo_push(myFIFO, (long long)greek_letter[3]);

	//print length
	printf("I.A. > FIFO has length : %lu\n", myFIFO->length);

	//poping third string
	res = (char*)fifo_pop(myFIFO);
	printf("I.A. > Popping third string : \"%s\".\n", res);

	//print length
	printf("I.A. > FIFO has length : %lu\n", myFIFO->length);



	//DELETE

	//clearing FIFO (can still be used)
	printf("I.A. > Clearing fifo...\n");
	fifo_clear(myFIFO);
	printf("I.A. > FIFO cleared (length %lu).\n", myFIFO->length);

	//free FIFO (no longer useable)
	fifo_free(myFIFO);



	return EXIT_SUCCESS;
}
