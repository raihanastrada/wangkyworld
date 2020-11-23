/* map.c */
/* Realisasi map.h */

#include "map.h"
#include <stdio.h>
#include <stdlib.h>


/********** KONSTRUKTOR **********/
void CreateMap(int NB, int NK, Map *M)
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
}

void InitMap(Map *M, char filename[])
/* I.S. Map M kosong dan siap diisi */
/* F.S. Map terinisialisasi */
{
    /* Mengisi map berdasakan file txt */
    /* SEMENTARA */
    Info(*M,1,1) = 65;
    Info(*M,5,9) = 62;
    Info(*M,9,5) = 118;
    Info(*M,5,5) = 80;

    /* Mengisi bagian yang masih kosong atau belum termasuk dalam konfigurasi awal */
    for (int i = BrsMin; i < BrsMax; i++)
    {
        for (int j = KolMin; j < KolMax; j++)
        {
            if (Info(*M, i, j) == Nil)
            {
                if (IsBorder(*M,i,j))
                {
                    Info(*M, i, j) = '*';
                }
                else
                {
                    Info(*M, i, j) = '-';    
                }    
            }
        }
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
            printf("%c", Info(M, i, j));
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
  return ((i == BrsMin) || (i == BrsMax-1) || (j == KolMin) || (j == KolMax-1)) && !IsGerbang(M,i,j);
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
    return (Info(M,i-1,j)=='W'||'A') || (Info(M,i+1,j)=='W'||'A') || (Info(M,i,j-1)=='W'||'A') || (Info(M,i,j+1)=='W'||'A');
}

void Move(Map *M, char move)
/* I.S. Matriks terdefinisi & tidak kosong */
/* F.S. Player bergerak berdasarkan input, 
jika menabrak pagar Player tetap pada posisi awal, 
jika berada di atas office maka dapat berinteraksi dengan office */
{
    int i = PlayerX(*M);
    int j = PlayerY(*M);

    switch (move)
    {
    case 'w':
        if (!IsBorder(*M,i-1,j))
        {
            PlayerX(*M) = i-1;
	        PlayerY(*M) = j;
        }
        else if (IsGerbang(*M,i-1,j))
        {
            /* code */
        }
        
        break;
    case 'a':
        if (!IsBorder(*M,i,j-1))
        {
            PlayerX(*M) = i;
	        PlayerY(*M) = j-1;
        }
        else if (IsGerbang(*M,i,j-1))
        {
            /* code */
        }
        
        break;
    case 's':
        if (!IsBorder(*M,i+1,j))
        {
            PlayerX(*M) = i+1;
	        PlayerY(*M) = j;
        }
        else if (IsGerbang(*M,i+1,j))
        {
            /* code */
        }
        
        break;
    case 'd':
        if (!IsBorder(*M,i,j+1))
        {
            PlayerX(*M) = i;
	        PlayerY(*M) = j+1;
        }
        else if (IsGerbang(*M,i,j+1))
        {
            /* code */
        }

        break;
    default:
        break;
    }
}

/*
int char_to_int(char c)
{
    int result;
    switch (c)
    {
    case '1':
        result = 1;
    case '2':
        result = 2;
    case '3':
        result = 3;
    case '4':
        result = 4;
    case '5':
        result = 5;
    case '6':
        result = 6;
    case '7':
        result = 7;
    case '8':
        result = 8;
    case '9':
        result = 9;
    default:
        result = 0;
    }
    return result;
}
*/