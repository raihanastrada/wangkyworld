#ifndef PREPARATION_H

#include "../map.h"
#include "../Array/array.h"
#include "../Wahana/arrayWahana.h"
#include "../Wahana/arrayWMap.h"
#include "../Wahana/stackWMap.h"
#include "../MesinKata/mesinkata.h"
#include "../Antrian/antrian.h"
#include "../Antrian/listlinier.h"
#include "cmdstack.h"
#include "../Jam/jam.h"

void PrintPreviewMap(Map M, ListWMap WMap, StackWMap WBuild, int NMap);
/* Menampilkan peta pada kondisi preparation phase */

/* ************ Menjalankan Command pada CmdStack ************ */
void ExecuteCommand (CmdStack *S, ListLin *WahanaP, int *uang, int *s_aksi, int *s_waktu, int *s_uang, JAM *time_curr, ListWMap *WMap, StackWMap *WBuild, ListMap *ListM, List *ListMat);
/* menjalankan command-command yang ada di CmdStack S */
/* I.S. S mungkin kosong */
/* F.S. melakukan build/upgrade/buy sesuai command yang ada di stack, lalu mulai main phase */

void Buy(List L, List LC, char *Nama, int Quantity, int Uang, int *s_uang, int time_remain, int *s_waktu, int *s_aksi, CmdStack *S);
/* I.S. Parameter Fungsi Terdefinisi */
/* F.S. Uang berkurang sebanyak (harga barang)*(quantity), jika uang tidak cukup maka akan ditampilkan pesan error
        & proses tidak dijalankan */

void Build(ListW KamusWahana, List LC, int NMap, char *WName, ListMap *M, List *MatPemain, ListWMap *WMap, StackWMap *WBuild, int *s_waktu, int *s_aksi, CmdStack *S);

void UndoBuild(ListW KamusWahana, List LC, List *MatPemain, StackWMap *WBuild, int *s_waktu, int *s_aksi, CmdStack *S);

void UndoBuy(List LM, List LC, int *s_waktu, int *s_aksi, int*s_uang, CmdStack *S);

#endif