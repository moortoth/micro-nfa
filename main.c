#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

bool match(const char* t, const char *exp) {
    // zero or more
    if (exp[1] == '*') {
        while (*t == *exp) t++;
        return match(t, exp + 2);
    }

    // one or more
    if (exp[1] == '+') {
        if (*t != *exp) return false;
        while (*t == *exp) t++;
        return match(t, exp + 2);
    }

    // zero or one
    // if (exp[1] == '?') {
        
    // }

    if (!(*exp) || !(*t)) 
        return true;

    if (*exp == '.' || *t == *exp)
        return match(t + 1, exp + 1);

    return false;
}

typedef struct slice {
    char* ptr;
    size_t len;
} slice;

// returns 
slice next_match(const char* t, const char* exp, bool reset) {
    static char* last = NULL;
    slice res = {
        .ptr = NULL,
        .len = 0
    };

    if (reset || last == NULL);
    char* curr = last;
    if (match(curr, exp)) {
        res.ptr = t,
        res.len = curr - last;
        curr = last;
    }

    return res;
}

int main(int argc, char* argv[]) {
    assert(match("abc", "abc"));
    assert(!match("abc", "d"));
    assert(match("aaaa", "a*"));
    assert(match("bbbb", "b+"));
    assert(!match("c", "b+"));

    return 0;
}