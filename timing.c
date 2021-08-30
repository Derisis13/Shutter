//
// Created by lacko on 08/08/2021.
//

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
            if (strcmp (buffer, "VAS") == 0)
              return 1;
          break;
          case 1:
            if (strcmp (buffer, "HET") == 0)
              return 1;
          break;
          case 2:
            if (strcmp (buffer, "KED") == 0)
              return 1;
          break;
          case 3:
            if (strcmp (buffer, "SZE") == 0)
              return 1;
          break;
          case 4:
            if (strcmp (buffer, "CSU") == 0)
              return 1;
          break;
          case 5:
            if (strcmp (buffer, "PEN") == 0)
              return 1;
          break;
          case 6:
            if (strcmp (buffer, "SZO") == 0)
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
  int channel = 0;
  while (channel != r->ch)
    {
      fscanf (schedule, "%*[^\n]s\n");
      while (fscanf (schedule, "%d", &channel) != 1)
        {
          fscanf (schedule, "%*c");
        }
    }

  while (fscanf (schedule, "%d:%d", &r->up.tm_hour, &r->up.tm_min) != 2)
    fscanf (schedule, "%*c");

  while (fscanf (schedule, "%d:%d", &r->down.tm_hour, &r->down.tm_min) != 2)
    fscanf (schedule, "%*c");

  while (fscanf (schedule, "%d", &r->percentage) != 1)
    fscanf (schedule, "%*c");

  fscanf (schedule, "%*[^\n]s\n");
}

buttons check_timing (shutter *r)
{
  if (r->percentage == 0)
    return stop;
  time_t t = time (NULL);
  struct tm *now = localtime (&t);
  if ((r->down.tm_hour == now->tm_hour) && (r->down.tm_min == now->tm_min))
    {
      return down;
    }

  if ((r->up.tm_hour == now->tm_hour) && (r->up.tm_min == now->tm_min))
    {
      return up;
    }

  return stop;
}
