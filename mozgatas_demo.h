//
// Created by lacko on 19/08/2021.
//

#ifndef _MOZGATAS_DEMO_H_
#define _MOZGATAS_DEMO_H_
#include "redony.h"

//beállítja a távirányítón a kívánt redőny csatornáját
void set_ch (redony *r);

//megnyomja a kívánt gombot
void press_button (buttons b);

//exportálja a használt GPIO-kat
void export ();

//reseteli a távirányítót, hogy a 0-ás csatornáról kezdjünk
void reset ();

#endif //_MOZGATAS_DEMO_H_
