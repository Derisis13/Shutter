//
// Created by lacko on 08/08/2021.
//

#include "moving.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //project is to be compiled to openwrt

void set_ch (shutter *r, byte *ch)
{
  while (*ch != r->ch)
    {
      if (*ch > r->ch)
        {
          press_button (prev);
          *ch--;
        }
      else if (*ch < r->ch)
        {
          press_button (next);
          *ch++;
        }
    }
}

//doing negative logic as reset is active low and GPIO2 is 1 on startup
void reset ()
{
  FILE *gpio2 = fopen ("/sys/class/gpio/gpio2/value", "w");
  fprintf (gpio2, "0");
  fclose (gpio2);
  sleep (1);
  gpio2 = fopen ("/sys/class/gpio/gpio2/value", "w");
  fprintf (gpio2, "1");
  fclose (gpio2);
  sleep (3);
}

//doing positive logic as button GPIOs are 0 on startup
void press_button (buttons b)
{
  char *fname = calloc (29, 1);
  sprintf (fname, "/sys/class/gpio/gpio%d/value", b);
  FILE *gpio = fopen (fname, "w");
  usleep (200000);
  fprintf (gpio, "0");
  fclose (gpio);
  gpio = fopen (fname, "w");
  usleep (200000);
  fprintf (gpio, "1");
  fclose (gpio);
}

void lower (shutter *r)
{
  press_button (down);
  usleep (r->percentage * r->rolltime_down * 10000);
  press_button (stop);
}