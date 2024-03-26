# Strong-Bool

Consider a legacy codebase in C++ that uses `int` instead of `bool`.
It's **so** legacy that it is probably C89, really, before the
advent of the `bool` type in any form. So typical code that has
a "boolean" variable as a class member variable looks like this:

```
class Example {
public:
    Example() : m_toggle(0) { }
    void SetIt(int v) { m_toggle = v; }
    void ToggleIt() { if (m_toggle) { m_toggle = 0; } else { m_toggle = 1; } }
    const char * Status() { if (m_toggle) return "ON"; else return "OFF"; }
private:
    int m_toggle;
};
```

There is an `int` in this class, but we use it like a boolean value. Except
for `SetIt()`, there is sort-of-an-invariant that the value is either 0 or 1.

Suppose I wake up and want to replace that `int` by a `bool`, but in such a
way that **every** use of that variable with an integer value -- and not
a boolean constant -- will trigger a compile error? In other words, what
type `T` do I need so that the following does-it-compile holds?

```
T t = 0; // error
T t{17}; // error
T t = false; // ok
T t{true}; // ok
```


## Trying the Examples

There is a `Makefile` here. It works with both BSD and GNU Make. This will
compile all the examples that **can** compile, and also try to compile
the ones that do not.


### Example 0, Example 1

This is the unmodified example from above. It builds, and displays "ON", "ON", "OFF",
with an exit code of 0. It builds with all warnings enabled, too.

### Example 2

Just replacing `int` with `bool` does not help: the rest of the code does not
need to change, and so we are left with all the undesirable `int`-to-`bool`
conversions.

### Example 3

We introduce a `struct strong_bool` that just wraps a single bool. We use this
type instead of `int` or `bool` in the `Example` class. I have added four
variable declarations as well, with `strong_bool var` and some initialization.
I want two of the initializations to fail, and two to succeed.

Compiling this with Clang yields 8 sort-of-meaningful error messages.
Six of them are the ones I want, but it also fails on `strong_bool d = false;`,
which is something I **do** want to work.

### Example 4

Let's give the `struct` some stronger behavioral guarantees. We can turn it into
a class (so there is no access to the inner `bool b` anymore, and provide
it with:

- a constructor, so that it can be created from a bool
- a boolean-conversion operator, so it can work as a bool in some contexts.

```
class strong_bool
{
    bool b = false;
public:
    strong_bool() = default;
    strong_bool(bool v) : b(v) {}
    explicit operator bool() const { return b; }
};
```

Unfortunately, now everything compiles again because `int` can convert to `bool` (the
non-strong type) and then the constructor taking a `bool` is applicable. So no warnings,
but that is not what we want. We have gone too far the other way.

### Example 5

Templates to the rescue. It is possible to **delete** overloads of member functions,
including constructors, so we're going to delete all of them except for the one
taking `bool`. THe trick here is that the template matches first, so passing
an int, or a pointer, or whatever, matches that type first -- and that overload is deleted.

```
    template<typename T> strong_bool(T v) = delete;
    template<> strong_bool(bool v) : b(v) {};
```

In this example, I've added some more initializations to show that other types
are not accepted, but that it is still possible to copy or assign `strong_bool`
values.

### Example 6

Using the new templated version of `strong_bool`, we can convert the example class
to use it. Each use of an int or integer constant where we really meant a `bool`
value is flagged by the compiler, so we can use those as a guide and end up
with this:

```
class Example {
public:
    Example() = default;
    void SetIt(bool v) { m_toggle = v; }
    void ToggleIt() { if (m_toggle) { m_toggle = false; } else { m_toggle = true; } }
    const char * Status() { if (m_toggle) return "ON"; else return "OFF"; }
private:
    strong_bool m_toggle = false;
};
```

All's well, right? Well, almost: that `bool` in the `SetIt()` method is a not-so-strong
`bool`, so everything converts to it by following the standard rules. A call `SetIt(3)` is just
fine (the `3` converts to `true`, and in the `SetIt()` function we're assigning that `bool` value
to the `strong_bool`). In other words,
we have the **internal** use of the booleans repaired, but not the **external** API.

Switching the API type so that `SetIt()` also takes a `strong_bool` might not be
possible, depending on the API stability guarantees given by the codebase.

## What About Performance?

This struct has the same size and alignment properties as a `bool`. It has size 1 (at least
when compiled with Clang). With just about any optimizations enabled, the compiler
can turn all reads and writes to the "inner" `bool b` into just that: writes to that
value. The example program (e.g. Example 6) is optimized to call `puts()` three times,
since the compiler can figure out what value `b` has anyway, and there is no need
to keep the `strong_bool` or anything else around.

You don't pay for what you don't use, but here you get type safety for free!
