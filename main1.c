#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef enum Term_C {
    NONE,
    ZERO_OR_MANY = '*',
    ZERO_OR_ONE = '?',
    ONE_OR_MANY = '+'
} Term_C;

typedef enum Type {
    LITERAL,
    CLASS,
    GROUP
} Type;

// sequence of regex consists of actual matching pattern
// (like literal characters or class of symbols)
// possibly followed by modifier like '*', '.' or '?'
// seq := pattern | mod
// pattern can be recursively parsed to some sequence as well
// pattern := seq | _
typedef struct seq {
    char* exp;
    Term_C term;
    Type t;
} seq;

// parsing regular expression into seq structure
seq parse(char* p) {
    #define is_terminal(c) (c == '*' || c == '?' || c == '+')

    char* start = p;

    while (p && !is_terminal(*p)) {
        p++;
    }

    seq res = {
        .exp = malloc(p - start),
        .term = *(p - 1),
        .t = LITERAL
    };

    memcpy(res.exp, start, p - start);

    return res;
}

// function tests if sequence s matches text t
// based on sequence type
bool seq_match(char* t, const seq *s) {
    switch (s->t) {
        case LITERAL: {
            if ()
        }
    }
}

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
    if (regexp[0] == '^')
        return matchhere(regexp+1, text);
    do {    /* must look even if string is empty */
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
    do {    /* a * matches zero or more instances */
        if (matchhere(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp + 2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return matchhere(regexp+1, text+1);
    return 0;
}

bool match(const char* t, const char *re){char* seq_start = re;
    
    switch (*re) {
        // any non-special symbol
        default: (
            if (*t != *re)
                return false;
            else ()
        )
    }
}

int main(int argc, char* argv[]) {
    assert(match("abc", "abc") == true);
    assert(match(".*", "abc") == true);

    return 0;
}