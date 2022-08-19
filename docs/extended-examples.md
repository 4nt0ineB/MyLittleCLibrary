
### Double Linked List of Circular double linked lists
```c  
DoubleLinkedList l;  
CircularDoubleLinkedList l_2;  
float x;  
  
x = 3.14f;  
l_2 = new_circular_double_linked_list(&x, float_m);  

/* If we suppose that you already defined a circular double linked list manifest */
l = new_double_linked_list(&l_2, circular_double_linked_list_m);  

l->d->append(&l, &x); 
l->d->free(&tmp);  
```  

```c
int main(){    
	/* Making a new TypeDescriptor */     
	TypeDescriptor td;    
	td = new_type_descriptor(char_m);      
	/*      
		Allocating a TypeDescriptor is done inside      
		the constructor of the structure, so you just have to pass the manifest directly.   
	*/    
	char c;   
	CircularLinkedList l;    
	c = 'a';   
	l = new_circular_linked_list(&x, char_m);       
	/*      
		You can redefine the TypeDescriptor of a structure by its own descriptor.     
		Its has effect on all the structure, so you know what you are doing.   
	*/  
	type_descriptor_free(&l->d->type_descriptor);    
	l->d->type_descriptor = td;
	l->d->free(&tmp);
	return 0;
}
```