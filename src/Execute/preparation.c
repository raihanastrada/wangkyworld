#include "../map.h"
#include "../Array/array.h"
#include "../Wahana/arrayWahana.h"
#include "../Wahana/arrayWMap.h"
#include "../Wahana/stackWMap.h"
#include "../MesinKata/mesinkata.h"
#include "../Antrian/antrian.h"
#include "../Antrian/listlinier.h"
#include "cmdstack.h"
#include "preparation.h"
#include "../Jam/jam.h"
#include <stdio.h>

int strcmp(const char* str1, const char* str2); /* Buat ngecek strings */
char* strcpy(char* destination, const char* source); /* Buat masukin ke strings (array of char) */

void PrintPreviewMap(Map M, ListWMap WMap, StackWMap WBuild, int NMap)
/* Menampilkan peta pada kondisi preparation phase */
{
    for (int i = BrsMin; i < BrsMax; i++)
    {
        for (int j = KolMin; j < KolMax; j++)
        {
            if (i == PlayerY(M) && j == PlayerX(M))
            {
                printf("P");
            }
            else if (SearchSWMap(WBuild, i, j, NMap))
            {
                printf("W");
            }
            else if (SearchWMap(WMap, i, j, NMap))
            {
                printf("W");
            }
            else
            {
                printf("%c", Info(M, i, j));
            }
            if (j == KolMax-1)
            {
                printf("\n");
            }
        }
    }
    PrintLegend();
}

/* ************ Menjalankan Command pada CmdStack ************ */
void ExecuteCommand (CmdStack *S1, ListLin *WahanaP, int *uang, int *s_aksi, int *s_waktu, int *s_uang, JAM *time_curr, ListWMap *WMap, StackWMap *WBuild1, ListMap *ListM, List *ListMat)
/* menjalankan command-command yang ada di CmdStack S */
/* I.S. S mungkin kosong */
/* F.S. melakukan build/upgrade/buy sesuai command yang ada di stack, lalu mulai main phase */
{
    int idx;
    int amount;
    int wahana;
    char detail[20];
    POINT position;
    int n_map;
    int IDW;
    POINT Pos;
    int Quad;
    Command C;
    printf("Executing...\n");

    CmdStack S;
    CreateSEmpty(&S);
    StackWMap WBuild;
    CreateWMEmpty(&WBuild);
    
    while (!IsSEmpty(*S1)) {
        PopCommand(S1, &C);
        PushCommand(&S, C);
    }

    while (!IsWMEmpty(*WBuild1)) {
        PopWahana(WBuild1, &IDW, &Pos, &Quad);
        PushWahana(&WBuild, IDW, Pos, Quad);
    }

    while (*s_aksi > 0) {
        PopCommand(&S, &C);
        idx = Idx(C);
        amount = Jml(C);
        wahana = Whn(C);
        strcpy(detail, Det(C));
        position = Posn(C);
        n_map = NMap(C);

        if (idx == 4) {
            PopWahana(&WBuild, &IDW, &Pos, &Quad);
            PushLWM(WMap, wahana, position, n_map);
            if (SearchL(*WahanaP, wahana) == NilN) {
                InsVFirstL(WahanaP, wahana);
            }
        } else if (idx == 5) {
            // upgrade
        } else if (idx == 6) {
            boolean found = false;
            int i = IdxMin;
            while( (strcmp(Key(*ListMat,i),"undef") != 0) && !found) { // Looping selama Key tidak "kosong"
                if (strcmp(Key(*ListMat,i),detail) == 0) { // Jika ditemukan Key pada List
                    found = true;
                } else {
                    i++;
                }
            }
        }
        (*s_aksi)--;
    }

    *uang = *uang-*s_uang;
    *time_curr = AddJam(JAMToDetik(*time_curr),*s_waktu);

    *s_uang = 0;
    *s_waktu = 0;
}

void Buy(List L, List LC, char *Nama, int Quantity, int Uang, int *s_uang, int time_remain, int *s_waktu, int *s_aksi, CmdStack *S)
/* I.S. Parameter Fungsi Terdefinisi */
/* F.S. Uang berkurang sebanyak (harga barang)*(quantity), jika uang tidak cukup maka akan ditampilkan pesan error
        & proses tidak dijalankan */
{
        int total;
        int idx = SearchList1(L,Nama);
        int addtime;
        if (idx != IdxUndef)
        {
                total = Value(L,idx)*Quantity+*s_uang;
                addtime = Value(LC, SearchList1(LC, "buy"));
                if (*s_waktu+addtime < time_remain) {
                    if (Uang > total)
                    {
                            *s_uang = total;
                            *s_waktu = *s_waktu+addtime;
                            (*s_aksi)++;
                            Command C;
                            AssignC(&C, 6, Quantity, 0, Nama, -1, -1, 0);
                            PushCommand(S, C);
                    }
                    else
                    {
                            printf("Uang tidak mencukupi\n");
                    }
                }
                else
                {
                    printf("Waktu tidak cukup.\n");
                }
        }
        else
        {
                printf("Tidak terdapat barang pada List\n");
        }
}

