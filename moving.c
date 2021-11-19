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

#include "moving.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //project is to be compiled to openwrt

#define RESETPIN "/sys/class/gpio/gpio2/value"

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

//doing negative logic as reset is active low and GPIO2 is 1 on startup
void reset ()
{
  FILE *gpio2 = fopen (RESETPIN, "w");
  fprintf (gpio2, "0");
  fclose (gpio2);
  sleep (1);
  gpio2 = fopen (RESETPIN, "w");
  fprintf (gpio2, "1");
  fclose (gpio2);
  sleep (3);
}

//doing positive logic as button GPIOs are 0 on startup
void press_button (buttons b)
{
  char *fname = calloc (29, sizeof (char ));
  sprintf (fname, "/sys/class/gpio/gpio%d/value", b);
  FILE *gpio = fopen (fname, "w");
  fprintf (gpio, "0");
  fclose (gpio);
  gpio = fopen (fname, "w");
  usleep (150000);
  fprintf (gpio, "1");
  fclose (gpio);
  usleep (250000);
  free (fname);
}

void lower (shutter *r)
{
  press_button (down);
  usleep (r->percentage * r->rolltime_down * 10000);
  press_button (stop);
}
