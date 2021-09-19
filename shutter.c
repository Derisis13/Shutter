//
// Created by lacko on 18/09/2021.
//
#include "shutter.h"
#include "stdlib.h"

shutter *create_shutter (byte ch, byte rolltime_down)
{
  shutter *new_shutter = calloc (1, sizeof (shutter));
  new_shutter->ch = ch;
  new_shutter->rolltime_down = rolltime_down;
  return new_shutter;
}

void append_shutter (shutter **head, shutter *new_shutter)
{
  if (*head == NULL)
    {
      *head = new_shutter;
      return;
    }
  shutter *tmp = *head;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new_shutter;
}

void free_shutters (shutter *head)
{
  for (shutter *tmp = head; head != NULL; tmp = head)
    {
      head = head->next;
      free (tmp);
    }
}
