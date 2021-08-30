//
// Created by lacko on 08/08/2021.
//

#include "idozites.h"
#include <string.h>

//function, which navigates the file, and stops at the label of today.
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
            if (strcasecmp (buffer, "VAS") == 0)
              return 1;
          break;
          case 1:
            if (strcasecmp (buffer, "HET") == 0)
              return 1;
          break;
          case 2:
            if (strcasecmp (buffer, "KED") == 0)
              return 1;
          break;
          case 3:
            if (strcasecmp (buffer, "SZE") == 0)
              return 1;
          break;
          case 4:
            if (strcasecmp (buffer, "CSU") == 0)
              return 1;
          break;
          case 5:
            if (strcasecmp (buffer, "PEN") == 0)
              return 1;
          break;
          case 6:
            if (strcasecmp (buffer, "SZO") == 0)
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

void get_timing (redony *r, FILE *schedule)
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
  fscanf (schedule, "%*[^\n]s\n");

}

buttons check_timing (redony *r)
{
  if ((r->up.tm_hour == r->down.tm_hour) && (r->up.tm_min == r->down.tm_min))
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
