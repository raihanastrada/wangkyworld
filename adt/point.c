#include <stdio.h>
#include "point.h"
#include <math.h>
#include "boolean.h"
#define PI 3.14159265358979323846

/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (float X, float Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;
	return P;
}

void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
{
	float X,Y;
	scanf("%f %f", &X, &Y);
	*P = MakePOINT(X,Y);
}

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
{
	printf("(%.2f,%.2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == (Ordinat(P2))));
}
boolean NEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
	return ((Absis(P1) != Absis(P2)) || (Ordinat(P1) != (Ordinat(P2))));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
	return ((Absis(P)==0) && (Ordinat(P)==0));
}
boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
	return (Ordinat(P) == 0);
}
boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
	return (Absis(P) == 0);
}
int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
/* Menurut file check_point, jika prekondisi tidak dipenuhi maka akan mengeluarkan -1 */
{
	if (IsOrigin(P) || IsOnSbX(P) || IsOnSbY(P))
	{
		return -1;
	}
	else
	{
		if (Absis(P)>0)
		{
			if (Ordinat(P)>0)
			{
				return 1;
			}
			else
			{
				return 4;
			}
		}
		else
		{
			if (Ordinat(P)>0)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
}


/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */
{
	return MakePOINT(Absis(P)+1, Ordinat(P));
}
POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	return MakePOINT(Absis(P), Ordinat(P)+1);
}
POINT PlusDelta (POINT P, float deltaX, float deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	return MakePOINT(Absis(P)+deltaX , Ordinat(P)+deltaY);
}
POINT MirrorOf (POINT P, boolean SbX)
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
{
	if (SbX == true)
	{
		return MakePOINT(Absis(P), Ordinat(P)*-1);
	}
	else
	{
		return MakePOINT(Absis(P)*-1, Ordinat(P));
	}
}

float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
	return (sqrt(pow(Absis(P),2)+pow(Ordinat(P),2)));
}
float Panjang (POINT P1, POINT P2)
/* Menghitung jarak antara P1 dan P2 */
{
	return (sqrt(pow((Absis(P1)-Absis(P2)),2)+pow((Ordinat(P1)-Ordinat(P2)),2)));
}

void Geser (POINT *P, float deltaX, float deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	Absis(*P) = Absis(*P)+deltaX; 
	Ordinat(*P) = Ordinat(*P)+deltaY;
}

void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
	Ordinat(*P) = 0;
}
void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
	Absis(*P) = 0;
}
void Mirror (POINT *P, boolean SbX)
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
{
	if (SbX == true)
	{
		Ordinat(*P) = Ordinat(*P)*-1;
	}
	else
	{
		Absis(*P) = Absis(*P)*-1;
	}
}
void Putar (POINT *P, float Sudut)
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) searah jarum jam*/
{
	double Sudut1 = Sudut * (PI / 180.0);
	double xrot, yrot;
	xrot = (Absis(*P)*cos(Sudut1)) + (Ordinat(*P)*sin(Sudut1));
	yrot = (Ordinat(*P)*cos(Sudut1) - Absis(*P)*sin(Sudut1));
	Absis(*P) = xrot;
	Ordinat(*P) = yrot;
}
	
