/* File : cmdstack.h */
/* realisasi ADT cmdstack */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include <stdio.h>
#include "boolean.h"
#include "cmdstack.h"
#include "../Jam/jam.h"

/*
    Nama        : Muhammad Rifat Abiwardani
    NIM         : 13519205
    Tanggal     : 21 Oktober 2020
    Praktikum   : 8
    Deskripsi   : Realisasi ADT cmdstack
*/

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void AssignC (Command *C, int idx, int amount, int wahana, char detail[20]);
/* I.S. sembarang */
/* F.S. Membuat Command C dengan index command idx, jumlah (jika tidak 0) amount */
/* index wahana (jika tidak 0) wahana, dan keterangan (jika tidak kosong) detail */
{
    Idx(*C) = idx;
    Jml(*C) = amount;
    Whn(*C) = wahana;
    Det(*C) = detail;
}

void CreateSEmpty (CmdStack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah CmdStack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri CmdStack kosong : TOP bernilai Nil */
{
    Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (CmdStack S)
/* Mengirim true jika CmdStack kosong: lihat definisi di atas */
{
    return (Top(S) == Nil);
}
boolean IsSFull (CmdStack S)
/* Mengirim true jika tabel penampung nilai elemen CmdStack penuh */
{
    return (Top(S) == MaxEl-1);
}

/* ************ Menambahkan sebuah elemen ke CmdStack ************ */
void Push (CmdStack *S, Command C)
/* Menambahkan X sebagai elemen CmdStack S. */
/* I.S. S mungkin kosong, tabel penampung elemen CmdStack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    Top(*S) += 1;
    InfoTop(*S) = C;
}

/* ************ Menghapus sebuah elemen CmdStack ************ */
void Pop (CmdStack *S, Command *C)
/* Menghapus X dari CmdStack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    *C = InfoTop(*S);
    Top(*S) -= 1;
}

/* ************ Menjalankan Command pada CmdStack ************ */
void ExecuteCommand (CmdStack *S, int *s_aksi, int *s_waktu, int *s_uang, JAM *time_curr, JAM *time_goal, JAM *time_remain)
/* menjalankan command-command yang ada di CmdStack S */
/* I.S. S mungkin kosong */
/* F.S. melakukan build/upgrade/buy sesuai command yang ada di stack, lalu mulai main phase */
{
    int i;
    while (s_aksi > 0) {
        i = 0;
    }
}