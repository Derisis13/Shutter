/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file is part of Shutter.
 *
 * Shutter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shutter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shutter.  If not, see <https://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
#endif //_MOZGATAS_H_
