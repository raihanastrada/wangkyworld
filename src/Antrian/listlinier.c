/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addrList dengan pointer */
/* infotypeL adalah integer */

/*  NIM         : 13519205
    Nama        : Muhammad Rifat Abiwardani
    Tanggal     : 4 Oktober 2020
    Topik       : ADT ListLin
    Deskripsi   : Merealisasikan ADT ListLin
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Array/boolean.h"
#include "listlinier.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsLEmpty (ListLin L)
/* Mengirim true jika list kosong */
{
    return (FirstL(L) == NilN);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateLEmpty (ListLin *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FirstL(*L) = NilN;
}

/****************** Manajemen Memori ******************/
addrList AlokasiL (infotypeL X)
/* Mengirimkan addrList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrList tidak NilN, dan misalnya */
/* menghasilkan P, maka InfoL(P)=X, NextL(P)=NilN */
/* Jika alokasi gagal, mengirimkan NilN */
{
    addrList P = (addrList) malloc (sizeof(addrList));
    if (P != NULL) {
        InfoL(P) = X;
        NextL(P) = NilN;
    } else {
        P = NilN;
    }
    return P;
}
void DealokasiL (addrList *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrList P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addrList SearchL (ListLin L, infotypeL X)
/* Mencari apakah ada elemen list dengan InfoL(P)= X */
/* Jika ada, mengirimkan addrList elemen tersebut. */
/* Jika tidak ada, mengirimkan NilN */
{
    if (IsLEmpty(L)) {
        return NilN;
    } else {
        addrList P1 = FirstL(L);
        while ((NextL(P1) != NilN) && InfoL(P1) != X) {
            P1 = NextL(P1);
        }
        if (InfoL(P1) == X) {
            return P1;
        } else {
            return NilN;
        }
    }
}
boolean FSearchL (ListLin L, addrList P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    if (IsLEmpty(L)) {
        return (P == NilN);
    } else {
        addrList P1 = FirstL(L);
        while (NextL(P1) != NilN && P1 != P) {
            P1 = NextL(P1);
        }
        return (P1 == P);
    }
}
addrList SearchLPrec (ListLin L, infotypeL X)
/* Mengirimkan addrList elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan InfoL(P)=X */
/* Jika ada, mengirimkan addrList Prec, dengan NextL(Prec)=P dan InfoL(P)=X. */
/* Jika tidak ada, mengirimkan NilN */
/* Jika P adalah elemen pertama, maka Prec=NilN */
/* SearchL dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah SearchL akan dilakukan operasi lain */
{
    if (IsLEmpty(L)) {
        return NilN;
    } else {
        addrList P1 = FirstL(L);
        addrList P2 = NilN;
        while ((NextL(P1) != NilN) && InfoL(P1) != X) {
            P2 = P1;
            P1 = NextL(P1);
        }
        if (InfoL(P1) == X) {
            return P2;
        } else {
            return NilN;
        }
    }
}

/****************** PRIMITIF BERDASARKAN nilai ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstL (ListLin *L, infotypeL X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    addrList P = AlokasiL(X);
    if (P != NULL) {
        if (!IsLEmpty(*L)) {
            NextL(P) = FirstL(*L);
        }
        FirstL(*L) = P;
    }
}
void InsVLastL (ListLin *L, infotypeL X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    addrList P = AlokasiL(X);
    if (P != NULL) {
        if (IsLEmpty(*L)) {
            FirstL(*L) = P;
        } else {
            addrList P1 = FirstL(*L);
            while (NextL(P1) != NilN) {
                P1 = NextL(P1);
            }
            NextL(P1) = P;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstL (ListLin *L, infotypeL *X)
/* I.S. ListLin L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    addrList P = FirstL(*L);
    FirstL(*L) = NextL(FirstL(*L));
    *X = InfoL(P);
    DealokasiL(&P);
}
void DelVLastL (ListLin *L, infotypeL *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    addrList P1 = FirstL(*L);
    addrList P2;
    while (NextL(P1) != NilN) {
        P2 = P1;
        P1 = NextL(P1);
    }
    NextL(P2) = NilN;
    *X = InfoL(P1);
    DealokasiL(&P1);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstL (ListLin *L, addrList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addrList P sebagai elemen pertama */
{
    NextL(P) = FirstL(*L);
    FirstL(*L) = P;
}
void InsertAfter (ListLin *L, addrList P, addrList Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    NextL(P) = NextL(Prec);
    NextL(Prec) = P;
}
void InsertLastL (ListLin *L, addrList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    NextL(P) = NilN;
    if (IsLEmpty(*L)) {
        FirstL(*L) = P;
    } else {
        addrList P1 = FirstL(*L);
        while (NextL(P1) != NilN) {
            P1 = NextL(P1);
        }
        NextL(P1) = P;
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstL (ListLin *L, addrList *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* FirstL element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = FirstL(*L);
    FirstL(*L) = NextL(FirstL(*L));
}
void DelP (ListLin *L, infotypeL X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddrList P, dengan InfoL(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan InfoL(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    addrList P = SearchL(*L, X);
    if (P != NilN) {
        addrList P1 = FirstL(*L);
        if (P1 == P) {
            FirstL(*L) = NilN;
        } else {
            while (NextL(P1) != P) {
                P1 = NextL(P1);
            }
            NextL(P1) = NextL(P);
            DealokasiL(&P);
        }
    }
}
void DelLastL (ListLin *L, addrList *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* LastL element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    addrList P1 = FirstL(*L);
    addrList P2;
    while (NextL(P1) != NilN) {
        P2 = P1;
        P1 = NextL(P1);
    }
    *P = P1;
    if (P1 == FirstL(*L)) {
        FirstL(*L) = NilN;
    } else {
        NextL(P2) = NilN;
    }
}
void DelAfter (ListLin *L, addrList *Pdel, addrList Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus NextL(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    *Pdel = NextL(Prec);
    NextL(Prec) = NextL(NextL(Prec));
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (ListLin L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
    if (!IsLEmpty(L)) {
        addrList P1 = FirstL(L);
        int count = 0;
        while (NextL(P1) != NilN) {
            printf("%d,", InfoL(P1));
            P1 = NextL(P1);
        }
        if (NextL(P1) == NilN) {
            printf("%d", InfoL(P1));
        }
    }
    printf("]");
}
int NbElmtL (ListLin L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    if (IsLEmpty(L)) {
        return 0;
    } else {
        int i = 1;
        addrList P1 = FirstL(L);
        while (NextL(P1) != NilN) {
            P1 = NextL(P1);
            i++;
        }
        return i;
    }
}

/*** Prekondisi untuk Max: List tidak kosong ***/
infotypeL Max (ListLin L)
/* Mengirimkan nilai InfoL(P) yang maksimum */
{
    infotypeL max = InfoL(FirstL(L));
    addrList P1 = FirstL(L);
    while (NextL(P1) != NilN) {
        P1 = NextL(P1);
        if (InfoL(P1) > max) {
            max = InfoL(P1);
        }
    }
    return max;
}
addrList AdrMax (ListLin L)
/* Mengirimkan addrList P, dengan InfoL(P) yang bernilai maksimum */
{
    addrList adrmax = FirstL(L);
    addrList P1 = FirstL(L);
    while (NextL(P1) != NilN) {
        P1 = NextL(P1);
        if (InfoL(P1) > InfoL(adrmax)) {
            adrmax = P1;
        }
    }
    return adrmax;
}
/*** Prekondisi untuk Min: List tidak kosong ***/
infotypeL Min (ListLin L)
/* Mengirimkan nilai InfoL(P) yang minimum */
{
    infotypeL min = InfoL(FirstL(L));
    addrList P1 = FirstL(L);
    while (NextL(P1) != NilN) {
        P1 = NextL(P1);
        if (InfoL(P1) < min) {
            min = InfoL(P1);
        }
    }
    return min;
}
addrList AdrMin (ListLin L)
/* Mengirimkan addrList P, dengan InfoL(P) yang bernilai minimum */
{
    addrList adrmin = FirstL(L);
    addrList P1 = FirstL(L);
    while (NextL(P1) != NilN) {
        P1 = NextL(P1);
        if (InfoL(P1) < InfoL(adrmin)) {
            adrmin = P1;
        }
    }
    return adrmin;
}
float Average (ListLin L)
/* Mengirimkan nilai rata-rata InfoL(P) */
{
    int sum = InfoL(FirstL(L));
    float i = 1;
    addrList P1 = FirstL(L);
    while (NextL(P1) != NilN) {
        P1 = NextL(P1);
        sum += InfoL(P1);
        i++;
    }
    return (float) sum/i;
}

/****************** PROSES TERHADAP LIST ******************/
void DelAll (ListLin *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
    addrList P;
    while (!IsLEmpty(*L)) {
        DelFirstL(L, &P);
        DealokasiL(&P);
    }
}

void InversList (ListLin *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
    if (!IsLEmpty(*L)) {
        addrList P1 = FirstL(*L);
        addrList P2 = P1;
        while (NextL(P2) != NilN) {
            P1 = NextL(P2);
            NextL(P2) = NextL(P1);
            NextL(P1) = FirstL(*L);
            FirstL(*L) = P1;
        }
    }
}

ListLin FInversList (ListLin L)
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
    ListLin L1;
    CreateLEmpty(&L1);
    if (!IsLEmpty(L)) {
        addrList P1 = FirstL(L);
        addrList P = NilN;
        while (P1 != NilN) {
            P = AlokasiL(InfoL(P1));
            P1 = NextL(P1);
            if (P != NilN) {
                InsertFirstL(&L1, P);
            } else {
                break;
            }
        }
        if (P == NilN) {
            DelAll(&L1);
        }
    }
    return L1;
}

void CopyList (ListLin *L1, ListLin *L2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
    FirstL(*L2) = FirstL(*L1);
}

ListLin FCopyList (ListLin L)
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
    ListLin L1;
    CreateLEmpty(&L1);
    if (!IsLEmpty(L)) {
        addrList P1 = FirstL(L);
        addrList P = NilN;
        while (P1 != NilN) {
            P = AlokasiL(InfoL(P1));
            P1 = NextL(P1);
            if (P != NilN) {
                InsertLastL(&L1, P);
            } else {
                break;
            }
        }
        if (P == NilN) {
            DelAll(&L1);
        }
    }
    return L1;
}

void CpAlokList (ListLin Lin, ListLin *Lout)
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=NilN dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
{
    CreateLEmpty(Lout);
    if (!IsLEmpty(Lin)) {
        addrList P1 = FirstL(Lin);
        addrList P = AlokasiL(InfoL(P1));
        InsertFirstL(Lout, P);
        while (NextL(P1) != NilN && P != NilN) {
            InsertLastL(Lout, P);
            P1 = NextL(P1);
            P = AlokasiL(InfoL(P1));
        }
        if (P == NilN) {
            DelAll(Lout);
        }
    }
}

void Konkat (ListLin L1, ListLin L2, ListLin * L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=NilN*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai NilN*/
/* dan semua elemen yang pernah dialokasi didealokasi */
{
    addrList P = FirstL(L1);
    CreateLEmpty(L3);
    while (!IsLEmpty(L1) && P != NilN) {
        DelFirstL(&L1, &P);
        InsertLastL(L3, P);
    }
    while (!IsLEmpty(L2) && P != NilN) {
        DelFirstL(&L2, &P);
        InsertLastL(L3, P);
    }
    if (P == NilN) {
        DelAll(L3);
    }
}

void Konkat1 (ListLin *L1, ListLin *L2, ListLin *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen ListLin L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    addrList P;
    CreateLEmpty(L3);
    while (!IsLEmpty(*L1)) {
        DelFirstL(L1, &P);
        InsertLastL(L3, P);
    }
    while (!IsLEmpty(*L2)) {
        DelFirstL(L2, &P);
        InsertLastL(L3, P);
    }
}

void PecahList (ListLin *L1, ListLin *L2, ListLin L)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah ListLin L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmtL(L) div 2 */
{
    int n = NbElmtL(L)/2;
    int i;
    CreateLEmpty(L1);
    CreateLEmpty(L2);
    addrList P1 = FirstL(L);
    addrList P;
    boolean success = true;
    for (i = 0; i < n; i++) {
        InsVLastL(L1, InfoL(P1));
        P1 = NextL(P1);
        if (FirstL(*L1) == NilN) {
            success = false;
            break;
        }
    }
    if (success) {
        for (i = n; i < NbElmtL(L); i++) {
            InsVLastL(L2, InfoL(P1));
            P1 = NextL(P1);
            if (FirstL(*L1) == NilN) {
                success = false;
                break;
            }
        }
    }
    if (!success) {
        DelAll(L1);
        DelAll(L2);
    }
}