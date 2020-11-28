/* array.c */
/* Realisasi array.h */

#include "arrayWahana.h"
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "../Antrian/listlinier.h"
#include "../MesinKata/mesinkar.h"
#include "../MesinKata/mesinkata.h"

int strcmp(const char* str1, const char* str2);
char* strcpy(char* destination, const char* source);
char* strcat(char *s1, const char *s2);

void CreateListW(ListW *L)
/* I.S. L sembarang */
/* F.S. Terbentuk ListW L kosong dengan kapasitas IdxMax-IdxMin+1 */
{
    for (int i=IdxMin;i<=IdxMax;i++)
	{
		strcpy(WName(*L,i), "undef"); // Assign variabel "kosong"
        ID(*L,i) = ValUndef; // Assign variabel "kosong"
        Duration(*L,i) = ValUndef; // Assign variabel "kosong"
        Level(*L,i) = ValUndef; // Assign variabel "kosong"
        int j;
        for (j = 0; j < 5; j++) {
            Bahan(*L, i, j) = ValUndef;
        }
	}
}

void InitListW(ListW *L, char *filename)
/* I.S. ListW L kosong */
/* F.S. ListW L diisi data dari file eksternal (.txt) */
{
    STARTKATA2(filename);
    int i = 0;
    int j;
    while (!EndKata && i<=IdxMax)
    {
        strcpy(WName(*L,i), CKata.TabKata);
        ADVKATA();
        strcat(WName(*L,i), " ");
        strcat(WName(*L,i), CKata.TabKata);
        ADVKATA();
        ID(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        Duration(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        Level(*L,i) = toInt(CKata.TabKata);
        for (j = 0; j < 5; j++) {
            ADVKATA();
            Bahan(*L, i, j) = toInt(CKata.TabKata);
        }
        ADVKATA();
        i++;
    }
    EndKata = false;
}

void PrintListW(ListW L)
/* I.S. ListW L tidak kosong */
/* F.S. Menampilkan ListW yang ada, untuk menampilkan ListW wahana */
{
    printf("Ingin membangun apa?\n");
    printf("List:\n");

    int i = IdxMin;
    while ( strcmp(WName(L,i),"undef") != 0 && i <= IdxMax)
    {
        printf("     - ");
        printf("%s\n", WName(L,i));
        i++;
    }
}

boolean SearchListWB(ListW L, int idx)
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan True jika WName terdapat pada ListW L */
{
    boolean found = false;
    int i = IdxMin;
	while(ID(L,i) != idx && !found) // Looping selama ID bukan idx
	{
		if (ID(L,i) == idx) // Jika ditemukan ID pada ListW
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

int SearchListW1(ListW L, int idx)
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks WName pada ListW L, jika tidak ada mengembalika IdxUndef */
{
    boolean found = false;
    int i = IdxMin;
	while(ID(L,i) == idx && !found) // Looping selama ID bukan idx
	{
		if (ID(L,i) == idx) // Jika ditemukan ID pada ListW
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

void Build(ListW W, ListLin WahanaP, int idx, List *LM)
/* I.S. Parameter Fungsi Terdefinisi */
/* F.S. Uang berkurang sebanyak (harga barang)*(quantity), jika uang tidak cukup maka akan ditampilkan pesan error
        & proses tidak dijalankan */
{
    int i = 0;
}