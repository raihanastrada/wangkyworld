/* main.c */

#include "./src/map.h"
#include "./src/Array/array.h"
#include "./src/MesinKata/mesinkata.h"
#include <stdio.h>

void info(char *nama, int uang, int time_curr, int time_open, int time_remain, int s_aksi, int s_waktu, int s_uang)
{
    printf("Nama: ");
    printf("%s\n", nama);
    printf("Money: ");
    printf("%d\n", uang);
    printf("Current Time: ");
    printf("%d\n", time_curr);
    printf("Opening Time: ");
    printf("%d\n", time_open);
    printf("Time remaining: ");
    printf("%d\n", time_remain);
    printf("Total aksi yang akan dilakukan: ");
    printf("%d\n", s_aksi);
    printf("Total waktu yang dibutuhkan: ");
    printf("%d\n", s_waktu);
    printf("Total uang yang dibutuhkan: ");
    printf("%d\n", s_uang);
}

int strcmp(const char* str1, const char* str2); /* Buat ngecek strings */

int main()
{
    boolean running = false;
    printf(" __________________________________________ \n");
    printf("| Welcome to Willy Wangky's Fun Factory !! |\n");
    printf("|__________________________________________|\n");
    printf("   __________     ___________     ______   \n");
    printf("  | new game |   | load game |   | exit |  \n");
    printf("  |__________|   |___________|   |______|  \n");
    STARTKATA();
    
    if (strcmp(CKata.TabKata,"new") == 0)
    { running = true; }
        
    if (running)
    {   
        /* Info */
        char *nama; 
        printf("Memulai permainan baru...\n");
        printf("Masukkan nama: \n");
        STARTKATA(); // Belom bisa ngambil input lagi setelah STARTKATA() awal
        
        nama = CKata.TabKata;
        int uang = 1000;
        int time_curr = 2100;
        int time_open = 1900;
        int time_remain = 12;
        int s_aksi = 0;
        int s_waktu = 0; 
        int s_uang = 0;

        /* Inisialisasi Game */
        Map M1; //Map M1,M2,M3,M4
        CreateMap(10, 10, &M1);
        InitMap(&M1, "map1.txt");
        List LM; // List Msterial
        InitList2(&LM);

        while (running)
        {
            PrintMap(M1);
            info(nama, uang, time_curr, time_open, time_remain, s_aksi, s_waktu, s_uang);
            STARTKATA(); // Belom bisa ngambil input lagi setelah STARTKATA() awal

            /* Bergerak (w,a,s,d) di Command Game */
            /* code */

            /* 'Build' di Command Game */
            /* code */

            /* 'Upgrade' di Command Game */
            /* code */

            /* 'Buy' di Command Game */
            if (strcmp(CKata.TabKata,"exit") == 0)
            {
                PrintListM(LM);
                /* Scan Nama Barang Harga */
                /* Masukkin perintah Buy(LM, barang, jumlah, &uang) ke Stack */
            }

            /* 'Undo' di Command Game */
            /* code */

            /* 'Execute' di Command Game */
            /* code */

            /* 'Main' di Command Game */
            /* code */

            /* 'Serve' di Command Game */
            /* code */

            /* 'Repair' di Command Game */
            /* code */

            /* 'Detail' di Command Game */
            /* code */

            /* 'Office' di Command Game */
            /* code */

            /* 'Prepare' di Command Game */
            /* code */

            /* Exit di Command Game */
            if (strcmp(CKata.TabKata,"exit") == 0)
            {
                running = false;
                printf(" ________________________ \n");
                printf("| Thanks for playing !!! |\n");
                printf("|________________________|\n");
                return 0;
            }
            running = false; // Temporary buat ngestop
        }
    }
        
        
    
    /* EXIT */
    if (strcmp(CKata.TabKata,"exit") == 0)
    {
        printf(" ________________________ \n");
        printf("| Thanks for playing !!! |\n");
        printf("|________________________|\n");
        return 0;
    }
}