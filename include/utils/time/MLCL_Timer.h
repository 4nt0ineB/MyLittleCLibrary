/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
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

Timer * new_timer();
void timer_start(Timer *t);
void timer_update(Timer *t);
int timer_get_delta(const Timer *t);
void timer_fprint(const Timer *t, FILE *stream);
void timer_print(const Timer *t);


#endif /* MYLITTLECLIBRARY_MLCL_TIMER_H */
