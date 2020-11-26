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

void ADV();
/* I.S. CC != MARK */
/* F.S. : CC adalah karakter selanjutnya dari CC yang lama */

#endif
