/*
   Created by antoine on 6/18/22.
*/

#ifndef MYLITTLECLIBRARY_MLCL_TYPES_H
#define MYLITTLECLIBRARY_MLCL_TYPES_H

#include <stdlib.h>

typedef struct s_type_descriptor {
    size_t data_size;
    int (*cmp) (const void * x, const void * y);
    void (*print) (const void * data);
    void (*free_data) (void ** data);
} TypeDescriptor;

TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor));
void type_descriptor_free(TypeDescriptor ** td);

/* ... int ... */

void int_manifest(TypeDescriptor * type_descriptor);
int int_cmp(const void * x, const void * y);
void int_print(const void * x);
void int_free(void ** x);



#endif /* MYLITTLECLIBRARY_MLCL_TYPES_H */
