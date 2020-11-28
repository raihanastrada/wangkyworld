#include "mesinkata.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>

char CC;
boolean EOP;
boolean EndKata;
Kata CKata;

void IgnoreBlank()
{
	while (CC==BLANK && CC != MARK) {
		ADV();
	}
}

void IgnoreNl()
{
    while (CC==NEWLINE && CC != MARK)
    {
        ADV();
    }    
}

void STARTKATA()
{
	START();
	IgnoreBlank();
	ADVKATA();	
}

void STARTKATA2(char *filename)
{
	START2(filename);
	IgnoreBlank();
	ADVKATA();
}

void SCANKATA()
{
	SCAN();
	IgnoreBlank();
	ADVKATA();
}

void ADVKATA()
{
	if (CC==MARK){
		EndKata = true;
	}
	else {
		SalinKata();
		IgnoreBlank();
		IgnoreNl();
	}
}	   

void SalinKata()
{
	memset(CKata.TabKata,0,CKata.Length);
	CKata.Length = 0;
	while ((CC != MARK) && (CC != BLANK) && (CC != NEWLINE) && (CKata.Length < NMax)) {
		CKata.TabKata[CKata.Length] = CC;
		ADV();
		CKata.Length++;
	}
}

int toInt(char *num)
{
	int result;
	sscanf(num, "%d", &result);
	return result;	
}