#include "../Wahana/arrayWahana.h"
#include "../Antrian/listlinier.h"
#include "../MesinKata/mesinkar.h"
#include "../MesinKata/mesinkata.h"
#include "boolean.h"
#include "office.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	// List Wahana
    ListW LW;
    CreateListW(&LW);
    InitListW(&LW, "../Wahana/wahana.txt");
	// List Wahana Pemain
    ListLin WahanaP;
    CreateLEmpty(&WahanaP);
	InsVFirstL(&WahanaP, 720);
	InsVFirstL(&WahanaP, 212);
	PrintInfo(WahanaP);
	
	InitOffice(LW, WahanaP);
	return 0;
}