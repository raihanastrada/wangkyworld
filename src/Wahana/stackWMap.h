/* File StackWMap of WahanaMap */
/* arrayWMap.h */

#ifndef STACKWMAP_H
#define STACKWMAP_H

#include "../Array/boolean.h"
#include "point.h"
#include "../map.h"
#include "stackWMap.h"
#include "arrayWahana.h"
#include "arrayWMap.h"

#define NilWM -1
#define MaxElWM 100

typedef int addrWMap;   /* indeks tabel */
typedef struct {
    int id; /* nomer ID wahana */
    POINT loc; /* tempat wahana pada map */
    int n_map; /* terletak pada map keberapa */
} WMapItem;
 
typedef struct { 
    WMapItem T[MaxElWM]; /* Array of WahanaItem */
    addrWMap TOP;
} StackWMap;

/********** SELEKTOR **********/
#define IDW(WM) (WM).id
#define Loc(WM) (WM).loc
#define Quadrant(WM) (WM).n_map
#define TopWMap(S) (S).TOP
#define TopItem(S) (S).T[(S).TOP]

void CreateWMEmpty (StackWMap *WMap);
/* I.S. sembarang; */
/* F.S. Membuat sebuah StackWMap WMap yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri StackWMap kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan stack ************ */
boolean IsWMEmpty (StackWMap WMap);
/* Mengirim true jika StackWMap kosong: lihat definisi di atas */
boolean IsWMFull (StackWMap WMap);
/* Mengirim true jika tabel penampung nilai elemen StackWMap penuh */
boolean IsPosTaken (StackWMap WBuild, ListWMap WMap, int IDWahana, POINT Pos, int NMap, ListW L);
/* Mengirim true jika terdapat building lain pada lokasi Pos pada peta ke-NMap */

/* ************ Menambahkan sebuah elemen ke StackWMap ************ */
void PushWahana (StackWMap *WMap, int idw, POINT pos, int nmap);
/* Menambahkan X sebagai elemen StackWMap WMap. */
/* I.S. S mungkin kosong, tabel penampung elemen StackWMap TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen StackWMap ************ */
void PopWahana (StackWMap *WMap, int *X, POINT *Y, int *Z);
/* Menghapus X dari StackWMap WMap. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif