
#### Comparison predicate 
```c
NEQ // not equal     !=
EQ  // equal         == 
LT  // less than     <
LE  // less equal    <=
GT  // greater than  >
GE  // greater equal >=
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
```c
/**
 * @brief this is a typical 
 * filter function for a Filter
 * 
 * @param the struct / data that 
 * will be tested in this filter
 * 
 * @param field_value a value to 
 * pass to the test (or a more complex structure...)
 * 
 * @param cmp_predicate NEQ, EQ, LT, LE,...
 * 
 * @return 1 if not passing the filter, 
 * 0 else (no problem)
**/
int movie_filter_title(void *self, void *field_value, comparison_predicate_t cmp_predicate){
    Movie *movie;
    if(!self || !field_value) return 0;
    movie = (Movie *) self;
    return logic_cmp(strcmp(movie->title, field_value), cmp_predicate);
}
```
The function logic_cmp is very important (!!), it's a shortcut to not have to write a switch each time for the predicate.


<br>


then use this filter function as condition in a Filter instance

```c
/* MLCL_Filter.h */

/**
 * @brief make a new condition from 
 * filter_function for a Filter instance
 * 
 * @param filter_function a function to check 
 * condition on structure/type with a Filter
 * 
 * @param value a value to compare the field with
 * 
 * @param cmp_predicate how to compare 
 * the field with the value
 *
 * @param value_free Function to free the given 
 * field_value. Set NULL to avoid freeing
 * 
 * @return
 */
ConditionalFilter * new_condition(
        cfilter_f filter_function,
        void *field_value,
        comparison_predicate_t cmp_predicate,
        void (*value_free) (void *data)
);
```

```c
filter = new_filter(1);
/* We want to target movies with title "Barry Lyndon" */
filter->conditions[0] = new_condition(movie_filter_title, new_str("Barry Lyndon"), EQ, int_free);
```