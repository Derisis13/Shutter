//
// Created by lacko on 08/08/2021.
// Redőnyök mozgatásáért felelős függvényeket tartalmaz
//
#include "shutter.h"
#ifndef _MOZGATAS_H_
#define _MOZGATAS_H_

//set to the desired ch on the remote
void set_ch (shutter *r, byte *ch);

//activates the gpio given to it and thus "presses" the button
void press_button (buttons b);

//resets the remote so we start from ch 1
void reset ();

//lowers the shutter to the percentage level described in the shutter structure
void lower (shutter *r);
#endif _MOZGATAS_H_
