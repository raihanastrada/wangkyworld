/* office.h */

#ifndef OFFICE_H
#define OFFICE_H

#include "../Wahana/arrayWahana.h"
#include "../Antrian/listlinier.h"
#include "../MesinKata/mesinkar.h"
#include "../MesinKata/mesinkata.h"
#include "boolean.h"

void InitOffice(ListW LW, ListLin WahanaP);
/* Menu Office */

void InitDetails(ListW LW, ListLin WahanaP);
/* Menu Details */

void InitReport(ListW LW, ListLin WahanaP);
/* Menu Report */

#endif

	