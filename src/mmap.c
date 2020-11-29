#include "../adt/boolean.h"
#include "map.h"
#include "./mesinkata/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	/* Inisialisasi Konfigurasi Game */
    Map M1; //Map M1
    CreateMap(10, 10, &M1, 1);
    Map M2; //Map M2
    CreateMap(10, 10, &M2, 2);
    Map M3; //Map M3
    CreateMap(10, 10, &M3, 3);
    Map M4; //Map M4
    CreateMap(10, 10, &M4, 4);
	
    InitMap(&M1, "map1.txt");
    InitMap(&M2, "map2.txt");
    InitMap(&M3, "map3.txt");
    InitMap(&M4, "map4.txt");
	InitPlayer(&M1, 5, 5);
	
	List LC;
    CreateList(&LC);
    InitList2(&LC,"./Array/commands.txt");
    int idx;
	
	ListMap M; //List Map
    MakeListMap(&M, M1, M2, M3, M4);
	int P_NMap = 1;
	boolean running = true;
	while (running) {
		boolean pindah = false;
		PrintMap(MapN(M, P_NMap));
		printf("\n");
		printf("Masukkan Perintah:\n");
		SCANKATA();
		printf("%c\n",CKata.TabKata[0]);
		if (CKata.TabKata[0] == 'w')
		{
			Move(&(MapN(M, P_NMap)), 'w', &pindah);
			if (P_NMap==4 && pindah) {
				P_NMap = 1;
                InitPlayer(&MapN(M, P_NMap),5,10);
			}
			else if (P_NMap==3 && pindah) {
				P_NMap = 2;
                InitPlayer(&MapN(M, P_NMap),5,10);
			}
		}
		else if (CKata.TabKata[0] == 'a')
		{
			Move(&(MapN(M, P_NMap)), 'a', &pindah);
			if (P_NMap==2 && pindah) {
				P_NMap = 1;
                InitPlayer(&MapN(M, P_NMap),10,5);
			}
			else if (P_NMap==3 && pindah) {
				P_NMap = 4;
                InitPlayer(&MapN(M, P_NMap),10,5);
			}
		}
		else if (CKata.TabKata[0] == 's')
		{
			Move(&(MapN(M, P_NMap)), 's', &pindah);
			if (P_NMap==1 && pindah) {
				P_NMap = 4;
                InitPlayer(&MapN(M, P_NMap),5,1);
			}
			else if (P_NMap==2 && pindah) {
				P_NMap = 3;
                InitPlayer(&MapN(M, P_NMap),5,1);
			}
		}
		else if (CKata.TabKata[0] == 'd')
		{
			Move(&(MapN(M, P_NMap)), 'd', &pindah);
			if (P_NMap==1 && pindah) {
				P_NMap = 2;
                InitPlayer(&MapN(M, P_NMap),1,5);
			}
			else if (P_NMap==4 && pindah) {
				P_NMap = 3;
                InitPlayer(&MapN(M, P_NMap),1,5);
			}
		}
		else running = false;
	}
	return 0;
}