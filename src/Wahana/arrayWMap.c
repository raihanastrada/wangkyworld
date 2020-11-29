/* File ListWMap of Wahana */
/* arrayWMap.h */

#include <stdio.h>
#include "../Array/boolean.h"
#include "../Array/array.h"
#include "point.h"
#include "stackWMap.h"
#include "arrayWMap.h"

void CreateLWMEmpty(ListWMap *WMap)
/* I.S. ListWMap sembarang */
/* F.S. Length = 0 */
{
    int i;
    for (i = 0; i < IdxMaxW; i++) {
        IDW(WMItem(*WMap, i)) = ValUndefW;
        Loc(WMItem(*WMap, i)) = MakePOINT(ValUndefW, ValUndefW);
        Quadrant(WMItem(*WMap, i)) = ValUndefW;
    }
    LenWM(*WMap) = 0;
}

boolean IsLWMEmpty(ListWMap WMap)
/* Mengembalikan true jika WMap kosong */
{
    return (LenWM(WMap) == 0);
}

boolean IsLWMFull(ListWMap WMap)
/* Mengembalikan true jika WMap penuh */
{
    return (LenWM(WMap) == IdxMaxW+1);
}

boolean SearchLWM(ListWMap WMap, int ID, POINT Pos, int NMap)
/* Mengembalikan true jika ada WMapItem dalam WMap dengan IDW, Pos, NMap */
{
    int i;
    WMapItemCopy Wahana;
    for (i = 0; i < LenWM(WMap); i++) {
        Wahana = WMItem(WMap, i);
        if (IDW(Wahana) == ID && EQ(Loc(Wahana),Pos) && Quadrant(Wahana) == NMap) {
            return true;
        }
    }
    return false;
}

boolean SearchWMap(ListWMap WMap, int posy, int posx, int NMap)
{
    int i;
    for (i = 0; i < LenWM(WMap); i++) {
        if (Absis(Loc(WMItem(WMap, i))) == posx && Ordinat(Loc(WMItem(WMap, i))) == posy && Quadrant(WMItem(WMap, i)) == NMap) {
            return true;
        }
    }
    return false;
}

void PushLWM(ListWMap *WMap, int ID, POINT Pos, int NMap)
/* Menyimpan wahana item baru */
/* prekondisi: IsPosTaken() false */
{
    LenWM(*WMap)++;
    IDW(WMItem(*WMap, LenWM(*WMap))) = ID;
    Loc(WMItem(*WMap, LenWM(*WMap))) = Pos;
    Quadrant(WMItem(*WMap, LenWM(*WMap))) = NMap;
}

void DeleteLWM(ListWMap *WMap, int ID, POINT Pos, int NMap)
/* Menghapus wahana item dari ListWMap */
/* prekondisi: ada WMapItem dalam WMap dengan IDW, Pos, NMap */
{
    int i;
    boolean found = false;
    while (i < LenWM(*WMap)) {
        if (IDW(WMItem(*WMap, i)) == ID && EQ(Loc(WMItem(*WMap, i)),Pos) && Quadrant(WMItem(*WMap, i)) == NMap) {
            found = true;
            LenWM(*WMap)--;
        }

        if (found) {
            if (i == IdxMaxW-1) {
                IDW(WMItem(*WMap, i)) = ValUndefW;
                Loc(WMItem(*WMap, i)) = MakePOINT(ValUndefW, ValUndefW);
                Quadrant(WMItem(*WMap, i)) = ValUndefW;
            } else {
                IDW(WMItem(*WMap, i)) = IDW(WMItem(*WMap, i+1));
                Loc(WMItem(*WMap, i)) = Loc(WMItem(*WMap, i+1));
                Quadrant(WMItem(*WMap, i)) = Quadrant(WMItem(*WMap, i+1));
            }
        }
        i++;
    }
}