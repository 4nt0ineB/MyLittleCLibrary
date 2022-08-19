
##  Type manifest

###  What's that

All the structures are linked to a *TypeDescriptor*, an interface required to manipulate the data they are carrying.

It requires (for now), few things:
- the size of the type you want to use
- some functions to print the data
- a function to free the data and another one to copy the data  (deep or not, you decide if you make your own)
- some comparison functions

The *TypeDescriptor* gets those through a type manifest which handle specific functions of the type to be manipulated.  
Its like defining you own type in Python (\_\_str__, \_\_eq__, \_\_lt__, etc...).

When making new structures you passes the manifest of the type you want they carry :
```c
ArrayList l = new_array_list(int_m); /* Voilà, you have got a brand new array list of int */
```
### Define your own type

Let's look at the *char_m*(anifest) for example:

```c  
/*   src/basic_types.c */  
void char_m(TypeDescriptor * td){  
	assert(type_descriptor);  
  td->data_size = sizeof(char);  
  td->manifest = char_m;  
  td->cmp = char_cmp;  
  td->print = char_print;  
  td->fprint = char_fprint;  
  td->copy = char_copy;  
  td->free_data = char_free;  
  td->eq = char_eq;  
  td->lt = char_lt;  
  td->le = char_le;  
  td->gt = char_gt;  
  td->ge = char_ge;  
}  
  
int char_cmp(const void * x, const void * y){  
	return (*(char *) x == *(char *) y) ? 0 : (*(char *) x < *(char *) y) ? -1 : 1;  
}  
  
int char_eq(const void * x, const void * y){  
	return (*(char *) x) == (*(char *) y);  
}  
  
int char_lt(const void * x, const void * y){  
	return (*(char *) x) < (*(char *) y);  
}  
  
int char_le(const void * x, const void * y){  
	return (*(char *) x) <= (*(char *) y);  
}  
  
int char_gt(const void * x, const void * y){  
	return (*(char *) x) > (*(char *) y);  
}  
  
int char_ge(const void * x, const void * y){  
	return (*(char *) x) >= (*(char *) y);  
}  
  
void char_print(const void * x){  
	char_fprint(stdout, x);  
}  
  
void char_fprint(FILE * stream, const void * x){  
	if(!x)  fprintf(stream, "Null");  
  fprintf(stream, "%c",  *(char *) x);  
}  
  
void * char_copy(const void * data){  
	void * alloc_data;  
	size_t data_size;  
	data_size = sizeof(char);  
	alloc_data = calloc(1, data_size);  
	if(!alloc_data) return NULL;  
	memcpy(alloc_data, data, data_size);  
	return alloc_data;  
}  
  
void char_free(void ** x){  
	if(!*x) return;  
	free(*x);  
	*x = NULL;  
}

/*    
	By making your own type_manifest you will be able to use your custom Type through
	the lib's implemented structures. Like so:    
*/
 
int main(){  
 char c; 
 CircularLinkedList l;  
 c = 'a'; 
 l = new_circular_linked_list(&x, char_m);     
 l->d->free(&tmp);  
 return 0;
}
```