//
// Created by lacko on 08/08/2021.
//

#ifndef _REDONY_H_
#define _REDONY_H_

#include <time.h>

typedef char byte;

typedef struct ido {
  byte tm_hour;
  byte tm_min;
} ido;

typedef struct redony {
  byte ch;
  ido up;
  ido down;
  byte rolltime_up;     //measured in seconds
  byte rolltime_down;   //measured in seconds
  byte percentage;
} redony;

typedef enum buttons {
  up = 17,
  stop,
  down,
  prev,
  next
} buttons;
#endif //_REDONY_H_
