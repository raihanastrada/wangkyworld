/* array.c */
/* Realisasi array.h */

#include "arrayWahana.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Array/array.h"
#include "../Array/boolean.h"
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
        Harga(*L,i) = ValUndef; // Assign variabel "kosong"
        Kapasitas(*L,i) = ValUndef; // Assign variabel "kosong"
        Duration(*L,i) = ValUndef; // Assign variabel "kosong"
        strcpy(WDesc(*L,i), "undef"); // Assign variabel "kosong"
        Level(*L,i) = ValUndef; // Assign variabel "kosong"
        Biaya(*L,i) = ValUndef; // Assign variabel "kosong"
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
    if (EndKata) {
        EndKata = false;
    }
    
    STARTKATA2(filename);
    int i = 0;
    int j;
    while (!EndKata && i<=IdxMax)
    {
        /* Nama */
        strcpy(WName(*L,i), CKata.TabKata);
        ADVKATA();
        strcat(WName(*L,i), " ");
        strcat(WName(*L,i), CKata.TabKata);
        ADVKATA();
        /* ID */
        ID(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        /* Harga */
        Harga(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        /* Kapasitas */
        Kapasitas(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        /* Durasi */
        Duration(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        /* Deskripsi */
        strcpy(WDesc(*L,i), CKata.TabKata);
        ADVKATA();
        strcat(WDesc(*L,i), " ");
        strcat(WDesc(*L,i), CKata.TabKata);
        ADVKATA();
        strcat(WDesc(*L,i), " ");
        strcat(WDesc(*L,i), CKata.TabKata);
        ADVKATA();
        /* Level */
        Level(*L,i) = toInt(CKata.TabKata);
        ADVKATA();
        /* Biaya */
        Biaya(*L,i) = toInt(CKata.TabKata);
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
    int i = IdxMin;
	while(ID(L,i) != idx) // Looping selama ID bukan idx
	{
		i++;
	}
    return (ID(L,i) == idx);
}

int SearchListWName(ListW L, int idx)
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks WName pada ListW L, jika tidak ada mengembalika IdxUndef */
{
    int i = IdxMin;
	while(ID(L,i) != idx) // Looping selama ID bukan idx
	{
		i++;
	}
    if (ID(L, i) == idx)
    {
        return i;
    }
    else
    {
        return IdxUndef;
    }
}

int SearchListWLvl(ListW L, int idx)
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks WName pada ListW L, jika tidak ada mengembalikan ValUndef */
{
    int i = IdxMin;
	while(ID(L,i) != idx) // Looping selama ID bukan idx
	{
		i++;
	}
    if (ID(L, i) == idx)
    {
        return Level(L, i);
    }
    else
    {
        return ValUndef;
    }
}

int IDFromWahana(ListW L, char *wname)
/* I.S. ListW L dan wname terdefinisi, terdapat wahana dengan nama wname di L */
/* F.S. Mengembalikan ID wahana pada ListW L dengan WName wname */
{
    int i = IdxMin;
	while(strcmp(WName(L,i), wname) != 0) // Looping selama ID bukan idx
	{
        i++;
	}
    return ID(L, i);
}
