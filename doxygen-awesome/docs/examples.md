# Examples

## Linked list
```c
int x;
LinkedList l;

x = 5.3f;
l = new_linked_list(&x, float_manifest);

l->d->append(&l, &x);
l->d->free(&tmp);

```

## Double linked list
```c
int x;
DoubleLinkedList l;

x = 5;
l = new_double_linked_list(&x, int_manifest);

l->d->append(&l, &x);
l->d->free(&tmp);
```

## Extended Examples

### DoubleLinkedList of CircularDoubleLinkedLists
```c
DoubleLinkedList l;
CircularDoubleLinkedList l_2;
float x;

x = 3.14f;
l_2 = new_circular_double_linked_list(&x, float_manifest);
l = new_double_linked_list(&l_2, circular_double_linked_list_manifest);
l->d->append(&l, &x); 
l->d->free(&tmp);

```


### Type_manifest

#### What's that

All the structures are linked to a TypeDescriptor, an interface required to manipulate the data they are carrying.

It requires (for now), few things:
	- the size of the type you want to use
	- some functions to print the data
	- a function to free the data and another one to copy the data
	- some comparison functions

The TypeDescriptor gets this through a type_manifest which handle specific functions of the type to be manipulated.

### Writing your own TypeDescriptor

Let's look at the char_manifest for example:

```c
/* 
	src/basic_types.c 
*/
void char_manifest(TypeDescriptor * type_descriptor){
	assert(type_descriptor);
	type_descriptor->data_size = sizeof(float);
	type_descriptor->print = char_print;
	type_descriptor->fprint = char_fprint;
	type_descriptor->copy = char_copy;
	type_descriptor->free_data = char_free;
	type_descriptor->cmp = char_cmp;
	type_descriptor->eq = char_eq;
	type_descriptor->lt = char_lt;
	type_descriptor->le = char_le;
	type_descriptor->gt = char_gt;
	type_descriptor->ge = char_ge;
}

int char_cmp(const void * x, const void * y){
	return (*(char *) x == *(char *) y) ? 0 : (*(char *) x < *(char *) y) ? -1 :  1;
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

void char_fprint(FILE * file, const void * x){
	fprintf(file, "%c",  *(char *) x);
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
 * By making your own type_manifest you will be able to use your custom Type through 
 * the lib's implemented structures. Like so: 
 */
int main(){
    
    /* Making a brand new TypeDescriptor */

	TypeDescriptor td;
	td = new_type_descriptor(char_manifest);
    
	/* 
	  Allocating a TypeDescriptor is done inside 
	  the constructor of the structure,
	  so you just have to pass the manifest directly.
	*/

	char c;
	CircularLinkedList l;

	c = 'a';
	l = new_circular_linked_list(&x, char_manifest);
    
    /* 
     Note: You can redefine the TypeDescriptor of a structure by its own descriptor.
     Its has effect on all the structure, so you know what you are doing.
    */
    
	type_descriptor_free(&l->d->type_descriptor);
    l->d->type_descriptor = td;
	
	l->d->free(&tmp);
	return 0;
}

```