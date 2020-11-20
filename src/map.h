#ifndef MAP_H
#define MAP_H

#include "matriks.h"

typedef struct Map
{
    
};

void CreateMap(int NB, int NK, Map *M);
/* I.S. NB dan NK terdefinisi dan bernilai valid (NB & NK > 0) */
/* F.S. Terbentuk Map M dengan panjang baris NB dan panjang kolom NK */

void InitMap(Map *M);
/* I.S. Map M kosong dan diisi */
/* F.S. Map terinisialisasi */

void PrintMap(Map M);
/* I.S. M terdefinisi */
/* F.S. M ditampilkan pada layar */

#endif