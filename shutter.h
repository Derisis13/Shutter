//
// Created by lacko on 08/08/2021.
//

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
