/* 	office.c 			*/
/* 	Realisasi office.h 	*/

#include "../Wahana/arrayWahana.h"
#include "../Antrian/listlinier.h"
#include "../MesinKata/mesinkar.h"
#include "../MesinKata/mesinkata.h"
#include "boolean.h"
#include "office.h"
#include <stdio.h>
#include <stdlib.h>

int strcmp(const char* str1, const char* str2); /* Buat ngecek strings */
char* strcpy(char* destination, const char* source); /* Buat masukin ke strings (array of char) */
char* strcat(char *s1, const char *s2);

void InitOffice(ListW LW, ListLin WahanaP)
/* Menu Office */
{
	/* Kata Details */
	Kata Details;
	Details.TabKata[0] = 'D';
	Details.TabKata[1] = 'e';
	Details.TabKata[2] = 't';
	Details.TabKata[3] = 'a';
	Details.TabKata[4] = 'i';
	Details.TabKata[5] = 'l';
	Details.TabKata[6] = 's';
	Details.Length = 7;
	
	/* Kata Report */
	Kata Report;
	Report.TabKata[0] = 'R';
	Report.TabKata[1] = 'e';
	Report.TabKata[2] = 'p';
	Report.TabKata[3] = 'o';
	Report.TabKata[4] = 'r';
	Report.TabKata[5] = 't';
	Report.Length = 6;
	
	/* Kata Exit */
	Kata Exit;
	Exit.TabKata[0] = 'E';
	Exit.TabKata[1] = 'x';
	Exit.TabKata[2] = 'i';
	Exit.TabKata[3] = 't';
	Exit.Length = 4;
	
	printf("Anda memasuki Interface Office\n");
	boolean running = true;
	char input[20]; 
	while(running) {
		printf("Masukkan perintah (Details / Report / Exit)\n");
		SCANKATA();
		//strcpy(input, CKata.TabKata);
		printf("%s\n",CKata.TabKata);
		if (strcmp(Details.TabKata, CKata.TabKata) == 0) {
			InitDetails(LW, WahanaP);
		}
		else if (strcmp(Report.TabKata, CKata.TabKata) == 0) {
			InitReport(LW, WahanaP);
		}
		else if (strcmp(Exit.TabKata, CKata.TabKata) == 0) {
			running = false;
		}
	}
}

void InitDetails(ListW LW, ListLin WahanaP)
/* Menu Details */
{
	WahanaListing(LW, WahanaP);
	int ID;
	printf("Masukkan ID Wahana yang ingin dilihat Detailnya\n");
	scanf("%d",&ID);
	DetailWahana(LW,ID);
}

void InitReport(ListW LW, ListLin WahanaP)
/* Menu Report */
{
	printf("Menu Report\n");
	WahanaListing(LW, WahanaP);
	int ID;
	printf("Masukkan ID Wahana yang ingin dilihat Reportnya\n");
	scanf("%d",&ID);
}

void WahanaListing(ListW LW, ListLin WahanaP)
/* Listing Wahana untuk Interface Details dan Report */
{
	addrList L = FirstL(WahanaP);
	int idx, i;
	boolean found;
    while (L!=NilN)
    {
		i = 0;
		found = false;
		idx = InfoL(L);
		while (!found) {
			if (ID(LW,i)==idx) {	
				printf("%d - ",idx);
				printf("%s\n", WName(LW,i));
				found = true;
			}
			i++;
		}
		L = NextL(L);
	}
}

void DetailWahana(ListW LW, int idx)
/* Menampilkan Detail ID Wahana yang Dipilih */
{
	WahanaItem curr = WahanaFromID(LW, idx);
	printf("Nama : "); printf("%s\n",curr.wname);
	printf("ID : "); printf("%d\n",curr.id);
	printf("Harga : "); printf("%d\n",curr.harga);
	printf("Kapasitas : "); printf("%d\n",curr.kapasitas);
	printf("Durasi : "); printf("%d\n",curr.duration);
	printf("Deskripsi : "); printf("%s\n",curr.wdesc);
	printf("Level Upgrade : "); printf("%d\n",curr.level);
}

void ReportWahana(ListW LW, int idx)
/* Menampilkan Report ID Wahana yang Dipilih */
{
	WahanaItem curr = WahanaFromID(LW, idx);
	
}