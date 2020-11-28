#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "antrian.h"
#include "listlinier.h"

int main() {
    ListLin Wahana;
    CreateLEmpty(&Wahana);
    InsVFirstL(&Wahana, 101);
    InsVFirstL(&Wahana, 112);
    InsVFirstL(&Wahana, 205);
    InsVFirstL(&Wahana, 234);
    /*InsVFirstL(&Wahana, 317);
    InsVFirstL(&Wahana, 389);
    InsVFirstL(&Wahana, 571);*/

    Antrian AntriPengunjung;
    GeneratePengunjung(&AntriPengunjung, Wahana, 5, 4);

    int i;
    addrA B = FirstA(AntriPengunjung);
    for (i = 0; i < 5; i++) {
        printf("%d: \n  ", Prio(B));
        PrintInfo(Wahana(B));
        printf("\n");
        B = NextA(B);
    }

    return 0;
}