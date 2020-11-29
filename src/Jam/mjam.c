#include <stdio.h>
#include <stdlib.h>
#include "jam.h"

int main()
{
    JAM JAw, JAkh;
    long detik, detik2;

    printf("Mengecek Kevalidan Jam kemudian membuat ADT Jam\n");
    BacaJAM(&JAw);
    while (!IsJAMValid(Hour(JAw),Minute(JAw),Second(JAw)))
    {
        BacaJAM(&JAw);
    }

    printf("Menampilkan jam dengan format HH.MM \n");
    TulisJAM(JAw);
    printf("\n");

    printf("Mengkonversikan jam dalam detik\n");
    detik = JAMToDetik(JAw);
    printf("%d detik\n",detik);

    printf("Meminta input detik kemudian mengkonversikan ke type jam\n");
    scanf("%d", &detik);
    JAkh = DetikToJAM(detik);
    TulisJAM(JAkh);
    printf("\n");

    printf("Mengecek apakah input Jam 1 > input Jam 2 & input Jam 1 = input Jam 2\n");
    if (JEQ(JAw,JAkh))
    {
        printf("Input Jam 1 = Input Jam 2\n");
    }
    else
    {
        printf("Input Jam 1 != Input Jam 2\n");
    }
    
    if (JGT(JAw,JAkh))
    {
        printf("Input Jam 1 > Input Jam 2\n");
    }
    else
    {
        printf("Input Jam 1 < Input Jam 2\n");
    }
    
    printf("Menambah input jam 1 dengan input jam 2\n");
    JAw = AddJam(JAMToDetik(JAw),JAMToDetik(JAkh));
    TulisJAM(JAw);
    printf("\n");

    printf("Menuliskan durasi antara input jam 1 & input jam 2\n");
    TulisDurasi(Durasi(JAw,JAkh));
    printf("\n");

    return 0;
}