/* main.c */

#include "./src/map.h"
#include "./src/Array/array.h"
#include "./src/Wahana/arrayWahana.h"
#include "./src/Wahana/arrayWMap.h"
#include "./src/Wahana/stackWMap.h"
#include "./src/MesinKata/mesinkata.h"
#include "./src/Antrian/antrian.h"
#include "./src/Antrian/listlinier.h"
#include "./src/Execute/cmdstack.h"
#include "./src/Execute/preparation.h"
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
    TulisDurasi(DetikToJAM(s_waktu));
    printf("\n");
    printf("Total uang yang dibutuhkan: ");
    printf("%d\n", s_uang);
}

int strcmp(const char* str1, const char* str2); /* Buat ngecek strings */
char* strcpy(char* destination, const char* source); /* Buat masukin ke strings (array of char) */
char* strcat(char *s1, const char *s2);

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
        while (!EndKata)
        {
            char temp[20]; 
            strcpy(temp, CKata.TabKata);
            ADVKATA();
            if (strcmp(CKata.TabKata,temp) != 0)
            {
                strcat(nama, " ");
                strcat(nama, CKata.TabKata);
            }
        }
        
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
        CmdStack s_commands;
        CreateSEmpty(&s_commands);

        /* Inisialisasi Konfigurasi Game */
        Map M1; //Map M1
        CreateMap(10, 10, &M1, 1);
        Map M2; //Map M2
        CreateMap(10, 10, &M2, 2);
        Map M3; //Map M3
        CreateMap(10, 10, &M3, 3);
        Map M4; //Map M4
        CreateMap(10, 10, &M4, 4);
        InitMap(&M1, "./src/map1.txt");
        /*InitMap(&M2, "./src/map2.txt");
        InitMap(&M3, "./src/map3.txt");
        InitMap(&M4, "./src/map4.txt");*/

        ListMap M; //List Map
        MakeListMap(&M, M1, M2, M3, M4);
        
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
        ListW LW;
        CreateListW(&LW);
        InitListW(&LW, "./src/Wahana/wahana.txt");

        // List Wahana Pemain
        ListLin WahanaP;
        CreateLEmpty(&WahanaP);

        // List Wahana pada Map
        ListWMap LWMap;
        CreateLWMEmpty(&LWMap);

        // Stack Wahana pada phase preparation
        StackWMap WBuild;
        CreateWMEmpty(&WBuild);

        // Queue Antrian Pengunjung
        Antrian AntrianP;
        CreateAEmpty(&AntrianP);

        int day = 1;
        int P_NMap = 1; // Pemain berada di peta keberapa
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
            
            if (main) {
                PrintMap(MapN(M, P_NMap));
            } else {
                PrintPreviewMap(MapN(M, P_NMap), LWMap, WBuild, P_NMap);
                if (!IsWMEmpty(WBuild)) {
                    printf("%d %d \n", Ordinat(Loc(TopItem(WBuild))), Absis(Loc(TopItem(WBuild))));
                }
            }
            info(nama, uang, time_curr, time_goal, time_remain, s_aksi, s_waktu, s_uang);
            printf("\n");
            printf("Masukkan Perintah:\n");
            SCANKATA();

            /* Pengecekan Command Valid */
            idx = SearchList1(LC, CKata.TabKata);
            if (idx == IdxUndef) // Jika tidak terdapat pada list command
            {
                printf("Command yang anda masukkan tidak valid\n");
            }
            else
            {
                /* Bergerak (w,a,s,d) di Command Game */
                if (idx == 0)
                {
                    Move(&(MapN(M, P_NMap)), 'w');
                    time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
                }

                if (idx == 1)
                {
                    Move(&(MapN(M, P_NMap)), 'a');
                    time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
                }

                if (idx == 2)
                {
                    Move(&(MapN(M, P_NMap)), 's');
                    time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
                }

                if (idx == 3)
                {
                    Move(&(MapN(M, P_NMap)), 'd');
                    time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
                }

                /* 'Build' di Command Game */
                if (idx == 4)
                {
                    PrintListW(LW);
                    char wahana[NMax];

                    SCANKATA();
                    strcpy(wahana, CKata.TabKata);
                    SCANKATA();
                    strcat(wahana, " ");
                    strcat(wahana, CKata.TabKata);
                    Build(LW, LC, P_NMap, wahana, &M, &LM, &LWMap, &WBuild, &s_waktu, &s_aksi, &s_commands);
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
                    Buy(LM,LC,barang,jumlah,uang,&s_uang,time_remain,&s_waktu,&s_aksi,&s_commands);
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
                    InsVFirstL(&WahanaP, 105);
                    GeneratePengunjung(&AntrianP, WahanaP, jmlPengunjung, 7);
                    /*ExecuteCommand(&s_commands, &uang, &s_aksi, &s_waktu, &s_uang, &time_curr, &time_goal, &time_remain, &M, &LM);*/
                }
                
                /* 'Main' di Command Game */
                if (idx == 9)
                {
                    if (main)
                    {
                        printf("Anda sedang berada di main phase!\n");
                    }
                    else
                    {
                        //int jmlPengunjung = 5;
                        //GeneratePengunjung(&AntrianP, WahanaP, jmlPengunjung, 7);
                        time_curr = time_open;
                        Second(time_curr)++;
                    }
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
                    if (!main)
                    {
                        printf("Anda sedang berada di preparation phase!\n");
                    }
                    else
                    {
                        time_curr = time_close;
                    }
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