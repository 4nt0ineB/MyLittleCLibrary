# Examples

### Linked list
```c

int x;
LinkedList l;

x = 5.3f;
l = new_linked_list(&x, float_manifest);

l->d->append(&l, &x);
l->d->free(&tmp);

```

### Double linked list
```c

int x;
DoubleLinkedList l;

x = 5;
l = new_double_linked_list(&x, int_manifest);

l->d->append(&l, &x);
l->d->free(&tmp);

```

## TypeDescriptor : How do I make my own

### What's that

The TypeDescriptor is an interface required to manipulate the data across all the lib's structures. 

It require (for now), few things:
	- the size of the the type you want to use
	- a function to compare two data, and works like strcmp, returning -1, 0, or 1 (inferior, equal, superior)
	- a function to print the data on a stream
	- a function to print the data on stdout (actually a shortcut for the previous one)
	- a function to free the data

The TypeDescriptor gets those trough a type_manifest which handle specific functions of the type to be manipulated.

### Writing your own TypeDescriptor

Let's look at the char_manifest for example:

```c
/* 
	src/basic_types.c 
*/

void char_manifest(TypeDescriptor * type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(char);
    type_descriptor->cmp = char_cmp;
    type_descriptor->fprint = char_fprint;
    type_descriptor->print = char_print;
    type_descriptor->free_data = char_free;
}

int char_cmp(const void * x, const void * y){
    return (*(char *) x == *(char *) y) ? 0 : (*(char *) x < *(char *) y) ? -1 :  1;
}

void char_fprint(FILE * file, const void * x){
    fprintf(file, "%c",  *(char *) x);
}

void char_print(const void * x){
    char_fprint(stdout, x);
}

void char_free(void ** x){
    if(!*x) return;
    free(*x);
    *x = NULL;
}

/* Wich allow us to do */

int main(){

	TypeDescriptor td;
	td = new_type_descriptor(char_manifest);
	type_descriptor_free(&td);

	/* This is done inside the constructor of the structure,
	  so you just have to pass the manifest */

	char c;
	CircularLinkedList l;

	c = 'a';
	l = new_circular_linked_list(&x, char_manifest);
	l->d->free(&tmp);

	return 0;
}

```