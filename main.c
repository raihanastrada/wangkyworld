/* main.c */

#include "./src/map.h"
#include "./src/Array/array.h"
#include "./src/MesinKata/mesinkata.h"
#include "./src/Antrian/antrian.h"
#include "./src/Antrian/listlinier.h"
#include "./src/Jam/jam.h"
#include <stdio.h>


void info(char *nama, int uang, JAM time_curr, JAM time_goal, JAM time_remain, int s_aksi, int s_waktu, int s_uang)
{
    printf("Nama: ");
    printf("%s\n", nama);
    printf("Money: ");
    printf("%d\n", uang);
    printf("Current Time: ");
    TulisJAM(time_curr);
    printf("\n");
    printf("Opening Time: ");
    TulisJAM(time_goal);
    printf("\n");
    printf("Time remaining: ");
    TulisDurasi(time_remain);
    printf("\n");
    printf("Total aksi yang akan dilakukan: ");
    printf("%d\n", s_aksi);
    printf("Total waktu yang dibutuhkan: ");
    printf("%d\n", s_waktu);
    printf("Total uang yang dibutuhkan: ");
    printf("%d\n", s_uang);
}

int strcmp(const char* str1, const char* str2); /* Buat ngecek strings */
char* strcpy(char* destination, const char* source); /* Buat masukin ke strings (array of char) */

int main()
{
    boolean running = false;
    printf(" __________________________________________ \n");
    printf("| Welcome to Willy Wangky's Fun Factory !! |\n");
    printf("|__________________________________________|\n");
    printf("   __________     ___________     ______   \n");
    printf("  | new game |   | load game |   | exit |  \n");
    printf("  |__________|   |___________|   |______|  \n");
    SCANKATA();
    
    if (strcmp(CKata.TabKata,"new") == 0)
    { running = true; }
        
    if (running)
    {   
        /* Info */
        /* Nama */
        char nama[20]; 
        printf("Memulai permainan baru...\n");
        printf("Masukkan nama: \n");
        SCANKATA();
        strcpy(nama, CKata.TabKata);
        
        /* Inisiasi Uang */
        int uang = 1000;        
        
        /* Inisiasi Jam */
        JAM time_open = MakeJAM(9,0,0);
        JAM time_close = MakeJAM(21,0,0);
        JAM time_curr = time_close;
        JAM time_goal = time_open;
        JAM time_remain;
        
        /* Inisialisasi Stack */
        int s_aksi = 0;
        int s_waktu = 0; 
        int s_uang = 0;

        /* Inisialisasi Konfigurasi Game */
        Map M1; //Map M1,M2,M3,M4
        CreateMap(10, 10, &M1);
        InitMap(&M1, "./src/map1.txt");
        
        // List Material
        List LM; 
        CreateList(&LM);
        InitList2(&LM,"./src/Array/materials.txt");

        // List Command
        List LC;
        CreateList(&LC);
        InitList2(&LC,"./src/Array/commands.txt");
        int idx;

        // List Wahana
        List LW;
        CreateList(&LW);
        InitList3(&LW, "./src/Array/wahana.txt");

        // List Wahana Pemain
        ListLin WahanaP;
        CreateLEmpty(&WahanaP);

        // Queue Antrian Pengunjung
        Antrian AntrianP;
        CreateAEmpty(&AntrianP);

        int day = 1;
        boolean main;
        while (running)
        {
            printf("\n");
            main = JinRange(time_open, time_close, time_curr); // Menghasilkan true jika current time berada diantaro time opening dan closing
            if (!main) // Jika preparation phase
            {
                printf("Preparation ");
                time_goal = time_open;
            }
            else
            {
                printf("Main ");
                time_goal = time_close;
            }
            printf("phase day %d\n",day);
            time_remain = Durasi(time_curr,time_goal);
            
            PrintMap(M1);
            info(nama, uang, time_curr, time_goal, time_remain, s_aksi, s_waktu, s_uang);
            printf("\n");
            printf("Masukkan Perintah:\n");
            SCANKATA();

            /* Pengecekan Command Valid */
            idx = SearchList1(LC, CKata.TabKata);
            printf("YOU TYPED: %s\n", CKata.TabKata);
            if (idx == IdxUndef) // Jika tidak terdapat pada list command
            {
                printf("Command yang anda masukkan tidak valid\n");
            }
            else
            {
                /* Bergerak (w,a,s,d) di Command Game */
                /* code */

                /* 'Build' di Command Game */
                if (idx == 4)
                {
                    PrintListW(LW);
                }

                /* 'Upgrade' di Command Game */
                if (idx == 5)
                {
                    /* code */
                }

                /* 'Buy' di Command Game */
                if (idx == 6)
                {
                    // KAMUS
                    char barang[20];
                    int jumlah;

                    PrintListM(LM);

                    SCANKATA();
                    jumlah = toInt(CKata.TabKata);
                    ADVKATA();
                    strcpy(barang, CKata.TabKata);
                    Buy(LM,barang,jumlah,&uang);
                }

                /* 'Undo' di Command Game */
                if (idx == 7)
                {
                    /* code */
                }
                
                /* 'Execute' di Command Game */
                if (idx == 8)
                {
                    int jmlPengunjung = 5;
                    GeneratePengunjung(&AntrianP, WahanaP, jmlPengunjung, 7);
                }
                
                /* 'Main' di Command Game */
                if (idx == 9)
                {
                    /* code */
                }
                
                /* 'Serve' di Command Game */
                if (idx == 10)
                {
                    /* code */
                }
                

                /* 'Repair' di Command Game */
                if (idx == 11)
                {
                    /* code */
                }
                

                /* 'Detail' di Command Game */
                if (idx == 12)
                {
                    /* code */
                }
                
                /* 'Office' di Command Game */
                if (idx == 13)
                {
                    /* code */
                }

                /* 'Prepare' di Command Game */
                if (idx == 14)
                {
                    /* code */
                }

                /* Exit di Command Game */
                if (idx == 15)
                {
                    running = false;
                    printf(" ________________________ \n");
                    printf("| Thanks for playing !!! |\n");
                    printf("|________________________|\n");
                    return 0;
                }
            }
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