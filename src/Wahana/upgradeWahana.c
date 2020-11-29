#include "upgradeWahana.h"
#include "arrayWahana.h"
#include "../array/boolean.h"
#include <stdio.h>
#include <stdlib.h>

#define Nil NULL

/* Manajemen Memory */
addrNode AlokNode(int X)
{
  addrNode P = (addrNode)malloc(sizeof(Node));
  if (P != Nil)
  {
    Akar(P) = X;
    Left(P) = Nil;
    Right(P) = Nil;
  }
  return P;
}
void DealokNode(addrNode P)
{
  free(P);
}

/* *** Konstruktor *** */
UpgradeTree Tree(int Akar, UpgradeTree L, UpgradeTree R)
/* Menghasilkan sebuah pohon upgrade dari A, L, dan R */
{
    addrNode P = AlokNode(Akar);
    if (P != Nil)
    {
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}
void MakeTree(int Akar, UpgradeTree L, UpgradeTree R, UpgradeTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R */
{
    (*P) = Tree(Akar,L,R);
}

void BuildUpgradeTree(ListW LW, UpgradeTree *P)
/* I.S ListW tidak kosong */
/* F.S Membuat pohon upgrade dari list wahana */
{
  int i = 0;
  *P = Tree(Level(LW,i),Nil,Nil);
  while ( Level(LW,i) != ValUndef && i <= IdxMax)
  {
    if (Level(LW,i) == 2)
    {
      if (IsTreeOneElmt(*P))
      {
        AddDaun(P,1,ID(LW,i),true);
      }
      else
      {
        if (Right(*P) == Nil)
        {
          Right(*P) = AlokNode(ID(LW,i));
        }        
      }
    }
    i++;
  }

  i = 0;
  while ( Level(LW,i) != ValUndef && i <= IdxMax)
  {
    if (Level(LW,i) == 3)
    {
      if (IsTreeOneElmt(Left(*P)) && IsTreeOneElmt(Right(*P)))
      {
        Left(Left(*P)) = AlokNode(ID(LW,i));
        Left(Right(*P)) = AlokNode(ID(LW,i));
      }
      else
      {
        Right(Left(*P)) = AlokNode(ID(LW,i));
        Right(Right(*P)) = AlokNode(ID(LW,i));
      }
    }
    i++;
  }
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(UpgradeTree P)
{
  return (P == Nil);
}
boolean IsTreeOneElmt(UpgradeTree P)
{
  return (!IsTreeEmpty(P) && Left(P) == Nil && Right(P) == Nil);
}
boolean IsUnerLeft(UpgradeTree P)
{
  return (Left(P) != Nil && Right(P) == Nil);
}
boolean IsUnerRight(UpgradeTree P)
{
  return (Right(P) != Nil && Left(P) == Nil);
}
boolean IsBiner(UpgradeTree P)
{
  return (Right(P) != Nil && Left(P) != Nil);
}

void PrintTreeLev(UpgradeTree P, int h, int level)
{
  if (!IsTreeEmpty(P))
  {
    for (int i = 0; i < h*level; i++)
    {
      printf(" ");
    }
        
    printf("%d\n",Akar(P));
    PrintTreeLev(Left(P), h, level+1);
    PrintTreeLev(Right(P), h, level+1);
  }
}
/* *** Traversal *** */
void PrintTree(UpgradeTree P, int h)
{   
    PrintTreeLev(P,h,0);
}
/* *** Searching *** */
boolean SearchTree(UpgradeTree P, int id)
/* Mengirimkan true jika ada node dari P yang bernilai W */
{
  if (IsTreeEmpty(P))
  {
    return false;
  }
  else
  {
    if(Akar(P) == id)
    {
      return true;
    }
    else
    {
      return SearchTree(Left(P),id) || SearchTree(Right(P),id);
    }
  }
}

/* *** Fungsi-fungsi lain *** */
boolean IsSkewLeft(UpgradeTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
  if (IsTreeEmpty(P))
  {
    return true;
  }
  else
  {
    if(Right(P)!=Nil)
    {
      return false;
    }
    else
    {
      return IsSkewLeft(Left(P));
    }
  }
}
boolean IsSkewRight(UpgradeTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
  if (IsTreeEmpty(P))
  {
    return true;
  }
  else
  {
    if(Left(P)!=Nil)
    {
      return false;
    }
    else
    {
      return IsSkewRight(Right(P));
    }
  }
}

/* *** Operasi lain *** */
void AddDaun(UpgradeTree *P, int X, int Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Upgrade P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
{
  if (!IsTreeEmpty(*P))
  {
    if (Akar(*P) == X && IsTreeOneElmt(*P))
    {
      if (Kiri)
      {
        Left(*P) = Tree(Y,Nil,Nil);
      }
      else
      {
        Right(*P) = Tree(Y,Nil,Nil);
      }
    }
    else
    {
      if (SearchTree(Left(*P), X))
      {
        AddDaun(&Left(*P),X,Y,Kiri);
      }
      else if (SearchTree(Right(*P), X))
      {
        AddDaun(&Right(*P),X,Y,Kiri);
      }
    }
  }
}