/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MYLITTLECLIBRARY_MLCL_TIMER_H
#define MYLITTLECLIBRARY_MLCL_TIMER_H

#include <stdio.h>
#include <sys/time.h>

typedef struct {
  unsigned int state: 1;
  struct timeval start;
  struct timeval end;
} Timer;

int timer_diff_time(struct timeval start, struct timeval end);
int timer_ms_to_ss(int ms);
int timer_ms_to_s(int ms);
int timer_ms_to_m(int ms);
int timer_ms_to_h(int ms);
void timer_start(Timer *t);
void timer_update(Timer *t);
int timer_get_delta(Timer t);
void timer_fprint(FILE * stream, Timer t);
void timer_print(Timer t);


#endif /* MYLITTLECLIBRARY_MLCL_TIMER_H */
