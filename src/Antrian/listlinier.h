/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addrList dengan pointer */
/* infotypeL adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"

#define NilN NULL

typedef int infotypeL;
typedef struct tElmtlist *addrList;
typedef struct tElmtlist { 
	infotypeL infoL;
	addrList nextL;
} ElmtList;
typedef struct {
	addrList FirstL;
} List;

/* Definisi list : */
/* List kosong : FirstL(L) = Nil */
/* Setiap elemen dengan addrList P dapat diacu InfoL(P), NextL(P) */
/* Elemen terakhir list : jika addrListnya Last, maka NextL(Last)=Nil */
#define InfoL(P) (P)->infoL
#define NextL(P) (P)->nextL
#define FirstL(L) ((L).FirstL)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsLEmpty (List L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateLEmpty (List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addrList AlokasiL (infotypeL X);
/* Mengirimkan addrList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrList tidak nil, dan misalnya */
/* menghasilkan P, maka InfoL(P)=X, NextL(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiL (addrList *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrList P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addrList SearchL (List L, infotypeL X);
/* Mencari apakah ada elemen list dengan InfoL(P)= X */
/* Jika ada, mengirimkan addrList elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
boolean FSearchL (List L, addrList P);
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
addrList SearchLPrec (List L, infotypeL X);
/* Mengirimkan addrList elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan InfoL(P)=X */
/* Jika ada, mengirimkan addrList Prec, dengan NextL(Prec)=P dan InfoL(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstL (List *L, infotypeL X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastL (List *L, infotypeL X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstL (List *L, infotypeL *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLastL (List *L, infotypeL *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstL (List *L, addrList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addrList P sebagai elemen pertama */
void InsertAfter (List *L, addrList P, addrList Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastL (List *L, addrList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstL (List *L, addrList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (List *L, infotypeL X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddrList P, dengan InfoL(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan InfoL(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLastL (List *L, addrList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (List *L, addrList *Pdel, addrList Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus NextL(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmtL (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotypeL Max (List L);
/* Mengirimkan nilai InfoL(P) yang maksimum */
addrList AdrMax (List L);
/* Mengirimkan addrList P, dengan InfoL(P) yang bernilai maksimum */
infotypeL Min (List L);
/* Mengirimkan nilai InfoL(P) yang minimum */
addrList AdrMin (List L);
/* Mengirimkan addrList P, dengan InfoL(P) yang bernilai minimum */
float Average (List L);
/* Mengirimkan nilai rata-rata InfoL(P) */

/****************** PROSES TERHADAP LIST ******************/
void DelAll (List *L);
/* Delete semua elemen list dan alamat elemen di-dealokasi */

void InversList (List *L);
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */

List FInversList (List L);
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */

void CopyList (List *L1, List *L2);
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */

List FCopyList (List L);
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */

void CpAlokList (List Lin, List *Lout);
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */

void Konkat (List L1, List L2, List * L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */

void Konkat1 (List *L1, List *L2, List *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

void PecahList (List *L1, List *L2, List L);
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */

#endif