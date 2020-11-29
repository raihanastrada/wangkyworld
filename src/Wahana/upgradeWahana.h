/* ADT Tree */
#ifndef _UPGRADEWAHANA_H_
#define _UPGRADEWAHANA_H_

/* Modul lain yang digunakan : */
#include "arrayWahana.h"

/* *** Definisi Type Pohon Upgrade *** */

typedef struct tNode *addrNode;
typedef struct tNode
{
  int id;
  addrNode left;
  addrNode right;
} Node;

/* Definisi Pohon Upgrade : */
/* Pohon Upgrade kosong : P = Nil */
typedef addrNode UpgradeTree;

/* *** Selektor *** */
#define Akar(P) (P)->id
#define Left(P) (P)->left
#define Right(P) (P)->right

/* *** Konstruktor *** */
UpgradeTree Tree(int Akar, UpgradeTree L, UpgradeTree R);
/* Menghasilkan sebuah pohon upgrade dari A, L, dan R */
void MakeTree(int Akar, UpgradeTree L, UpgradeTree R, UpgradeTree *P);
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R */
void BuildUpgradeTree(ListW Wahana, UpgradeTree *P);
/* I.S ListW tidak kosong */
/* F.S Membuat pohon upgrade dari list wahana */

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(UpgradeTree P);
/* Mengirimkan true jika P adalah pohon upgrade kosong */
boolean IsTreeOneElmt(UpgradeTree P);
/* Mengirimkan true jika P adalah pohon upgrade tidak kosong dan hanya memiliki 1 elemen */
boolean IsUnerLeft(UpgradeTree P);
/* Mengirimkan true jika pohon upgrade tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerRight(UpgradeTree P);
/* Mengirimkan true jika pohon upgrade tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsBiner(UpgradeTree P);
/* Mengirimkan true jika pohon upgrade tidak kosong P adalah pohon upgrade: mempunyai subpohon kiri dan subpohon kanan*/

/* *** Traversal *** */
void PrintTree(UpgradeTree P, int h);
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/

/* *** Searching *** */
boolean SearchTree(UpgradeTree P, int id);
/* Mengirimkan true jika ada node dari P yang bernilai W */

/* *** Operasi lain *** */
void AddDaunTerkiri(UpgradeTree *P, int W);
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan W sebagai simpul daun terkiri */

#endif