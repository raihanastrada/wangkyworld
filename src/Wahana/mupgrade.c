#include "upgradeWahana.h"
#include "arrayWahana.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ListW L;
    UpgradeTree P;

    CreateListW(&L);
    InitListW(&L,"wahana.txt");
    BuildUpgradeTree(L, &P);
    PrintTree(P,1);

    return 0;
}
