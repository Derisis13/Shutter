#include "timing.h"
#include "moving_debug.h"
#include <stdio.h>
#define FILEPATH "menetrend.txt"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SHUTTER AUTOMATA
 * ---------------
 * C program for automating remote controlled shutters via an openwrt router and a paired remote.
 * This program needs to be called by Cron in few minute intervals.
 * Raise and lowering times as well as the desired lowering percentage is read from a local file (menetrend.txt), and is
 * executed; the schedule contains one full week.
 * The program uses GPIO2 for resetting the remote and GPIO17-21 for controlling the remote.
 * The program is compiled to openwrt 19.07.8; HW: D-Link DIR-600 rev.B6E
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main ()
{
  shutter ercsi13[] = {
      {
          1, 0, 0, 0, 0, 27, 0 //fiúszoba
      },
      {
          2, 0, 0, 0, 0, 27, 0 //lányszoba
      },
      {
          3, 0, 0, 0, 0, 27, 0 //nappali bal
      },
      {
          4, 0, 0, 0, 0, 27, 0 //nappali jobb
      },
      {
          5, 0, 0, 0, 0, 27, 0 //szülői szoba
      },
      {
          6, 0, 0, 0, 0, 18, 0 //konyha
      },
      {
          7, 0, 0, 0, 0, 33, 0 //előtető (lehúzás = kieresztés, felhúzás = behúzás)
      }
  };

  //scan the schedule
  for (int i = 0; i < 7; ++i)
    {
      FILE *schedule = fopen (FILEPATH, "r");
      find_today (schedule);
      get_timing (&ercsi13[i], schedule);
      fclose (schedule);
    }

  reset ();
  byte ch = 1;  //remote defaults to ch 1

  //check timings and act accordingly
  for (int i = 0; i < 7; ++i)
    {
      set_ch (&ercsi13[i], &ch);
      switch (check_timing (&ercsi13[i]))
        {
          case up:press_button (up);
          break;
          case stop:break;
          case down:lower (&ercsi13[i]);
          break;
          case prev:
          case next:break;
        };
    }
  return 0;
}