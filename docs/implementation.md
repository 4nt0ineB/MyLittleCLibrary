
## Introduction

The structures are linked to a type descriptor (called 'td') trough which they use the associated functions, allowing to manipulate the data independently of the *effective* type they are carrying.  You specify the data carried by the structure at creation.
For example the linked list is implemented like [this](#linked-list-implementation).

You use the linked list this way:
```c
LinkedList *l = new_linked_list(int_m);
linked_list_append(l, new_int(3));
```
As the functions of a structures call other functions through the descriptor, we can override the methods behavior be using custom ones (so, on the modified structure only).

```c
void my_custom_fprintf(const void *data, FILE *stream){
    fprintf("[--- %c ---]", *(char *) data);
}
...
LinkedList *l = new_linked_list(char_m);
l->td->fprint = my_custom_fprintf;
```


### Structures inheritance

```mermaid
flowchart  TB
	 
	ArrayList --> TypeDescriptor
	LinkedList --> TypeDescriptor
	DoubleLinkedList --> TypeDescriptor
	
	List --> ArrayList
	List --> LinkedList 
	List --> CircularLinkedList --> LinkedList
	List --> DoubleLinkedList 
	List --> CircularDoubleLinkedList --> DoubleLinkedList
	
	BinaryHeap --> ArrayList
	Queue --> List
	Stack --> List
	
	BinarySearchTree --> TypeDescriptor
	AVLTree --> TypeDescriptor
	LexicalTree --> TypeDescriptor
	BKTree --> TypeDescriptor
	
```

### Linked list implementation

```mermaid
flowchart  LR

	subgraph ll[LinkedList]
		td
		head
	end
	head --> cell0
	td --> tdescriptor
	 
	subgraph  tdescriptor[TypeDescriptor]
		data_size
		manifest
		f0("data_free")
		f1("printf()")
		f2("fprintf()")
		f3("cmp()")
		f4("eq()")
		...
	end
	
	subgraph cell0[LinkedListNode]
        v0(void *data)
        next0(next)
        
    end
    next0 --> cell1
    
    subgraph cell1[LinkedListNode]
        v0(void *data)
        next1(next)
    end
    next1 --> cell2
    
    subgraph  cell2[LinkedListNode]
        v0(void *data)
        next2(next)
    end
```
Basically all structures are implemented this way.