# Cato

*"Garbage delenda est."*

![Cato's Bust](https://classconnection.s3.amazonaws.com/801/flashcards/363801/jpg/cato1364004919780.jpg)

Cato is a crusty garbage collector implementing [Cheney's Algorithm]
[cheney wiki], the same one [V8 uses for its first generation of garbage
collection][jay conrod post].

"Crusty" means you would never want to use Cato because it requires you to
replace C's most basic operations with obtrusive macros. The source is small so
it's worth a read. The relevant files are [value.h], [value.c], [cheney.h], and
[cheney.c][cheney.c].

[cheney wiki]: http://en.wikipedia.org/wiki/Cheney's_algorithm
[jay conrod post]: http://jayconrod.com/posts/55/a-tour-of-v8-garbage-collection

[value.h]: src/value.h
[value.c]: src/value.c
[cheney.h]: src/cheney.h
[cheney.c]: src/cheney.c

## Using Cato

*"Νature has it that style is in the service of thought, not the other way
around."*


**The Virtual Stack**

Cato needs to mirror your stack variables in its own virtual stack. This way it
can start from the current and previous stack frames when scanning the state of
your program for live objects. You must call `pushFrame` and `popFrame` at the
beginning and end of every function call.

**Initializing Variables**

Cato also needs to know about new stack variables. To initialize a primitive,
call `PRIM_VAR(type, identifier, data)`.  For a variable that holds references
to other variables, call `OBJ_VAR(type, identifier, data)`. For example:

```c
    // Initialize a variable myVar of type char that holds the character 'b'
    PRIM_VAR(char, myVar, 'b');

    // Initialize a variable v1 of type Vertex that points to variables v2 and v3.
    OBJ_VAR(Vertex, v, ((Vertex) {
          .left = b,
          .right = c
        }));
```

**Accessing variables**

Accessing the value inside a variable also requires a macro, like so:

```c
    PRIM_VAR(char, myVar, 'b');
    'b' == DATA(myVar, char); // => true
```

## Cato's Values

*"The best way to keep good acts in memory is to refresh them with new."*

Cheney's Algorithm relies on the existence of composite values that reference
each other. For this Cato defines the ValueHeader type. A value is either a
primitive or a collection of references to other values. The ValueHeader is a
struct that holds information about this value. The value's data is type-punned
onto the ValueHeader. In other words, take a ValueHeader's address, offset that
by the size of a ValueHeader, and that's where you'll find the associated data.

"ValueHeader" is a mouthful and it's always used as a pointer, so Cato
helpfully aliases pointers to ValueHeaders as ValRefs.

## Cheney's Algorithm

*"Grasp the subject, the words will follow."*

Cheney's Algorithm consists in allocating all objects in one arena. Once that
arena reaches a certain capacity, its live objects are copied over to another,
equal-capacity arena. Copied objects are replaced in the original arena with
pointers to locations in the new one. These allow the algorithm to trace the
graph of each object's references so that objects without references are never
copied. The original arena is then freed and used as the destination to copy
objects to once the new arena reaches its own usage limit.

To determine whether an object is live or garbage, Cato starts at the root set
of objects and traces their references to other objects. Any object that isn't
reachable from the root set is treated as garbage. While common, this approach
is not exhaustive. Objects may be no longer needed and yet still reacheable
from the root set. The root set is the set of variables in current or previous
stack frames.

## Lessons Learned

*"Wise men learn more from fools than fools from the wise."*

When incrementing a variable, always check whether it holds a pointer that
could affect the size of the increment.

GCC allows the creation of arbitrary scopes using curly braces. This is good
for keeping variables private inside a macro.

To avoid surprises when the compiler [inserts padding between unaligned values]
[alignment article], Cato records the length of a value in its ValueHeader as a
multiple of the ValueHeader type's alignment requirement. That number is 8
bytes on most platforms because the ValueHeader's member type with the highest
alignment requirement is a `size_t`. To avoid hard-coding this number, Cato
uses the `__alignof` operator.

[alignment article]: http://www.catb.org/esr/structure-packing/

