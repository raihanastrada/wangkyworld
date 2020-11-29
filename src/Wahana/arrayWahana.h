/* File ListW of Wahana */
/* arrayWahana.h */

#ifndef ARRAYWAHANA_H
#define ARRAYWAHANA_H

#include "../Array/boolean.h"
#include "../Array/array.h"
#include "../Antrian/listlinier.h"

#define IdxMax 19 /* Indeks maksimum array */
#define IdxMin 0 /* Indeks minimum array */
#define IdxUndef -999 /* Indeks tak terdefinisi*/
#define ValUndef -1 /* Nilai tidak terdefinisi (Harga Barang/Durasi) */

typedef struct {
    char wname[50]; /* String nama wahana */
    int id; /* nomer ID wahana */
    int harga; /* uang yang didapat dari wahana */
    int kapasitas; /* kapasitas dari wahana */
    int duration; /* lama menaik wahana */
    char wdesc[50]; /* deskripsi wahana */
    int level; /* level upgrade wahana */
    int biaya; /* biaya upgrade wahana */
    int bahan[5]; /* bahan upgrade wahana */
} WahanaItem;
 
typedef struct { 
  WahanaItem T[IdxMax+1]; /* Array of WahanaItem */
} ListW ;

/********** SELEKTOR **********/
#define WName(L,i) (L).T[(i)].wname
#define ID(L,i) (L).T[(i)].id
#define Harga(L,i) (L).T[(i)].harga
#define Kapasitas(L,i) (L).T[(i)].kapasitas
#define Duration(L, i) (L).T[(i)].duration
#define WDesc(L,i) (L).T[(i)].wdesc
#define Level(L, i) (L).T[(i)].level
#define Biaya(L,i) (L).T[(i)].biaya
#define Bahan(L, i, j) (L).T[(i)].bahan[(j)]

void CreateListW(ListW *L);
/* I.S. L sembarang */
/* F.S. Terbentuk ListW L kosong dengan kapasitas IdxMax-IdxMin+1 */

void InitListW(ListW *L, char* filename);
/* I.S. ListW L kosong */
/* F.S. ListW L diisi data dari file eksternal (.txt) */

void PrintListW(ListW L);
/* I.S. ListW L tidak kosong */
/* F.S. Menampilkan ListW yang ada */

boolean SearchListWB(ListW L, int idx);
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan True jika WName terdapat pada ListW L */

int SearchListWName(ListW L, int idx);
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks WName pada ListW L, jika tidak ada mengembalika IdxUndef */

int SearchListWLvl(ListW L, int idx);
/* I.S. ListW L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks Level pada ListW L, jika tidak ada mengembalika IdxUndef */

void Build(ListW W, ListLin WahanaP, int idx, List *LM);
/* I.S. Parameter Fungsi Terdefinisi */
/* F.S. Uang berkurang sebanyak (harga barang)*(quantity), jika uang tidak cukup maka akan ditampilkan pesan error
        & proses tidak dijalankan */

#endif