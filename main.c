/* main.c */

#include "./src/map.h"
#include <stdio.h>

int main()
{
    Map M1; //Map M1,M2,M3,M4
    CreateMap(10, 10, &M1);
    InitMap(&M1, "map1.txt");
    boolean exit = false;
    char input[10]; // Sementara, seharusnya input pake mesinkata
    
    while (!exit)
    {
        PrintMap(M1);
        scanf("%s",&input);
        if (input == "exit.") //exit
        {
            exit = true;
        }    
    }
    return 0;
}
