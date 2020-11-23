/* main.c */

#include "./src/map.h"
#include <stdio.h>

int main()
{
    Map M1; //Map M1,M2,M3,M4
    CreateMap(10, 10, &M1);
    InitMap(&M1, "map1.txt");
    PrintMap(M1);
    
    return 0;
}
