# Cato

*Garbage delenda est.*

![Cato's Bust](https://classconnection.s3.amazonaws.com/801/flashcards/363801/jpg/cato1364004919780.jpg)

## Cheney's Algorithm

Cato is currently implemented using [Cheney's algorithm][cheney wiki]. Cheney's
algorithm consists in allocating all objects in one arena. Once that arena
reaches a certain capacity, the objects it contains are copied over to another,
equal-capacity arena. Copied objects are replaced in the original arena with
pointers to locations in the new one. These allow the algorithm to trace the
graph of each object's references so that objects without references are never
copied. The original arena is then freed and used as the destination to copy
objects to once the new arena reaches its own usage limit.

[cheney wiki]: http://en.wikipedia.org/wiki/Cheney's_algorithm

## Cato's Values

Cato requires composite values that reference each other so that it can free
the ones that aren't referenced. For this it defines a simple ValueHeader
type--a struct whose members are a value's length and whether this value holds
primitive or composite data. The actual data is type-punned onto each
ValueHeader. The ValueHeader pointer type is aliased as Val.

The following macros make Cato's values easier to manipulate.

```c
    // Read or write the data held by the value with address valuePointer
    DATA(valuePointer, type) 

    // Allocate and return a value holding primitive data of the given type
    PRIM_VAL(type, data) 

    // Allocate and return a value holding composite data of the given type
    OBJ_VAL(type, data) 
```

## Lessons Learned

When incrementing a variable, always check whether it holds a pointer that
could affect the size of the increment.

GCC allows the creation of arbitrary scopes using curly braces. This is good
for keeping variables private inside a macro.

