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


void info(char *nama, int uang, JAM time_curr, JAM time_goal, int time_remain, int s_aksi, int s_waktu, int s_uang, boolean main)
{
    printf("Nama: ");
    printf("%s\n", nama);
    printf("Money: ");
    printf("%d\n", uang);
    printf("Current Time: ");
    TulisJAM(time_curr);
    printf("\n");
    if (!main) {
        printf("Closing Time: ");
    } else {
        printf("Opening Time: ");
    }
    TulisJAM(time_goal);
    printf("\n");
    printf("Time remaining: ");
    TulisDurasi(DetikToJAM(time_remain));
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
        int time_remain;
        
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
        InitMap(&M2, "./src/map2.txt");
        InitMap(&M3, "./src/map3.txt");
        InitMap(&M4, "./src/map4.txt");
		InitPlayer(&M1,5,5);

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
            //main = JinRange(time_open, time_close, time_curr); // Menghasilkan true jika current time berada diantaro time opening dan closing
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
            time_remain = JAMToDetik(Durasi(time_curr,time_goal));
            
            PrintPreviewMap(MapN(M, P_NMap), LWMap, WBuild, P_NMap);
            info(nama, uang, time_curr, time_goal, time_remain, s_aksi, s_waktu, s_uang, main);
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
				boolean pindah = false;
                if (idx == 0)
                {
                    Move(&(MapN(M, P_NMap)), 'w', &pindah);
					time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
					if (P_NMap==4 && pindah) {
						Generate1(M4,&M1);
						P_NMap = 1;
					}
					else if (P_NMap==3 && pindah) {
						Generate2(M3,&M2);
						P_NMap = 2;
					}
                }

                if (idx == 1)
                {
                    Move(&(MapN(M, P_NMap)), 'a', &pindah);
					time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
					if (P_NMap==2 && pindah) {
						Generate1(M2,&M1);
						P_NMap = 1;
					}
					else if (P_NMap==3 && pindah) {
						Generate4(M3,&M4);
						P_NMap = 4;
					}
                }

                if (idx == 2)
                {
                    Move(&(MapN(M, P_NMap)), 's', &pindah);
					time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
					if (P_NMap==1 && pindah) {
						Generate4(M1,&M4);
						P_NMap = 4;
					}
					else if (P_NMap==2 && pindah) {
						Generate3(M2,&M3);
						P_NMap = 3;
					}
                }

                if (idx == 3)
                {
                    Move(&(MapN(M, P_NMap)), 'd', &pindah);
					time_curr = AddJam(JAMToDetik(time_curr), Value(LC,idx));
					if (P_NMap==1 && pindah) {
						Generate2(M1,&M2);
						P_NMap = 2;
					}
					else if (P_NMap==4 && pindah) {
						Generate3(M4,&M3);
						P_NMap = 3;
					}
                }

                /* 'Build' di Command Game */
                if (idx == 4)
                {
                    if (!main) {
                        PrintListW(LW);
                        char wahana[NMax];

                        SCANKATA();
                        strcpy(wahana, CKata.TabKata);
                        ADVKATA();
                        strcat(wahana, " ");
                        strcat(wahana, CKata.TabKata);
                        Build(LW, LC, P_NMap, wahana, &M, &LM, &LWMap, &WBuild, &s_waktu, &s_aksi, &s_commands);
                    } else {
                        printf("Anda sedang berada di preparation phase!\n");
                    }
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
                    if (!main) {
                        char barang[20];
                        int jumlah;

                        PrintListM(LM);

                        SCANKATA();
                        jumlah = toInt(CKata.TabKata);
                        ADVKATA();
                        strcpy(barang, CKata.TabKata);
                        Buy(LM,LC,barang,jumlah,uang,&s_uang,time_remain,&s_waktu,&s_aksi,&s_commands);
                    } else {
                        printf("Anda sedang berada di preparation phase!\n");
                    }
                }

                /* 'Undo' di Command Game */
                if (idx == 7)
                {
                    if (Idx(InfoTopS(s_commands)) == 4) {
                        UndoBuild(LW, LC, &LM, &WBuild, &s_waktu, &s_aksi, &s_commands);
                    }
                }
                
                /* 'Execute' di Command Game */
                if (idx == 8)
                {
                    if (!main) {
                        ExecuteCommand(&s_commands, &WahanaP, &uang, &s_aksi, &s_waktu, &s_uang, &time_curr, &LWMap, &WBuild, &M, &LM);
                        if (JEQ(time_curr, time_open)) {
                            int jmlPengunjung = 5;
                            main = true;
                            time_curr = time_open;
                            GeneratePengunjung(&AntrianP, WahanaP, jmlPengunjung, 7);
                        }
                    } else {
                        printf("Anda sedang berada di preparation phase!\n");
                    }
                }
                
                /* 'Main' di Command Game */
                if (idx == 9)
                {
                    if (!main) {
                        ExecuteCommand(&s_commands, &WahanaP, &uang, &s_aksi, &s_waktu, &s_uang, &time_curr, &LWMap, &WBuild, &M, &LM);
                        int jmlPengunjung = 5;
                        main = true;
                        time_curr = time_open;
                        GeneratePengunjung(&AntrianP, WahanaP, jmlPengunjung, 7);
                    } else {
                        printf("Anda sedang berada di main phase!\n");
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
                    if (main) {
                        s_waktu = 0;
                        s_aksi = 0;
                        s_uang = 0;
                        time_curr = time_close;
                        main = false;
                        day++;
                    } else {
                        printf("Anda sedang berada di preparation phase!\n");
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