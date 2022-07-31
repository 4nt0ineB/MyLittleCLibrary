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
