/* File : cmdstack.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef cmdstack_H
#define cmdstack_H

#include "boolean.h"
#include "../Jam/jam.h"
#include "../Wahana/point.h"

#define NilS -1
#define MaxEl 100
/* Nil adalah CmdStack dengan elemen kosong . */

typedef int address;   /* indeks tabel */
typedef struct {
    int idx; /* indeks command, sesuai main.c */
    int amount; /* jumlah, jika buy */
    int wahana; /* wahana, jika build/upgrade */
    char detail[20]; /* nama item, jika buy */
    POINT position; /* lokasi pada map, jika build/upgrade */
    int n_map; /* terletak pada map keberapa, jika build/upgrade */
} Command;

/* Contoh deklarasi variabel bertype CmdStack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  Command T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} CmdStack;
/* Definisi CmdStack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai CmdStack T[0]..T[MaxEl-1] */
/* Jika S adalah CmdStack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Idx(C) (C).idx
#define Jml(C) (C).amount
#define Whn(C) (C).wahana
#define Det(C) (C).detail
#define Posn(C) (C).position
#define NMap(C) (C).n_map
#define TopS(S) (S).TOP
#define InfoTopS(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateCEmpty (Command *C, int idx, int amount, int wahana, char detail[20], int posX, int posY, int nmap);
/* I.S. sembarang */
/* F.S. Membuat Command C dengan index command idx, jumlah (jika tidak 0) amount */
/* index wahana (jika tidak 0) wahana, dan keterangan (jika tidak kosong) detail */

void CreateSEmpty (CmdStack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah CmdStack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri CmdStack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (CmdStack S);
/* Mengirim true jika CmdStack kosong: lihat definisi di atas */
boolean IsSFull (CmdStack S);
/* Mengirim true jika tabel penampung nilai elemen CmdStack penuh */

/* ************ Menambahkan sebuah elemen ke CmdStack ************ */
void PushCommand (CmdStack * S, infotype X);
/* Menambahkan X sebagai elemen CmdStack S. */
/* I.S. S mungkin kosong, tabel penampung elemen CmdStack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen CmdStack ************ */
void PopCommand (CmdStack * S, infotype* X);
/* Menghapus X dari CmdStack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

/* ************ Menjalankan Command pada CmdStack ************ */
void ExecuteCommand (CmdStack *S, int *uang, int *s_aksi, int *s_waktu, int *s_uang, JAM *time_curr, JAM *time_goal, JAM *time_remain, Map *M, List *ListMat);
/* menjalankan command-command yang ada di CmdStack S */
/* I.S. S mungkin kosong */
/* F.S. melakukan build/upgrade/buy sesuai command yang ada di CmdStack, lalu mulai main phase */

#endif
