#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>
#include <re.h>

// function to build next machine state from the previous one
state next(state st) {
    #define IS_SYM_EQ (*(st.exp) == '.' || *(st.t) == *(st.exp))
    #define IS_FIN (!*(st.exp) || !*(st.t))
    
    // actually parsing regular expression
    // zero or more occurencies (greedy)
    if (st.exp[1] == '*') {
        while (IS_SYM_EQ)
            st.t++;
        return match(st.t, st.exp + 2);
    }

    // one or more occurencies (greedy)
    if (st.exp[1] == '+') {
        if (!IS_SYM_EQ) {
            st.matched = false;
            return st;
        }

        while (IS_SYM_EQ) 
            st.t++;
        return match(st.t, st.exp + 2);
    }

    // zero or one occurence (lazy)
    if (st.exp[1] == '?') {
        // if (st.exp[2] == '?') { // greedy form
        //     return match(st.t + 1, st.exp + 2);
        // }
        // else {
        //     st.matched = true;
        //     return st;
        // }
        st.matched = true;
            return st;
    }

    // is it over
    if (IS_FIN) {
        st.matched = true;
        return st;
    }

    if (IS_SYM_EQ)
        return match(st.t + 1, st.exp + 1);

    return st;
}

// traverse through given input t and returns the first
// occurence of the matched text as a slice structure (without additional memory allocation)
// function keeps it's state statically, so every next call will return next occurence
slice yield(const char* t, const char* exp, bool reset) {
    static state last = (state) {.exp = NULL, .t = NULL, .matched = false};
    slice res = {
        .ptr = NULL,
        .len = 0
    };

    if (reset || !last.t) {
        last = (state) {.t = t, .exp = exp, .matched = false};
    }
    
    state curr = next(last);
    
    if (curr.matched) {
        res.ptr = last.t;
        res.len = curr.t - last.t;
    }

    last = curr;

    return res;
}

// function returns copy of the next matched substring
// so it's need to be freed afterwards
char* leftmost(const char* t, const char* exp) {
    static char* last_checked = NULL;
    bool reset = false;
    
    if (last_checked != t) {
        last_checked = t;
        reset = true;
    }

    char *res = NULL;
    slice s = yield(t, exp, reset);
    
    if (s.ptr) {
        res = malloc((s.len + 1) * sizeof(char));
        memcpy(res, s.ptr, s.len);
        res[s.len] = '\0';
    }

    return res;
}