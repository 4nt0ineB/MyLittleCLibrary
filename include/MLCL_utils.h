/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_UTILS_H_H
#define MYLITTLECLIBRARY_MLCL_UTILS_H_H


/**
 * Linear random unsigned int generator
 * see: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
 * @return
 */
unsigned mlcl_unsigned_rand();

int int_rand(int a, int b);

float float_rand(float min, float max);


#endif /* MYLITTLECLIBRARY_MLCL_UTILS_H_H */
