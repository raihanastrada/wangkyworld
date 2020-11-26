#include "mesinkata.h"
#include "boolean.h"

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
	CKata.Length = 0;
	while ((CC != MARK) && (CC != BLANK) && (CC != NEWLINE) && (CKata.Length < NMax)) {
		CKata.TabKata[CKata.Length] = CC;
		ADV();
		CKata.Length++;
	}
}
