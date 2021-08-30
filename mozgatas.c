//
// Created by lacko on 08/08/2021.
//

#include "mozgatas.h"
#include <stdio.h>
#include <unistd.h> //ugye openwrt-re fordul

void set_ch (redony *r)
{
  reset ();
  for (int i = 1; i < r->ch; ++i)
    {
      press_button (next);
    }
}

/*
void export ()
{
  printf ("exporting...\n");
  FILE *export = fopen ("/sys/class/gpio/export", "w");
  int gpios[] = {2, 17, 18, 19, 20, 21};
  for (int i = 0; i < 6; ++i)
  {
    fprintf (export, "%d", gpios[i]);
    char fname[33] = {'\0'};
    sprintf (fname, "/sys/class/gpio/gpio%d/direction", gpios[i]);
    FILE *gpio = fopen (fname, "w");
    fprintf (gpio, "out");
  }
  printf ("exporting done.\n");

}*/

//doing negative logic as reset is active low and GPIOs are 1 on startup
void reset ()
{
  //printf ("resetting...\n");

  FILE *gpio2 = fopen ("/sys/class/gpio/gpio2/value", "w");
  fprintf (gpio2, "0");
  fclose (gpio2);
  sleep (1);
  gpio2 = fopen ("/sys/class/gpio/gpio2/value", "w");
  fprintf (gpio2, "1");
  fclose (gpio2);
  sleep (3);

  //printf ("reset done\n");
}

//doing positive logic as GPIOs are 0 on startup
void press_button (buttons b)
{
  //printf ("activating gpio %d...\n", b);

  char fname[29] = {'\0'};
  sprintf (fname, "/sys/class/gpio/gpio%d/value", b);
  FILE *gpio = fopen (fname, "w");
  fprintf (gpio, "0");
  fclose (gpio);
  gpio = fopen (fname, "w");
  usleep (200000);
  fprintf (gpio, "1");
  fclose (gpio);
  sleep (1);

  //printf ("done\n");
}