//
// Created by lacko on 08/08/2021.
//
#ifndef _TIMING_H_
#define _TIMING_H_

#include "shutter.h"
#include <time.h>
#include <stdio.h>

//reads the timing and percentage form the schedule file
void get_timing (shutter *r, FILE *schedule);

//checks whether it's time to raise/lower and acts accordingly
buttons check_timing (shutter *r);

//checks the schedule file and sets the readhead to today's label
int find_today (FILE *schedule);

//sets the readhead to the next day-label
int find_next_day (FILE *f);

#endif //_TIMING_H_