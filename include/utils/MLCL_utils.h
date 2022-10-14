/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_UTILS_H_H
#define MYLITTLECLIBRARY_MLCL_UTILS_H_H

/**
 * Linear random unsigned int generator
 * see: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
 * @return
 */
unsigned munsigned_rand();

int mint_rand(int a, int b);
float mfloat_rand(float min, float max);
int mmodulo(int a, int b);

/**
 * Return Levenshtein distance (edit distance) between two words
 * from wikipedia
 * @param s1
 * @param s2
 * @return
 */
int mlevenshtein(const char *s1, const char *s2);

#endif /* MYLITTLECLIBRARY_MLCL_UTILS_H_H */
