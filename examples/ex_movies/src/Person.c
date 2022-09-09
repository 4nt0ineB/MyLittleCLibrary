
#include "../include/Person.h"
#include "stdlib.h"
#include "string.h"

Person * new_person(char *firstname, char *lastname){
    Person *person;
    if(!firstname && !lastname) return NULL;
    person = (Person *) malloc(sizeof(Person));
    if(!person) return NULL;
    person->firstname = firstname;
    person->lastname = lastname;
    person->birth = 0;
    return person;
}

void person_m(TypeDescriptor *td){  
    assert(td);
    td->data_size = sizeof(Person);  
    td->manifest = person_m;  
    td->cmp = person_cmp;  
    td->print = person_print;  
    td->fprint = person_fprint;  
    td->copy = NULL;  
    td->data_free = person_free;  
    td->eq = person_eq;  
    td->lt = person_lt;  
    td->le = person_le;  
    td->gt = person_gt;
    td->ge = person_ge;  
}  
  
int person_cmp(const void *x, const void *y){  
    char t;
	t = strcmp(((Person *) x)->lastname, ((Person *) y)->lastname);
    
    /*

    if(t == 0)
	    return strcmp(((Person *) x)->firstname, ((Person *) y)->firstname);
    */
    return t;
}  
  
int person_eq(const void *x, const void *y){  
	return person_cmp(x, y) == 0;
}  
  
int person_lt(const void *x, const void *y){  
	return person_cmp(x, y) < 0;
}  
  
int person_le(const void *x, const void *y){  
	return person_cmp(x, y) <= 0;
}  
  
int person_gt(const void *x, const void *y){  
	return person_cmp(x, y) > 0;
}  
  
int person_ge(const void *x, const void *y){  
	return person_cmp(x, y) >= 0;
}  
  
void person_print(const void *x){  
	person_fprint(x, stdout);  
}  
  
void person_fprint(const void *x, FILE *stream){  
    Person *person;
    if(!x) return;
    person = (Person *) x;
    if(person->firstname)
        fprintf(stream, "%s",  person->firstname);
    fprintf(stream, " ");
    if(person->lastname)
        fprintf(stream, "%s",  person->lastname);
}  
  
  
void person_free(void *x){
    Person *person;
	if(!x) return;
    person = (Person *) x;
    if(person->lastname) free(person->lastname);
	if(person->firstname) free(person->firstname);
	free(x);
}
