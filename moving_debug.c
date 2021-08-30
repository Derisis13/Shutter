//
// Created by lacko on 19/08/2021.
//

#include "moving_debug.h"
#include <stdio.h>

void set_ch (shutter *r, byte *channel)
{
  while (*channel != r->ch)
    {
      if (*channel > r->ch)
        {
          press_button (prev);
          (*channel)--;
        }
      else if (*channel < r->ch)
        {
          press_button (next);
          (*channel)++;
        }
    }
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

void lower (shutter *r)
{
  press_button (down);
  printf ("sleeping %d usecs", r->percentage * r->rolltime_down * 10000);
  press_button (stop);
}