#include "mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * filename;
static char retval;

void START() 
{
    filename = stdin;
	ADV();
}

void START2(char *string)
{
	filename = fopen(string,"r");
	ADV();
}

void ADV() 
{
	retval = fscanf(filename,"%c",&CC);
	EOP = (CC == MARK);
	if (EOP) 
    {
       fclose(filename);
 	}
}
