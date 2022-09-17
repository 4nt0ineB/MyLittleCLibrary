
#### Comparison predicate 
```c
NEQ // not equal !=
EQ // equal == 
LT // less than <
LE // less equal <=
GT // greater than >
GE // greater equal >=
```

### Filter

```c
Filter *filter = new_filter(1);
filter->condition[0] = new_condition(movie_filter_on_title, new_str("Matrix"), EQ, str_free);
filter_free(&filter);
```

### Evaluate
```c
filter->evaluate(filter, mycustomstruct);
```

### Free
```c
filter_free(&filter);
```

### Make your filter
// todo
``c
int movie_filter_title(void *self, void *field_value, comparison_predicate_t cmp_predicate){
    Movie *movie;
    if(!self || !field_value) return 0;
    movie = (Movie *) self;
    return logic_cmp(strcmp(movie->title, field_value), cmp_predicate);
}
``