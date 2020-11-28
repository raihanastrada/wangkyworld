#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main()
{
    List L;
    CreateList(&L);
    InitList2(&L); //Membaca file eksternal material.txt
    printf("Menampilkan list barang\n");
    PrintListM(L);

    printf("Mencari Key pada List\n");
    char Key[10];
    char *Keyptr = Key; 
    printf("Masukkan Key yang ingin dicari: ");
    scanf("%s", Keyptr);
    if (SearchListB(L, Key) == true)
    {
        printf("Ada\n");
    }
    else
    {
        printf("Gaada\n");
    }
    
    printf("Cek Prosedur Buy\n");
    int Uang,Jumlah;
    char Barang[10];
    char *Barangptr = Barang;
    printf("Masukkan jumlah uang: ");
    scanf("%d",&Uang);
    PrintListM(L);
    printf("Masukkan barang yang ingin dibeli dan jumlah: ");
    scanf("%s %d", Barang, &Jumlah);
    Buy(L,Barang,Jumlah,&Uang);
    printf("Uang akhir: ");
    printf("%d", Uang);

    return 0;
}