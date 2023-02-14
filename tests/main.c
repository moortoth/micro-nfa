#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>
#include "../re.h"

#define assert_str_h(a, b) assert(!strcmp(a, b)); free(a)

void assert_seq(char* s, char* re, int l, char* seq[l]) {
    for (int i = 0; i < l; ++i) {
        char* lm = leftmost(s, re);
        assert_str_h(lm, seq[i]);
    }
}

int main(int argc, char* argv[]) {
    assert(match("abc", "abc").matched);
    assert(!match("abc", "d").matched);
    assert(match("aaaa", "a*").matched);
    assert(match("bbbb", "b+").matched);
    assert(!match("c", "b+").matched);

    assert_str_h(leftmost("abc", "a"), "a");

    assert_seq("aabc", "a", 2, (char* []){"a", "a"});

    return 0;
}