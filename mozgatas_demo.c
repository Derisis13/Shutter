//
// Created by lacko on 19/08/2021.
//

#include "mozgatas_demo.h"
#include <stdio.h>

void set_ch (shutter *r)
{
  reset ();
  for (int i = 1; i <= r->ch; ++i)
    printf ("ch. %d\n", i);
}

//reset láb active low, de negatív logikával van bekötve
void reset ()
{
  printf ("remote reset\n");
}

void press_button (buttons b)
{
  switch (b)
    {
      case up: printf ("up\n");
      break;
      case down: printf ("down\n");
      break;
      case stop: printf ("stop\n");
      break;
      case prev: printf ("previous\n");
      break;
      case next: printf ("next ch\n");
      break;
      default: printf ("hiba\n");
    }
}