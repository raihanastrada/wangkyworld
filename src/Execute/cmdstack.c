/* File : cmdstack.h */
/* realisasi ADT cmdstack */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include <stdio.h>
#include "../Array/boolean.h"
#include "cmdstack.h"
#include "../Wahana/point.h"

char* strcpy(char* destination, const char* source);

/*
    Nama        : Muhammad Rifat Abiwardani
    NIM         : 13519205
    Tanggal     : 21 Oktober 2020
    Praktikum   : 8
    Deskripsi   : Realisasi ADT cmdstack
*/

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void AssignC (Command *C, int idx, int amount, int wahana, char *detail, int posX, int posY, int nmap)
/* I.S. sembarang */
/* F.S. Membuat Command C dengan index command idx, jumlah (jika tidak 0) amount */
/* index wahana (jika tidak 0) wahana, dan keterangan (jika tidak kosong) detail */
{
    Idx(*C) = idx;
    Jml(*C) = amount;
    Whn(*C) = wahana;
    strcpy(Det(*C), detail);
    POINT pos = MakePOINT(posX, posY);
    Posn(*C) = pos;
    NMap(*C) = nmap;
}

void CreateSEmpty (CmdStack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah CmdStack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri CmdStack kosong : TOP bernilai Nil */
{
    TopS(*S) = NilS;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (CmdStack S)
/* Mengirim true jika CmdStack kosong: lihat definisi di atas */
{
    return (TopS(S) == NilS);
}
boolean IsSFull (CmdStack S)
/* Mengirim true jika tabel penampung nilai elemen CmdStack penuh */
{
    return (TopS(S) == MaxEl-1);
}

/* ************ Menambahkan sebuah elemen ke CmdStack ************ */
void PushCommand (CmdStack *S, Command C)
/* Menambahkan X sebagai elemen CmdStack S. */
/* I.S. S mungkin kosong, tabel penampung elemen CmdStack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    TopS(*S) += 1;
    InfoTopS(*S) = C;
}

/* ************ Menghapus sebuah elemen CmdStack ************ */
void PopCommand (CmdStack *S, Command *C)
/* Menghapus X dari CmdStack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    *C = InfoTopS(*S);
    TopS(*S) -= 1;
}