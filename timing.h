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

#ifndef _TIMING_H_
#define _TIMING_H_

#include "shutter.h"
#include <time.h>
#include <stdio.h>

//reads the timing and percentage form the schedule file
void get_timing (shutter *r, FILE *schedule);

//checks whether it's time to raise/lower and acts accordingly
buttons check_timing (shutter *r, struct tm* now);

//checks the schedule file and sets the readhead to today's label
int find_today (FILE *schedule);

//sets the readhead to the next day-label
int find_next_day (FILE *f);

#endif //_TIMING_H_