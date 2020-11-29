/* File ListWMap of Wahana */
/* arrayWMap.h implementasi eksplisit */

#ifndef ARRAYWMAP_H
#define ARRAYWMAP_H

#include "../Array/boolean.h"
#include "../Array/array.h"
#include "point.h"

#define IdxMaxW 99 /* Indeks maksimum array */
#define IdxMinW 0 /* Indeks minimum array */
#define IdxUndefW -999 /* Indeks tak terdefinisi*/
#define ValUndefW -1 /* Nilai tidak terdefinisi (Harga Barang/Durasi) */
 
typedef struct {
    int id; /* nomer ID wahana */
    POINT loc; /* tempat wahana pada map */
    int n_map; /* terletak pada map keberapa */
} WMapItemCopy;

typedef struct { 
  WMapItemCopy T[IdxMaxW+1]; /* Array of WahanaItem */
  int length;
} ListWMap;

/********** SELEKTOR **********/
#define IDW(WM) (WM).id
#define Loc(WM) (WM).loc
#define Quadrant(WM) (WM).n_map
#define WMItem(WM, i) (WM).T[i]
#define LenWM(WM) (WM).length

void CreateLWMEmpty(ListWMap *WMap);
/* I.S. ListWMap sembarang */
/* F.S. ListWMap[IdxMin] = ValUndef */

boolean IsLWMEmpty(ListWMap WMap);
/* Mengembalikan true jika WMap kosong */
boolean IsLWMFull(ListWMap WMap);
/* Mengembalikan true jika WMap penuh */
boolean SearchLWM(ListWMap WMap, int ID, POINT Pos, int NMap);
/* Mengembalikan true jika ada WMapItem dalam WMap dengan IDW, Pos, NMap */
boolean SearchWMap(ListWMap WMap, int posx, int posy, int NMap);
/* Mengembalikan true jika ada WMapItem dalam WMap di lokasi (posx, posy) */

void PushLWM(ListWMap *WMap, int ID, POINT Pos, int NMap);
/* Menyimpan wahana item baru */
/* prekondisi: IsPosTaken() false */

void DeleteLWM(ListWMap *WMap, int ID, POINT Pos, int NMap);
/* Menghapus wahana item dari ListWMap */
/* prekondisi: ada WMapItem dalam WMap dengan IDW, Pos, NMap */

#endif