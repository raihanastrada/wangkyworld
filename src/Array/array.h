/* File List of Materials */
/* materials.h */

#ifndef ARRAY_H
#define ARRAY_H

#include "boolean.h"

#define IdxMax 19 /* Indeks maksimum array */
#define IdxMin 0 /* Indeks minimum array */
#define IdxUndef -999 /* Indeks tak terdefinisi*/
#define ValUndef -1 /* Nilai tidak terdefinisi (Harga Barang/Durasi) */

typedef struct {
    char key[50]; /* String nama barang atau command */
    int value; /* Harga barang atau durasi command */
} Tuple;
 
typedef struct { 
  Tuple T[IdxMax+1]; /* Array of Tuple */
} List ;

/********** SELEKTOR **********/
#define Key(L,i) (L).T[(i)].key
#define Value(L,i) (L).T[(i)].value

void CreateList(List *L);
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan kapasitas IdxMax-IdxMin+1 */

void InitList1(List *L);
/* I.S. List L kosong */
/* F.S. List L diisi data dari input */

void InitList2(List *L, char *filename);
/* I.S. List L kosong */
/* F.S. List L diisi data dari file eksternal (.txt) */

void InitList3(List *L, char *filename);
/* I.S. List L kosong */
/* F.S. List L diisi data dari file eksternal (.txt) */

void PrintListM(List L);
/* I.S. List L tidak kosong */
/* F.S. Menampilkan List yang ada, untuk menampilkan list pada buy */

boolean SearchListB(List L, char *Key);
/* I.S. List L dan Nama terdefinisi */
/* F.S. Mengembalikan True jika Key terdapat pada List L */

int SearchList1(List L, char *Key);
/* I.S. List L dan Nama terdefinisi */
/* F.S. Mengembalikan indeks Key pada List L, jika tidak ada mengembalika IdxUndef */

#endif