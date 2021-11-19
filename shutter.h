/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file is part of Shutter.
 *
 * Shutter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Shutter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shutter.  If not, see <https://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _SHUTTER_H_
#define _SHUTTER_H_

typedef char byte;

typedef struct minitime {
  byte tm_hour;
  byte tm_min;
} minitime;

typedef struct shutter {
  byte ch;                //assigned channel on the connected remote
  minitime up;            //time of raise
  minitime down;          //time of lowering
  byte rolltime_down;     //measured in seconds, measured when the shutter is rolling down (usually faster than rolling up)
  byte percentage;        //the percentage to which the shutter is to be lowered
  struct shutter *next;
} shutter;

typedef enum buttons {
  up = 17,      //I'm lucky, I found 5 consecutively numbered gpios, starting with gpio 17
  stop,
  down,
  prev,
  next
} buttons;

shutter * create_shutter (byte ch, byte rolltime_down);
void append_shutter (shutter **head, shutter *new_shutter);
void free_shutters (shutter * head);
#endif //_SHUTTER_H_
