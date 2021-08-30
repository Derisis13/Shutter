//
// Created by lacko on 08/08/2021.
// Redőnyök mozgatásáért felelős függvényeket tartalmaz
//
#include "redony.h"
#ifndef _MOZGATAS_H_
#define _MOZGATAS_H_


//beállítja a távirányítón a kívánt redőny csatornáját
void set_ch (redony *r);

//megnyomja a kívánt gombot
void press_button (buttons b);

//exportálja a használt GPIO-kat
void export ();

//reseteli a távirányítót, hogy a 0-ás csatornáról kezdjünk
void reset ();


#endif //_MOZGATAS_H_
