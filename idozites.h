//
// Created by lacko on 08/08/2021.
//
#ifndef _IDOZITES_H_
#define _IDOZITES_H_

#include "redony.h"
#include <time.h>
#include <stdio.h>

void get_timing (redony *r, FILE *schedule);

buttons check_timing (redony *r);

int find_today (FILE *schedule);

int find_next_day (FILE *f);

#endif //_IDOZITES_H_