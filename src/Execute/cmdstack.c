/* File : cmdstack.h */
/* realisasi ADT cmdstack */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include <stdio.h>
#include "boolean.h"
#include "cmdstack.h"
#include "../Array/array.h"
#include "../Jam/jam.h"
#include "../Wahana/point.h"
#include "../map.h"

int strcmp(const char* str1, const char* str2);
char* strcpy(char* destination, const char* source);
char* strcat(char *s1, const char *s2);

/*
    Nama        : Muhammad Rifat Abiwardani
    NIM         : 13519205
    Tanggal     : 21 Oktober 2020
    Praktikum   : 8
    Deskripsi   : Realisasi ADT cmdstack
*/

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void AssignC (Command *C, int idx, int amount, int wahana, char detail[20], int posX, int posY, int nmap);
/* I.S. sembarang */
/* F.S. Membuat Command C dengan index command idx, jumlah (jika tidak 0) amount */
/* index wahana (jika tidak 0) wahana, dan keterangan (jika tidak kosong) detail */
{
    Idx(*C) = idx;
    Jml(*C) = amount;
    Whn(*C) = wahana;
    Det(*C) = detail;
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
    TopS(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (CmdStack S)
/* Mengirim true jika CmdStack kosong: lihat definisi di atas */
{
    return (TopS(S) == Nil);
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

/* ************ Menjalankan Command pada CmdStack ************ */
void ExecuteCommand (CmdStack *S, int *uang, int *s_aksi, int *s_waktu, int *s_uang, JAM *time_curr, JAM *time_goal, JAM *time_remain, ListMap *ListM, List *ListMat)
/* menjalankan command-command yang ada di CmdStack S */
/* I.S. S mungkin kosong */
/* F.S. melakukan build/upgrade/buy sesuai command yang ada di stack, lalu mulai main phase */
{
    int idx;
    int amount;
    int wahana;
    char detail[50];
    POINT position;
    int n_map;
    while (s_aksi > 0) {
        PopCommand(S, &idx, &amount, &wahana, &detail, &position, &n_map);
        if (idx == 4) {
            MapNElmt(ListM, n_map, ordinat(position), absis(position)) = 'W';
        } else if (idx == 5) {
            // upgrade
        } else if (idx == 6) {
            boolean found = false;
            int i = IdxMin;
            while( (strcmp(Key(*ListMat,i),"undef") != 0) && !found) { // Looping selama Key tidak "kosong"
                if (strcmp(Key(*ListMat,i),Key) == 0) { // Jika ditemukan Key pada List
                    found = true;
                } else {
                    i++;
                }
            }
        }
    }

    *uang = *uang-*s_uang;

    *time_curr = MakeJAM(9,0,0);
    *time_goal = MakeJAM(21,0,0);
    *s_uang = 0;
    *s
}