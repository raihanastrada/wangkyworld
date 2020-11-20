#include <stdio.h>
#include "jam.h"
#include "boolean.h"
#include <math.h>

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
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
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
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.
   Jika jam / menit / detik hanya satu digit, tuliskan satu digit tanpa 0 di depannya. */
{
	printf("%d:%d:%d",Hour(J),Minute(J),Second(J));
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
boolean JNEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
	return(JAMToDetik(J1)!=JAMToDetik(J2));
}
boolean JLT (JAM J1, JAM J2)
/* Mengirimkan true jika J1<J2, false jika tidak */
{
	return(JAMToDetik(J1)<JAMToDetik(J2));
}
boolean JGT (JAM J1, JAM J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
	return(JAMToDetik(J1)>JAMToDetik(J2));
}

/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J)
/* Mengirim 1 detik setelah J dalam bentuk JAM */
{
	long tempdetik;
	tempdetik = JAMToDetik(J) + 1;
	if (JAMToDetik(J)>86399)
	{
		tempdetik = tempdetik%86400;
		return DetikToJAM(tempdetik);
	}
	else
	{
		return DetikToJAM(tempdetik);
	}
}

JAM NextNDetik (JAM J, int N)
/* Mengirim N detik setelah J dalam bentuk JAM */
{
	long tempdetik;
	tempdetik = JAMToDetik(J) + N;
	if (JAMToDetik(J)>86399)
	{
		tempdetik = tempdetik%86400;
		return DetikToJAM(tempdetik);
	}
	else
	{
		return DetikToJAM(tempdetik);
	}
}

JAM PrevDetik (JAM J)
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
{
	long tempdetik;
	tempdetik = JAMToDetik(J) - 1;
	if (tempdetik<0)
	{
		tempdetik = 86400+tempdetik;
		return DetikToJAM(tempdetik);
	}
	else
	{
		return DetikToJAM(tempdetik);
	}
}
	
JAM PrevNDetik (JAM J, int N)
/* Mengirim N detik sebelum J dalam bentuk JAM */
{
	long tempdetik;
	tempdetik = JAMToDetik(J) - N;
	if(tempdetik<0)
	{
		tempdetik = 86400+tempdetik;
		return DetikToJAM(tempdetik);
	}
	else
	{
		return DetikToJAM(tempdetik);
	}
}

/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
	if (JAMToDetik(JAw) > JAMToDetik(JAkh))
	{
		return (86400+(JAMToDetik(JAkh)-JAMToDetik(JAw)));
	}
	else
	{
		return (JAMToDetik(JAkh)-JAMToDetik(JAw));
	}
}
