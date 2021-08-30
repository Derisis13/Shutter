//
// Created by lacko on 08/08/2021.
//

#ifndef _REDONY_H_
#define _REDONY_H_

#include <time.h>


typedef struct ido {
  int tm_hour;
  int tm_min;
} ido;

typedef struct redony {
  int ch;
  ido up;
  ido down;
} redony;

typedef enum buttons {
  up = 17,
  stop,
  down,
  prev,
  next
} buttons;
#endif //_REDONY_H_
