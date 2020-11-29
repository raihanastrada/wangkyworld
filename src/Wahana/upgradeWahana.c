#include "upgradeWahana.h"
#include "arrayWahana.h"
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
    /*int i = 0;
    while ( Level(LW,i) != ValUndef && i <= IdxMax)
    {
        if (IsUnerLeft(P))
        {
           P = Tree(Akar(*P),AlokNode(ID(LW,i)),Right(*P));  
        }
        else if (IsTreeEmpty(P))
        {
            P = Tree(ID(LW,i),Nil,Nil);
        }
        else
        {
           P = Tree(Akar(*P),Left(*P),AlokNode(ID(LW,i))); 
        }
        i++;
    }
    
    return P; */
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

/* *** Operasi lain *** */
void AddDaunTerkiri(UpgradeTree *P, int id)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan W sebagai simpul daun terkiri */
{
  if (IsTreeEmpty(*P))
  {  
    *P = Tree(id,Nil,Nil);
  }
  else
  {
    AddDaunTerkiri(&Left(*P),id);
  }
}