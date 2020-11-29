/* File: jam.c */
/* Definisi ADT JAM */

#include "jam.h"
#include "boolean.h"
#include <math.h>
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
	return (((0<=H)&&(H<24)) && ((0<=M)&&(M<60)) && ((0<=S)&&(S<60)));
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
    JAM J;
	Hour(J) = HH;
	Minute(J) = MM;
	Second(J) = SS;
	return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
{
	int HH, MM, SS, i;
	i = 0;
	while (i==0)
	{
		scanf("%d %d %d",&HH,&MM,&SS);
		if (IsJAMValid(HH,MM,SS))
		{
			*J = MakeJAM(HH,MM,SS);
			i++;
		}
		else
		{
			printf("Jam tidak valid\n");
		}
	}
}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH.MM */
{
	if (Hour(J) < 10)
	{	
		printf("0%d.",Hour(J));
	}
	else
	{
		printf("%d.",Hour(J));
	}
	
	if (Minute(J) < 10)
	{	
		printf("0%d",Minute(J));
	}
	else
	{
		printf("%d",Minute(J));
	}
}

void TulisDurasi (JAM J)
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH hour(s), MM minute(s) */
/*        Jika jam = 0, hanya ditulis menit
          Jika jam atau menit hanya 1 maka tidak ditulis '(s)' */
{
    if (Hour(J) != 0)
    {
        if (Hour(J) == 1)
        {
            printf("%d hour ", Hour(J));
        }
        else
        {
            printf("%d hour(s) ", Hour(J));
        }
    }

    if (Minute(J) != 0)
	{
        if (Minute(J) == 1)
        {
            printf("%d minute ", Minute(J));
        }
        else
        {
            printf("%d minute(s) ", Minute(J));
        }
    }
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
{
    return ((Hour(J)*3600) + (Minute(J)*60) + Second(J));
}

JAM DetikToJAM (long N)
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */
{
	N = N%86400;
	JAM J;
	Hour(J) = N/3600;
	Minute(J) = (N%3600)/60;
	Second(J) = N%60;
	return J;
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
	return(JAMToDetik(J1)==JAMToDetik(J2));
}
boolean JGT (JAM J1, JAM J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
	return(JAMToDetik(J1)>JAMToDetik(J2));
}
boolean JinRange(JAM JAw, JAM JAkh, JAM J)
/* Mengirimkan true jika JAw <= J <= JAkh , false jika tidak */
{
	return JGT(J,JAw) && JGT(JAkh,J);
}

/* *** Kelompok Operator Aritmetika *** */
JAM Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
	if (JAMToDetik(JAw) > JAMToDetik(JAkh))
	{
		return DetikToJAM(86400+(JAMToDetik(JAkh)-JAMToDetik(JAw)));
	}
	else
	{
		return DetikToJAM(JAMToDetik(JAkh)-JAMToDetik(JAw));
	}
}

JAM AddJam (int J1, int J2)
/* Mengirim J1+J2 (dlm Detik) menjadi Jam, dengan kalkulasi */
{
    return DetikToJAM(J1+J2);
}