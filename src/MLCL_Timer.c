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

#include "../include/MLCL_Timer.h"
#include "../include/MLCL_utils.h"
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

void timer_fprint(FILE * stream, Timer t){
    int ss, s, m, h, ms;
    ms = timer_get_delta(t);
    ss = timer_ms_to_ss(ms);
    s = timer_ms_to_s(ms);
    m = timer_ms_to_m(ms);
    h = timer_ms_to_h(ms);
    fprintf(stream, "%02d:%02d:%02d:%02d", h, m, s, ss);
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

int timer_get_delta(Timer t){
    return timer_diff_time(t.start, t.end);
}

void timer_print(Timer t){
    timer_fprint(stdout, t);
}

