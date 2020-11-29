/* File StackWMap of WahanaMap */
/* arrayWMap.c */

#include <stdio.h>
#include "../Array/boolean.h"
#include "point.h"
#include "../map.h"
#include "stackWMap.h"
#include "arrayWahana.h"
#include "arrayWMap.h"

void CreateWMEmpty (StackWMap *WMap)
/* I.S. sembarang; */
/* F.S. Membuat sebuah StackWMap WMap yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxElWM */
/* Ciri StackWMap kosong : TOP bernilai NilWM */
{
    TopWMap(*WMap) = NilWM;
}

/* ************ Predikat Untuk test keadaan stack ************ */
boolean IsWMEmpty (StackWMap WMap)
/* Mengirim true jika StackWMap kosong: lihat definisi di atas */
{
    return (TopWMap(WMap) == NilWM);
}
boolean IsWMFull (StackWMap WMap)
/* Mengirim true jika tabel penampung nilai elemen StackWMap penuh */
{
    return (TopWMap(WMap) == MaxElWM);
}

boolean IsPosTaken (StackWMap WBuild, ListWMap WMap, int IDWahana, POINT Pos, int NMap, ListW L)
/* Mengirim true jika terdapat building lain pada lokasi Pos pada peta ke-NMap */
{
    int i;
    int j;
    int lvlA;
    int lvlB;
    POINT Pos1;
    int N1;
    WMapItem WBuildItem;
    for (i = TopWMap(WBuild); i >= 0; i--) {
        WBuildItem = WBuild.T[i];
        Pos1 = Loc(WBuildItem);
        N1 = Quadrant(WBuildItem);
        if (EQ(Pos1, Pos) && N1 == NMap) {
            lvlA = SearchListWLvl(L, IDWahana);
            lvlB = SearchListWLvl(L, IDW(WBuildItem));
            if (lvlA <= lvlB) {
                return false;
            }
        }
    }
    return true;
}

boolean SearchSWMap(StackWMap WMap, int posy, int posx, int NMap)
{
    int i;
    WMapItem WMI;
    for (i = 0; i < TopWMap(WMap)+1; i++) {
        WMI = WMap.T[i];
        if (Absis(Loc(WMI)) == posx && Ordinat(Loc(WMI)) == posy && Quadrant(WMI) == NMap) {
            return true;
        }
    }
    return false;
}

/* ************ Menambahkan sebuah elemen ke StackWMap ************ */
void PushWahana (StackWMap *WMap, int idw, POINT pos, int nmap)
/* Menambahkan X sebagai elemen StackWMap WMap. */
/* I.S. S mungkin kosong, tabel penampung elemen StackWMap TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    TopWMap(*WMap)++;
    IDW(TopItem(*WMap)) = idw;
    Loc(TopItem(*WMap)) = pos;
    Quadrant(TopItem(*WMap)) = nmap;
}

/* ************ Menghapus sebuah elemen StackWMap ************ */
void PopWahana (StackWMap *WMap, int *X, POINT *Y, int *Z)
/* Menghapus X dari StackWMap WMap. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    *X = IDW(TopItem(*WMap));
    *Y = Loc(TopItem(*WMap));
    *Z = Quadrant(TopItem(*WMap));
    TopWMap(*WMap)--;
}