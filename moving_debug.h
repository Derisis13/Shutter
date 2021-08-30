//
// Created by lacko on 19/08/2021.
//

#ifndef _MOVING_DEBUG_H_
#define _MOVING_DEBUG_H_
#include "shutter.h"

//set to the desired channel on the remote
void set_ch (shutter *r, byte *channel);

//activates the gpio given to it and thus "presses" the button
void press_button (buttons b);

//resets the remote so we start from ch 1
void reset ();

//lowers the shutter to the percentage level described in the shutter structure
void lower (shutter *r);

#endif //_MOVING_DEBUG_H_
