/* map.c */
/* Realisasi map.h */

#include "map.h"
#include "./MesinKata/mesinkata.h"
#include "./Wahana/arrayWMap.h"
#include "./Wahana/stackWMap.h"
#include <stdio.h>
#include <stdlib.h>


/********** KONSTRUKTOR **********/
void CreateMap(int NB, int NK, Map *M, int ID)
/* I.S. NB dan NK terdefinisi dan bernilai valid (NB & NK > 0) */
/* F.S. Terbentuk Map M dengan panjang baris NB dan panjang kolom NK */
{
    
    NBrs(*M) = NB;
    NKol(*M) = NK;
    int i,j;
    for (i = BrsMin; i < NB; i++)
    {
        for (j = KolMin; j < NK; j++)
        {
				Info(*M,i,j) = Nil;
        }
    }
    PlayerX(*M) = Nil;
    PlayerY(*M) = Nil;
	IDM(*M) = ID;
}

void InitPlayer(Map *M,int X, int Y)
/* I.S. Map Terdefinisi */
/* F.S. Map Memindahkan posisi (X,Y) player. PlayerX = X, PlayerY = Y */
{
	PlayerX(*M) = X;
	PlayerY(*M) = Y;
}


void InitMap(Map *M, char *filename)
/* I.S. Map M kosong dan siap diisi */
/* F.S. Map terinisialisasi */
{
	if (EndKata)
    {
		EndKata = false;
	}
	STARTKATA2(filename);
	int i = 0;

	while(!EndKata) {
		int j;
		for (j=0;j<CKata.Length;j++) {
			Info(*M,i,j) = CKata.TabKata[j];
		}
		ADVKATA();
		i++;
	}
}

/********** OPERASI **********/
void PrintMap(Map M)
/* I.S. M terdefinisi */
/* F.S. M ditampilkan pada layar */
{
    for (int i = BrsMin; i < BrsMax; i++)
    {
        for (int j = KolMin; j < KolMax; j++)
        {
            if (i == PlayerY(M) && j == PlayerX(M)) {
                printf("P");
            } else {
                printf("%c", Info(M, i, j));
            }
            if (j == KolMax-1)
            {
                printf("\n");
            }
        }
    }
    PrintLegend();
}

void PrintLegend()
/* Menampilkan Legenda Peta */
{
    printf("Legend:\n");
    printf("A = Antrian\n");
    printf("P = Player\n");
    printf("W = Wahana\n");
    printf("O = Office\n");
    printf("<, ^, >, V = Gerbang\n");
}

boolean IsBorder(Map M, int i, int j)
/* I.S. Matriks Terdefinisi */
/* F.S. Mengembalikan True jika Info[(i)][(j)] adalah border, border adalah bagian ujung (NBMin, NBMax, NKMin, NKMax) yang bukan gerbang */
{
  return (Info(M,i,j)=='*');
}

boolean IsSolid(Map M, int i, int j)
/* I.S. Matriks Terdefinisi */
/* F.S. Mengembalikan True jika Info[(i)][(j)] adalah solid, solid adalah wahana atau antrian 'W' atau 'A' */
{
  return ((Info(M,i,j)=='W') || (Info(M,i,j)=='A'));
}

boolean IsGerbang(Map M, int i, int j)
/* I.S. Matriks Terdefinisi */
/* F.S. Mengembalikan True jika Info[(i)][(j)] adalah gerbang */
{
  return (Info(M,i,j)=='V') || (Info(M,i,j)=='>') || (Info(M,i,j)=='^') || (Info(M,i,j)=='<');
}

boolean AvailInteraction(Map M, int i, int j)
/* I.S. baris dan kolom terdefinisi */
/* F.S. jika berada 1 petak di atas / bawah / kiri / kanan bangunan maka dapat berinteraksi */
{
    return ((Info(M,i-1,j)=='W'||Info(M,i-1,j)=='A'||Info(M,i-1,j)=='O') || 
			(Info(M,i+1,j)=='W'||Info(M,i+1,j)=='A'||Info(M,i+1,j)=='O') || 
			(Info(M,i,j-1)=='W'||Info(M,i,j-1)=='A'||Info(M,i,j-1)=='O') || 
			(Info(M,i,j+1)=='W'||Info(M,i,j+1)=='A'||Info(M,i,j+1)=='O'));
}


void Move(Map *M, char move, boolean *pindah)
/* I.S. Matriks terdefinisi & tidak kosong */
/* F.S. Player bergerak berdasarkan input, 
jika menabrak pagar Player tetap pada posisi awal, 
jika berada di atas office maka dapat berinteraksi dengan office */
{
    int i = PlayerY(*M);
    int j = PlayerX(*M);
    switch (move)
    {
    case 'w':
        if (!IsBorder(*M,i-1,j) && !IsSolid(*M,i-1,j) && !IsGerbang(*M,i-1,j))
        {
			InitPlayer(M, j, i-1));
        }
        else if (IsGerbang(*M,i-1,j))
        {
            *pindah = true;
        }
        
        break;
    case 'a':
        if (!IsBorder(*M,i,j-1) && !IsSolid(*M,i,j-1) && !IsGerbang(*M,i,j-1))
        {
			InitPlayer(M, j-1, i);
        }
        else if (IsGerbang(*M,i,j-1))
        {
            *pindah = true;
        }
        
        break;
    case 's':
        if (!IsBorder(*M,i+1,j) && !IsSolid(*M,i+1,j) && !IsGerbang(*M,i+1,j))
        {
            InitPlayer(M, j, i+1);
        }
        else if (IsGerbang(*M,i+1,j))
        {
            *pindah = true;
        }
        
        break;
    case 'd':
        if (!IsBorder(*M,i,j+1) && !IsSolid(*M,i,j+1) && !IsGerbang(*M,i,j+1))
        {
            InitPlayer(M, j+1, i);
        }
        else if (IsGerbang(*M,i,j+1))
        {
            *pindah = true;
        }

        break;
    default:
        break;
    }
}

void MakeListMap(ListMap *ListM, Map M1, Map M2, Map M3, Map M4)
/* I.S. ListMap sembarang */
/* F.S. ListMap[0] berisi M1 ... hingga ListMap[3] berisi M4 */
{
    MapN(*ListM, 1) = M1;
    MapN(*ListM, 2) = M2;
    MapN(*ListM, 3) = M3;
    MapN(*ListM, 4) = M4;
}