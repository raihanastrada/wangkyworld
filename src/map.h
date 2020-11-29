#ifndef MAP_H
#define MAP_H

#include "../adt/boolean.h"
#include "./Wahana/arrayWMap.h"
#include "./Wahana/stackWMap.h"
// #include "adt/graph.h"

#define BrsMin 0
#define BrsMax 12
#define KolMin 0
#define KolMax 12
#define Nil -1
#define Field '-'
#define Player 'P'
#define Border '*'

typedef struct
{
    char Mem[BrsMax + 1][KolMax + 1]; /* Info elemen Map[i][j] */
    int NBrs; /* Banyaknya baris */
    int NKol; /* Banyaknya kolom */
    int PlayerX; /* Posisi Player dalam koordinat X */
    int PlayerY; /* Posisi Player dalam koordinat Y */
	int IDM;
    // Graph Left; 
    // Graph Right;
} Map;

typedef struct
{
    Map LM[4];
} ListMap;

/********** SELEKTOR **********/
#define NBrs(M) (M).NBrs
#define NKol(M) (M).NKol
#define Info(M,i,j) (M).Mem[(i)][(j)]
#define PlayerX(M) (M).PlayerX
#define PlayerY(M) (M).PlayerY
#define IDM(M) (M).IDM
#define MapN(ListM, N) (ListM).LM[N-1]
#define MapNElmt(ListM, N, i, j) (ListM).LM[N-1].Mem[i][j]
//#define Left(M) (M).Left
//#define Right(M) (M).Right

/********** KONSTRUKTOR **********/
void CreateMap(int NB, int NK, Map *M, int ID);
/* I.S. NB dan NK terdefinisi dan bernilai valid (NB & NK > 0) */
/* F.S. Terbentuk Map M dengan panjang baris NB dan panjang kolom NK */

void InitPlayer(Map *M, int X, int Y);

void RetractPlayer(Map *M);

void InitMap(Map *M, char *filename);
/* I.S. Map M kosong dan diisi */
/* F.S. Map terinisialisasi */

/********** OPERASI **********/
void PrintMap(Map M);
/* I.S. M terdefinisi */
/* F.S. M ditampilkan pada layar */

void PrintLegend();
/* Menampilkan Legenda Peta */

boolean IsBorder(Map M, int i, int j);
/* I.S. Matriks Terdefinisi */
/* F.S. Mengembalikan True jika Info[(i)][(j)] adalah border, border adalah bagian ujung (NBMin, NBMax, NKMin, NKMax) yang bukan gerbang */

boolean IsGerbang(Map M, int i, int j);
/* I.S. Matriks Terdefinisi */
/* F.S. Mengembalikan True jika Info[(i)][(j)] adalah gerbang */

boolean AvailInteraction(Map M, int i, int j);
/* I.S. baris dan kolom terdefinisi */
/* F.S. jika berada 1 petak di atas / bawah / kiri / kanan bangunan maka dapat berinteraksi */

void Gerak(Map *M);

void Move(Map *M, char move, boolean *pindah);
/* I.S. Matriks terdefinisi & tidak kosong */
/* F.S. Player bergerak berdasarkan input, 
jika menabrak pagar Player tetap pada posisi awal, 
jika berada di atas office maka dapat berinteraksi dengan office */

void MakeListMap(ListMap *ListM, Map M1, Map M2, Map M3, Map M4);
/* I.S. ListMap sembarang */
/* F.S. ListMap[0] berisi M1 ... hingga ListMap[3] berisi M4 */

#endif