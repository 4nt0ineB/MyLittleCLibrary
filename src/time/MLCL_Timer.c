/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../include/time/MLCL_Timer.h"
#include "../../include/utils/MLCL_utils.h"
#include <stdlib.h>

int timer_diff_time(struct timeval start, struct timeval end){
    return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

int timer_ms_to_ss(int ms) {
    return proper_modulo(ms / 10, 100);
}

int timer_ms_to_s(int ms) {
    return proper_modulo(ms / 1000, 60);
}

int timer_ms_to_m(int ms) {
    return proper_modulo(ms / (1000 * 60), 60);
}

int timer_ms_to_h(int ms) {
    return proper_modulo(ms / (3.6 * 1000000), 100);
}

Timer * new_timer(){
    return (Timer *) calloc(1, sizeof(Timer));
}

void timer_start(Timer *t){
    if(!t) return;
    gettimeofday(&t->start, NULL);
}

void timer_update(Timer *t){
    if(!t) return;
    gettimeofday(&t->end, NULL);
}

int timer_get_delta(const Timer *t){
    return timer_diff_time(t->start, t->end);
}

void timer_fprint(FILE * stream, const Timer *t){
    int ss, s, m, h, ms;
    ms = timer_get_delta(t);
    ss = timer_ms_to_ss(ms);
    s = timer_ms_to_s(ms);
    m = timer_ms_to_m(ms);
    h = timer_ms_to_h(ms);
    fprintf(stream, "%02d:%02d:%02d:%02d", h, m, s, ss);
}

void timer_print(const Timer *t){
    timer_fprint(stdout, t);
}

