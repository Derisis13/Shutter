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

#include "timing.h"
#include <string.h>

int find_today (FILE *schedule)
{
  time_t t = time (NULL);
  struct tm *now = localtime (&t);
  char buffer[4] = {0};
  while (find_next_day (schedule) == 1)
    {
      fgets (buffer, 4, schedule);
      switch (now->tm_wday)
        {
          case 0:
            if (strcmp (buffer, "SUN") == 0)
              return 1;
          break;
          case 1:
            if (strcmp (buffer, "MON") == 0)
              return 1;
          break;
          case 2:
            if (strcmp (buffer, "TUE") == 0)
              return 1;
          break;
          case 3:
            if (strcmp (buffer, "WED") == 0)
              return 1;
          break;
          case 4:
            if (strcmp (buffer, "THU") == 0)
              return 1;
          break;
          case 5:
            if (strcmp (buffer, "FRI") == 0)
              return 1;
          break;
          case 6:
            if (strcmp (buffer, "SAT") == 0)
              return 1;
          break;
        }
    }
  return 0;
}

int find_next_day (FILE *f)
{
  char c;
  while (fscanf (f, "%c", &c) == 1)
    {
      if (c == '\n' && fgetc (f) == '\n')
        return 1;
    }
  return 0;
}

void get_timing (shutter *r, FILE *schedule)
{
  int tmp_min = 0, tmp_hour = 0, channel = 0, tmp_percentage = 0;
  while (channel != r->ch)
    {
      fscanf (schedule, "%*[^\n]s\n");
      while (fscanf (schedule, "%d", &channel) != 1)
        {
          fscanf (schedule, "%*c");
        }
    }

  while (fscanf (schedule, "%d:%d", &tmp_hour, &tmp_min) != 2)
    fscanf (schedule, "%*c");
  r->up.tm_hour = (char) tmp_hour;
  r->up.tm_min = (char) tmp_min;

  while (fscanf (schedule, "%d:%d", &tmp_hour, &tmp_min) != 2)
    fscanf (schedule, "%*c");
  r->down.tm_hour = (char) tmp_hour;
  r->down.tm_min = (char) tmp_min;

  while (fscanf (schedule, "%d", &tmp_percentage) != 1)
    fscanf (schedule, "%*c");
  r->percentage = (char) tmp_percentage;

  fscanf (schedule, "%*[^\n]s\n");
}

buttons check_timing (shutter *r, struct tm *now)
{
  if (r->percentage == 0)
    return stop;

  if ((r->down.tm_hour == now->tm_hour) && (r->down.tm_min == (now->tm_min)))
    {
      return down;
    }

  if ((r->up.tm_hour == now->tm_hour) && (r->up.tm_min == (now->tm_min)))
    {
      return up;
    }
  return stop;
}
