#ifndef _RE_C
#define _RE_C

#include <stddef.h>

// automata state of the running regexp test
typedef struct state {
    const char *t; // pointer to currently processing symbol
    const char *exp; // pointer to current regular expression symbol
    bool matched; // if match being found
} state;

// shorthand for simplier function call
#define match(t_ptr, exp_ptr) next((state){.t = t_ptr, .exp = exp_ptr, .matched = false})

// function to build next machine state from the previous one
state next(state st);

typedef struct slice {
    const char* ptr;
    size_t len;
} slice;

// traverse through given input t and returns the first
// occurence of the matched text as a slice structure (without additional memory allocation)
// function keeps it's state statically, so every next call will return next occurence
slice yield(const char* t, const char* exp, bool reset);

// function returns copy of the next matched substring
// so it's need to be freed afterwards
char* leftmost(const char* t, const char* exp);

#endif