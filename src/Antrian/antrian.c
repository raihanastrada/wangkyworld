/* File : Antrianlinier.h */
/* contoh ADT Antrian berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */

/*  NIM         : 13519205
    Nama        : Muhammad Rifat Abiwardani
    Tanggal     : 4 Oktober 2020
    Topik       : ADT Antrian Linier
    Deskripsi   : Merealisasikan ADT Antrian Linier
*/

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "antrian.h"
#include "listlinier.h"

/* PROTOTYPE */
/****************** TEST Antrian KOSONG ******************/
boolean IsAEmpty (Antrian A)
/* Mengirim true jika Antrian kosong */
{
    return (FirstA(A) == NilN && LastA(A) == NilN);
}

/****************** PEMBUATAN Antrian KOSONG ******************/
void CreateAEmpty (Antrian *A)
/* I.S. sembarang             */
/* F.S. Terbentuk Antrian kosong */
{
    FirstA(*A) = NilN;
    LastA(*A) = NilN;
}

/****************** Manajemen Memori ******************/
addrA AlokasiA (int X, List W)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NilN, dan misalnya */
/* menghasilkan P, maka Info(P)=X, NextA(P)=NilN */
/* Jika alokasi gagal, mengirimkan NilN */
{
    addrA E = (addrA) malloc (sizeof(ElmtAntrian));
    if (E != NULL) {
        Prio(E) = X;
        Wahana(E) = W;
        NextA(E) = NilN;
    } else {
        E = NilN;
    }
    return E;
}
void DealokasiA (addrA *E)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrA P */
{
    free(*E);
}

/****************** PENCARIAN SEBUAH ELEMEN ANTRIAN ******************/
addrA SearchA (Antrian A, int X)
/* Mencari apakah ada elemen Antrian dengan Info(P) < X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan NilN */
{
    if (IsAEmpty(A)) {
        return NilN;
    } else {
        addrA P1 = FirstA(A);
        while ((NextA(P1) != NilN) && Prio(P1) >= X) {
            P1 = NextA(P1);
        }
        if (Prio(P1) < X) {
            return P1;
        } else {
            return LastA(A);
        }
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void Antri (Antrian *A, int X, List W)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen Antrian di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    addrA E = AlokasiA(X, W);
    if (E != NULL) {
        if (IsAEmpty(*A)) {
            FirstA(*A) = E;
            LastA(*A) = E;
        } else if (NextA(FirstA(*A)) == NilN) {
            if (Prio(FirstA(*A)) >= X) {
                NextA(FirstA(*A)) = E;
                LastA(*A) = E;
            } else {
                NextA(E) = FirstA(*A);
                FirstA(*A) = E;
            }
        } else {
            addrA E1 = FirstA(*A);
            while (NextA(E1) != NilN) {
                if (Prio(NextA(E1)) >= X) {
                    E1 = NextA(E1);
                    if (NextA(E1) == NilN) {
                        NextA(E1) = E;
                        LastA(*A) = E;
                        break;
                    }
                } else {
                    if (E1 == FirstA(*A)) {
                        FirstA(*A) = E;
                        NextA(E) = E1;
                    } else {
                        NextA(E) = NextA(E1);
                        NextA(E1) = E;
                    }
                    break;
                }
            }
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void Keluar (Antrian *A, int *X, List *W)
/* I.S. Antrian L tidak kosong  */
/* F.S. Elemen pertama Antrian dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    addrA E = FirstA(*A);
    FirstA(*A) = NextA(FirstA(*A));
    if (FirstA(*A) == NilN) {
        LastA(*A) = NilN;
    }
    *X = Prio(E);
    *W = Wahana(E);
    DealokasiA(&E);
}

/****************** PROSES SEMUA ELEMEN Antrian ******************/
int PanjangA (Antrian A)
/* Mengirimkan banyaknya pengunjung dalam Antrian; mengirimkan 0 jika Antrian kosong */
{
    if (IsAEmpty(A)) {
        return 0;
    } else {
        int i = 1;
        addrA E1 = FirstA(A);
        while (NextA(E1) != NilN) {
            E1 = NextA(E1);
            i++;
        }
        return i;
    }
}

/* PROSEDUR GAME */
void GeneratePengunjung(Antrian *Antrian, List Wahana, int N, int seed) {
    int Length = NbElmtL(Wahana);
    srand(Length);
    int i;
    int j;
    int k;
    addrList W;
    List Wishlist;
    CreateAEmpty(Antrian);
    for (i = 0; i < N; i++) {
        CreateLEmpty(&Wishlist);

        for (j = seed; j > 0; j--) {
            k = (rand() % Length)+1;
        }

        while (NbElmtL(Wishlist) < k) {
            W = FirstL(Wahana);
            for (j = (rand() % Length); j > 0; j--) {
                W = NextL(W);
            }

            while (SearchL(Wishlist, InfoL(W)) != NilN) {
                W = FirstL(Wahana);
                for (j = (rand() % Length); j > 0; j--) {
                    W = NextL(W);
                }
            }

            InsVFirstL(&Wishlist, InfoL(W));
        }

        Antri(Antrian, 1, Wishlist);
    }
}