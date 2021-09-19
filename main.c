#include "timing.h"
#include "moving.h"
#include <stdio.h>
#define FILEPATH "menetrend.txt"
#define N_of_Shutters 7
#define rolltimelist {23, 23, 23, 23, 16, 23, 33}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SHUTTER AUTOMATA
 * -----------------
 * C program for automating remote controlled shutters via an openwrt router and a paired remote.
 * This program needs to be called by Cron in few minute intervals.
 * Raise and lowering times as well as the desired lowering percentage is read from a local file (menetrend.txt), and is
 * executed; the schedule contains one full week.
 * The program uses GPIO2 for resetting the remote and GPIO17-21 for controlling the remote.
 * The program is compiled to openwrt 19.07.8; HW: D-Link DIR-600 rev.B6E
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main ()
{
  //set up linked list of shutters
  shutter *ercsi13 = NULL;
  byte rolltimes[] = rolltimelist;
  for (int i = 0; i < N_of_Shutters; ++i)
    {
      shutter *tmpshutter = create_shutter ((byte)(i + 1), rolltimes[i]);
      append_shutter (&ercsi13, tmpshutter);
    }

  //get the time of launch
  time_t t = time (NULL);
  struct tm *now = localtime (&t);

  //scan the schedule

  for (shutter *tmp = ercsi13; tmp != NULL; tmp = tmp->next)
    {
      FILE *schedule = fopen (FILEPATH, "r");
      find_today (schedule);
      get_timing (tmp, schedule);
      fclose (schedule);
    }

  reset ();
  byte ch = 1;  //remote defaults to ch 1

  //check timings and act accordingly
  for (shutter *tmp = ercsi13; tmp != NULL; tmp = tmp->next)
    {
      set_ch (tmp, &ch);
      switch (check_timing (tmp, now))
        {
          case up:press_button (up);
          break;
          case stop:break;
          case down:lower (tmp);
          break;
          case prev:
          case next:break;
        };
    }
  free_shutters (ercsi13);
  return 0;
}