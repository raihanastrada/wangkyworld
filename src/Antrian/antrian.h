/* File : antrian.h */
/* contoh ADT antrian berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#ifndef antrian_H
#define antrian_H

#include "../Array/boolean.h"
#include "listlinier.h"

#define NilN NULL

typedef struct tElmtAntrian *addrA;
typedef struct tElmtAntrian { 
	int priority;
    ListLin wahana;
	int kesabaran;
	addrA nextA;
} ElmtAntrian;
typedef struct {
	addrA FirstA;
    addrA LastA;
} Antrian;

#define Prio(E) (E)->priority
#define Wahana(E) (E)->wahana
#define Patience(E) (E)->kesabaran
#define NextA(E) (E)->nextA
#define FirstA(A) ((A).FirstA)
#define LastA(A) ((A).LastA)

/* PROTOTYPE */
/****************** TEST Antrian KOSONG ******************/
boolean IsAEmpty (Antrian A);
/* Mengirim true jika Antrian kosong */

/****************** PEMBUATAN Antrian KOSONG ******************/
void CreateAEmpty (Antrian *A);
/* I.S. sembarang             */
/* F.S. Terbentuk Antrian kosong */

/****************** Manajemen Memori ******************/
addrA AlokasiA (int X, ListLin W, int K);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiA (addrA *E);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN Antrian ******************/
addrA SearchA (Antrian A, int X);
/* Mencari apakah ada elemen Antrian dengan info(P)< X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan last */

addrA SearchK (Antrian A, int K);
/* Mencari apakah ada elemen Antrian dengan Patience(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void Antri (Antrian *A, int X, ListLin W, int K);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen Antrian di posisi sesuai prioritas */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void Keluar (Antrian *A, int *X, ListLin *W, int *K);
/* I.S. Antrian L tidak kosong  */
/* F.S. Elemen pertama Antrian dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void HilangSabar (Antrian *A);
/* I.S. Antrian L tidak kosong  */
/* F.S. Elemen dengan kesabaran 0 dihapus */

/****************** PROSES SEMUA ELEMEN Antrian ******************/
int PanjangA (Antrian A);
/* Mengirimkan banyaknya pengunjung dalam Antrian; mengirimkan 0 jika Antrian kosong */

void GeneratePengunjung(Antrian *Antrian, ListLin Wahana, int N, int seed);
/* Menghasilkan N banyak pengunjung yang ingin menaiki jumlah wahana random dari Wahana; random buffer sebanyak seed kali */

#endif