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

#ifndef MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H
#define MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H

#include <stdio.h>

#define MLCL_TEST(result, str) {printf("├ %s :", str);if(result()){printf(" ok\n");}else{return 0;}}
#define MLCL_ERR(id, msg) {printf("\n\t[%d]: " msg "\n", id); return 0;}
#define MLCL_OK() {printf("\tok\n");}
#define MLCL_ERR_ALLOC "Allocation failed."
#define MLCL_ERR_EQ "Should be equal."
#define MLCL_ERR_NEQ "Shouldn't be equal."
#define MLCL_ERR_VAL "Not the expected value."
#define MLCL_ERR_TRUE "Should be true."
#define MLCL_ERR_FALSE "Should be false."

#endif /* MYLITTLECLIBRARY_MLCL_EXCEPTIONS_H */
