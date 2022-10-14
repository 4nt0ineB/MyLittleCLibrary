
```c
Timer * new_timer();
```

#### Start
```c
void timer_start(Timer *t);
```

#### Update
```c
void timer_update(Timer *t);
```

#### Get delta

```c
int timer_get_delta(const Timer *t);
```

#### Print
```c
void timer_fprint(const Timer *t, FILE * stream);
```

```c
void timer_print(const Timer *t);
```
