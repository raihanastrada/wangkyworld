#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "boolean.h"

#define MARK '.'

/* Kamus Global */
extern char CC;
extern boolean EOP;

void START();
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama yang akan dibaca.Jika CC = MARK maka EOP bernilai true, membaca dari input keyboard */

void START2(char *string);
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama yang akan dibaca.Jika CC = MARK maka EOP bernilai true, membaca dari file eksternal */

void SCAN();
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama yang akan dibaca.Jika CC = MARK maka EOP bernilai true, untuk scan command */

void ADV();
/* I.S. CC != MARK */
/* F.S. CC adalah karakter selanjutnya dari CC yang lama */

void ADVSCAN();
/* I.S. CC != MARK jika SCAN pertama kali digunakan dan CC == MARK jika SCAN setelah awal */
/* F.S. CC adalah dua karakter selanjutnya dari CC yang lama, buat keperluan scan comannd */

#endif
