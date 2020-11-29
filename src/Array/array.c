/* array.c */
/* Realisasi array.h */

#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include "../MesinKata/mesinkar.h"
#include "../MesinKata/mesinkata.h"
#include "../Execute/cmdstack.h"

int strcmp(const char* str1, const char* str2);
char* strcpy(char* destination, const char* source);
char* strcat(char *s1, const char *s2);

void CreateList(List *L)
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan kapasitas IdxMax-IdxMin+1 */
{
        for (int i=IdxMin;i<=IdxMax;i++)
	{
		strcpy(Key(*L,i), "undef"); // Assign variabel "kosong"
                Value(*L,i) = ValUndef; // Assign variabel "kosong"
	}
}

void InitList1(List *L)
/* I.S. List L kosong */
/* F.S. List L diisi data dari input */
{
        char Key[50];
        int Value;
        for (int i = IdxMin; i < 5; i++)
        {        
                scanf("%s", &Key);
                scanf("%d", &Value);
                
                strcpy(Key(*L,i), Key);
                Value(*L,i) = Value;
        }
}

void InitList2(List *L, char *filename)
/* I.S. List L kosong */
/* F.S. List L diisi data dari file eksternal (.txt) */
{
        if (EndKata)
        {
                EndKata = false;
        }
        
        STARTKATA2(filename);
        int i = 0;
        while (!EndKata && i<=IdxMax)
        {
            strcpy(Key(*L,i), CKata.TabKata);
            ADVKATA();
            Value(*L,i) = toInt(CKata.TabKata);
            ADVKATA();
            i++;
        }
}

void PrintListM(List L)
/* I.S. List L tidak kosong */
/* F.S. Menampilkan List yang ada, untuk menampilkan list pada buy */
{
        printf("Ingin membeli apa?\n");
        printf("List:\n");
	
        int i = IdxMin;
	while( strcmp(Key(L,i),"undef") != 0 && i <= IdxMax) // Selama value tidak "kosong"
	{
		printf("     - ");
                printf("%s\n", Key(L,i)); // Menampilkan nama barang
                i++;
	}
}

boolean SearchListB(List L, char *Key)
/* I.S. List L dan Nama terdefinisi */
/* F.S. Mengembalikan True jika Key terdapat pada List L */
{
        boolean found = false;
        int i = IdxMin;
	while( (strcmp(Key(L,i),"undef") != 0) && !found) // Looping selama Key tidak "kosong"
	{
		if (strcmp(Key(L,i),Key) == 0) // Jika ditemukan Key pada List
                {
                        found = true;
                }
                else
                {
                        i++;
                }
	}
        return found;
}

int SearchList1(List L, char *Key)
/* I.S. List L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks Key pada List L, jika tidak ada mengembalika IdxUndef */
{
        boolean found = false;
        int i = IdxMin;
	while( (strcmp(Key(L,i),"undef") != 0) && !found) // Looping selama Key tidak "kosong"
	{
		if (strcmp(Key(L,i),Key) == 0) // Jika ditemukan Key pada List
                {
                        found = true;
                }
                else
                {
                        i++;
                }
	}
        if (found)
        {
                return i;
        }
        else
        {
                return IdxUndef;
        }
}