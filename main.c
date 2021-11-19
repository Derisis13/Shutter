#include "timing.h"
#include "moving.h"
#include <stdio.h>
#define FILEPATH "schedule.txt"
#define N_of_Shutters 7
#define rolltimelist {23, 23, 23, 23, 16, 23, 33}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SHUTTER AUTOMATA
 * -----------------
 * C program for automating remote controlled shutters via an embedded linux platform and a paired remote.
 * This program needs to be called by a scheduler (like Cron) in few minute intervals.
 * Raise and lowering times are defined in the rolltimelist macro. The N_of_Shutters macro contains the f
 * well as the desired lowering percentages are read from a local file (schedule.txt), and
 * are executed; the schedule contains one full week.
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * This file is part of Shutter.
 *
 * Shutter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shutter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shutter.  If not, see <https://www.gnu.org/licenses/>.
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