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
{
	PlayerX(*M) = X;
	PlayerY(*M) = Y;
}

void RetractPlayer(Map *M)
{
    Info(*M,PlayerX(*M),PlayerY(*M)) = '-';
}

void InitMap(Map *M, char *filename)
/* I.S. Map M kosong dan siap diisi */
/* F.S. Map terinisialisasi */
{
    /* Mengisi map berdasakan file txt */
    /* SEMENTARA */
    /*
	Info(*M,1,1) = 65;
    Info(*M,5,9) = 62;
    Info(*M,9,5) = 118;
	PlayerX(*M) = 5;
	PlayerY(*M) = 5;
	*/
    /* Info(*M,5,5) = 80; */
	if (EndKata)
    {
		EndKata = false;
	}
	STARTKATA2(filename);
	int i = 0;
    //PlayerX(*M) = toInt(CKata.TabKata)+1;
    //ADVKATA();
    //PlayerY(*M) = toInt(CKata.TabKata)+1;
    //ADVKATA();
	while(!EndKata) {
		int j;
		for (j=0;j<CKata.Length;j++) {
			Info(*M,i,j) = CKata.TabKata[j];
		}
		ADVKATA();
		i++;
	}
	/*
    Mengisi bagian yang masih kosong atau belum termasuk dalam konfigurasi awal
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
    }*/
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
	RetractPlayer(M);
    switch (move)
    {
    case 'w':
		if (IsBorder(*M,i-1,j)) /*InitPlayer(M, PlayerX(*M), PlayerY(*M))*/;
        else if (!IsBorder(*M,i-1,j) && !IsGerbang(*M,i-1,j))
        {
            PlayerY(*M) = i-1;
	        PlayerX(*M) = j;
			//InitPlayer(M, PlayerX(*M), PlayerY(*M));
        }
        else if (IsGerbang(*M,i-1,j))
        {
            *pindah = true;
        }
        
        break;
    case 'a':
		if (IsBorder(*M,i,j-1)) /*InitPlayer(M, PlayerX(*M), PlayerY(*M))*/;
        else if (!IsBorder(*M,i,j-1) && !IsGerbang(*M,i,j-1))
        {
            PlayerY(*M) = i;
	        PlayerX(*M) = j-1;
			//InitPlayer(M, PlayerX(*M), PlayerY(*M));
        }
        else if (IsGerbang(*M,i,j-1))
        {
            *pindah = true;
        }
        
        break;
    case 's':
		if (IsBorder(*M,i+1,j)) /*InitPlayer(M, PlayerX(*M), PlayerY(*M))*/;
        else if (!IsBorder(*M,i+1,j) && !IsGerbang(*M,i+1,j))
        {
            PlayerY(*M) = i+1;
	        PlayerX(*M) = j;
			//InitPlayer(M, PlayerX(*M), PlayerY(*M));
        }
        else if (IsGerbang(*M,i+1,j))
        {
            *pindah = true;
        }
        
        break;
    case 'd':
		if (IsBorder(*M,i,j+1)) /*InitPlayer(M, PlayerX(*M), PlayerY(*M))*/;
        else if (!IsBorder(*M,i,j+1) && !IsGerbang(*M,i,j+1))
        {
            PlayerY(*M) = i;
	        PlayerX(*M) = j+1;
			//InitPlayer(M, PlayerX(*M), PlayerY(*M));
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

void Generate1(Map M, Map *Mnew)
{
	if (IDM(M)==4) {
		InitPlayer(Mnew,5,10);
	}
	else {
		InitPlayer(Mnew,10,5);
	}
}

void Generate2(Map M, Map *Mnew)
{
	if (IDM(M)==3) {
		InitPlayer(Mnew,5,10);
	}
	else {
		InitPlayer(Mnew,1,5);
	}	
}

void Generate3(Map M, Map *Mnew)
{
	if (IDM(M)==2) {
		InitPlayer(Mnew,5,1);
	}
	else {
		InitPlayer(Mnew,1,5);
	}	
}

void Generate4(Map M, Map *Mnew)
{
	if (IDM(M)==1) {
		InitPlayer(Mnew,5,1);
	}
	else {
		InitPlayer(Mnew,10,5);
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