


#ifndef __MLCL_TEST_PERSON_H__
#define __MLCL_TEST_PERSON_H__


#include "../MLCL/MLCL.h"
#include "time.h"


typedef struct Person{
    char *lastname;
    char *firstname;
    time_t birth;
} Person;

Person * new_person(char *firstname, char *lastname);
void person_m(TypeDescriptor *td);
int person_cmp(const void *x, const void *y);
int person_eq(const void *x, const void *y);
int person_lt(const void *x, const void *y);
int person_le(const void *x, const void *y);
int person_gt(const void *x, const void *y);
int person_ge(const void *x, const void *y);
void person_print(const void * x);
void person_fprint(const void *x, FILE *stream);
void person_free(void *x);

#endif /* __MLCL_TEST_PERSON_H__ */