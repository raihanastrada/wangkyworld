#include <stdio.h>
#include "arraypos.h"
#include "boolean.h"
#include <math.h>


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */
{
	for (int i=IdxMin;i<=IdxMax;i++)
	{
		Elmt(*T,i) = ValUndef;
	}
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
	int count;
	count = 0;
	for (int i=IdxMin;i<=IdxMax;i++)
	{
		if(Elmt(T,i)!=ValUndef)
		{
			count++;
		}
	}
	return count;
}
/* *** Daya tampung container *** */
int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
	return (IdxMax+1);
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
	return IdxMin;
}
IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
	int last = IdxMax;
	while(Elmt(T,last)==ValUndef)
	{
		last--;
	}
	return last;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
	return ((IdxMin<=i)&&(i<=IdxMax));
}
boolean IsIdxEff (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
	return ((IdxMin<=i)&&(i<=GetLastIdx(T)));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

{
	return (Elmt(T,IdxMin)==ValUndef);
}

/* *** Test tabel penuh *** */
boolean IsFull (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
	return (Elmt(T,IdxMax)!=ValUndef);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
	int cek = 0;
	int N;
	MakeEmpty(T);
	while (cek==0)
	{
		scanf("%d",&N);
		if ((N>=IdxMin) && (N<=MaxNbEl(*T)))
		{
			cek++;
		}
	}
	if (N==IdxMin)
	{
		MakeEmpty(T);
	}
	else
	{
		for (int i=IdxMin;i<N;i++)
		{
			int isi;
			scanf("%d",&isi);
			Elmt(*T,i) = isi;
		}
	}
}
void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
	printf("[");
	if (IsEmpty(T))
	{
		printf("]");
	}
	else
	{
		for (int i=IdxMin;i<GetLastIdx(T);i++)
		{
			printf("%d,",Elmt(T,i));
		}
		printf("%d",Elmt(T,GetLastIdx(T)));
		printf("]");
	}
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusMinusTab (TabInt T1, TabInt T2, boolean plus)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
{
	TabInt T3;
	MakeEmpty(&T3);
	if(plus)
	{
		for (int i=IdxMin;i<=GetLastIdx(T1);i++)
		{			
			Elmt(T3,i) = (Elmt(T1, i) != ValUndef ? Elmt(T1, i) : 0)+(Elmt(T2, i) != ValUndef ? Elmt(T2, i) : 0);
		}
	}
	else
	{
		for (int i=IdxMin;i<=GetLastIdx(T1);i++)
		{
			Elmt(T3,i) = (Elmt(T1, i) != ValUndef ? Elmt(T1, i) : 0)-(Elmt(T2, i) != ValUndef ? Elmt(T2, i) : 0);
		}
	}
	return T3;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{
	int beda = 0;
	for (int i=IdxMin;i<=IdxMax;i++)
	{
		if(Elmt(T1,i)!=Elmt(T2,i))
		{
			beda++;
		}
	}
	return(beda==0);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
	int stop,loc;
	stop = 0;
	int i = IdxMin;
	while((i<=GetLastIdx(T)) && (stop==0))
	{
		if(Elmt(T,i)==X)
		{
			loc = i;
			stop++;
		}
		i++;
	}
	if(stop!=0)
	{
		return loc;
	}
	else
	{
		return IdxUndef;
	}
}
boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
	int stop = 0;
	int i = IdxMin;
	while((i<=IdxMax) && (stop==0))
	{
		if(Elmt(T,i)==X)
		{
			stop++;
		}
		i++;
	}
	return (stop!=0);
}

/* ********** NILAI EKSTREM ********** */
void MaxMin (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
	*Max = Elmt(T,0);
	*Min = Elmt(T,0);
	for(int i=IdxMin+1;i<=GetLastIdx(T);i++)
	{
		if(*Max<Elmt(T,i))
		{
			*Max = Elmt(T,i);
		}
		if(*Min>Elmt(T,i))
		{
			*Min = Elmt(T,i);
		}
	}
}

/* ********** OPERASI LAIN ********** */
ElType SumTab (TabInt T)
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
{
	if(IsEmpty(T))
	{
		return 0;
	}	
	else
	{
		int sum = 0;
		for(int i=IdxMin;i<=GetLastIdx(T);i++)
		{
			sum += Elmt(T,i);
		}
		return sum;
	}
}

int CountX (TabInt T, ElType X)
/* Menghasilkan berapa banyak kemunculan X di T */
/* Jika T kosong menghasilkan 0 */
{
	if (IsEmpty(T))
	{
		return 0;
	}
	else
	{
		int count = 0;
		for(int i=IdxMin;i<=GetLastIdx(T);i++)
		{
			if(Elmt(T,i)==X)
			{
				count++;
			}
		}
		return count;
	}
}

boolean IsAllGenap (TabInt T)
/* Menghasilkan true jika semua elemen T genap */
{
	int stop = 0;
	int i = IdxMin;
	while ((i<=GetLastIdx(T)) && (stop==0))
	{
		if(Elmt(T,i)%2==1)
		{
			stop++;
		}
		i++;
	}
	return (stop==0);
}

/* ********** SORTING ********** */
void Sort (TabInt * T, boolean asc)
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */
{
	if(asc)
	{
		for(int i=IdxMin+1;i<=GetLastIdx(*T);i++)
		{
			int min = Elmt(*T,i);
			int j = i-1;
			while(j>=0 && Elmt(*T,j) > min)
			{
				Elmt(*T,j+1) = Elmt(*T,j);
				j--;
			}
			Elmt(*T,j+1) = min;
		}
	}
	else
	{	
		for(int i=IdxMin+1;i<=GetLastIdx(*T);i++)
		{
			int max = Elmt(*T,i);
			int j = i-1;
			while(j>=0 && Elmt(*T,j) < max)
			{
				Elmt(*T,j+1) = Elmt(*T,j);
				j--;
			}
			Elmt(*T,j+1) = max;
		}	
	}
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
	if(IsEmpty(*T))
	{
		Elmt(*T,IdxMin) = X;
	}
	else
	{
		int i = GetLastIdx(*T)+1;
		Elmt(*T,i) = X;
	}
}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
	if(!IsEmpty(*T))
	{
		*X = Elmt(*T,GetLastIdx(*T));
		Elmt(*T,GetLastIdx(*T)) = ValUndef;
	}
}