void Build(ListW KamusWahana, List LC, int NMap, char *WName, ListMap *M, List *MatPemain, ListWMap *WMap, StackWMap *WBuild, int *s_waktu, int *s_aksi, CmdStack *S)
{
    int posx = PlayerX(MapN(*M, NMap));
    int posy = PlayerY(MapN(*M, NMap));
    int addtime = Value(LC, SearchList1(LC, "build"));
    if ((*s_waktu+addtime < 12*3600) && !SearchWMap(*WMap, posy, posx, NMap) && !SearchSWMap(*WBuild, posy, posx, NMap) && MapNElmt(*M, NMap, posy, posx) == '-') {
        int i;
        int IDWahana = IDFromWahana(KamusWahana, WName);
        int idx = SearchListWName(KamusWahana, IDWahana);
        boolean AvailMat = true;
        for (i = 0; i < 5; i++) {
            AvailMat = AvailMat && (Bahan(KamusWahana, idx, i) <= Value(*MatPemain, i));
        }
        if (AvailMat) {
            for (i = 0; i < 5; i++) {
                Value(*MatPemain, i) = Value(*MatPemain, i) - Bahan(KamusWahana, idx, i);
            }
            *s_waktu = *s_waktu+addtime;
            (*s_aksi)++;
            Command C;
            POINT pos = MakePOINT(posx, posy);
            PushWahana(WBuild, IDWahana, pos, NMap);
            AssignC(&C, 4, 0, IDWahana, "", posx, posy, NMap);
            PushCommand(S, C);
            boolean pindah;

            if (MapNElmt(*M, NMap, posy, posx-1) == '-' && !(SearchSWMap(*WBuild, posy, posx-1, NMap)) && !(SearchWMap(*WMap, posy, posx-1, NMap))) {
                Move(&MapN(*M, NMap), 'a', &pindah);
            } else if (MapNElmt(*M, NMap, posy, posx+1) == '-' && !(SearchSWMap(*WBuild, posy, posx+1, NMap)) && !(SearchWMap(*WMap, posy, posx+1, NMap))) {
                Move(&MapN(*M, NMap), 'd', &pindah);
            } else if (MapNElmt(*M, NMap, posy-1, posx) == '-' && !(SearchSWMap(*WBuild, posy-1, posx, NMap)) && !(SearchWMap(*WMap, posy-1, posx, NMap))) {
                Move(&MapN(*M, NMap), 'w', &pindah);
            } else if (MapNElmt(*M, NMap, posy+1, posx) == '-' && !(SearchSWMap(*WBuild, posy+1, posx, NMap)) && !(SearchWMap(*WMap, posy+1, posx, NMap))) {
                Move(&MapN(*M, NMap), 's', &pindah);
            }
        } else {
            printf("Bahan tidak cukup.\n");
        }
    } else {
        printf("Tidak bisa membangun disini.\n");
    }
}

void UndoBuild(ListW KamusWahana, List LC, List *MatPemain, StackWMap *WBuild, int *s_waktu, int *s_aksi, CmdStack *S)
{
    int i;
    int IDWahana;
    POINT pos;
    int NMap;
    Command C;
    PopWahana(WBuild, &IDWahana, &pos, &NMap);
    int idx = SearchListWName(KamusWahana, IDWahana);
    PopCommand(S, &C);
    for (i = 0; i < 5; i++) {
        Value(*MatPemain, i) = Value(*MatPemain, i) + Bahan(KamusWahana, idx, i);
    }
    int addtime = Value(LC, SearchList1(LC, "build"));
    *s_waktu = *s_waktu-addtime;
    (*s_aksi)--;
}

void UndoBuy(List LM, List LC, int *s_waktu, int *s_aksi, int*s_uang, CmdStack *S)
{
    Command C;
    PopCommand(S, &C);
    int Quantity = Jml(C);
    char *detail = Det(C);
    *s_uang = *s_uang-Quantity*Value(LM, SearchList1(LM, detail));
    int addtime = Value(LC, SearchList1(LC, "buy"));
    *s_waktu = *s_waktu-addtime;
    (*s_aksi)--;
}