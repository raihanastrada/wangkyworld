#include "mesinkata.h"
#include <stdio.h>

int main()
{
    char file[20];
    char *fileptr = file;
    printf("Masukkan input: ");
    SCANKATA();
    printf("%s\n",CKata.TabKata);
    printf("Masukkan input: ");
    SCANKATA();
    printf("%s\n",CKata.TabKata);
    printf("Masukkan filename: ");
    scanf("%s", fileptr);
    STARTKATA2(file);
    printf("Cek apakah terdapat kata\n");
    if (EndKata)
    {
        printf ("Kata kosong\n");
    }
    else
    {
        printf("Terdapat kata\n");
        printf("Membaca Kata Sampai MARK\n");
        while (!EndKata)
        {
            printf("Current Kata: \n");
            printf("%s\n",CKata.TabKata);
            ADVKATA();
        }
    }
    
    return 0;
}
