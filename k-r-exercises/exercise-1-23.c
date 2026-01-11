#include <stdio.h>
/*
 * My implementation of Decomment uses a state machine.
 */


enum State {
    SEARCH,
    SEMI_COMMENT,
    CHAR,
    STR,
    SINGLE_LINE,
    MULTI_LINE,
    MULTI_LINE_SEMI,
    STR_ESC,
    CHAR_ESC,
};

enum State state = SEARCH;

void processChar(int ch)
{
    switch (state) {
        case SEARCH:
            switch (ch) {
                case '/':
                    state = SEMI_COMMENT;
                    break;
                case '"':
                    putchar('"');
                    state = STR;
                    break;
                case '\'':
                    putchar('\'');
                    state = CHAR;
                    break;
                default:
                    putchar(ch);
                    break;
            }
            break;

        case SEMI_COMMENT:
            switch (ch) {
                case '/':
                    state = SINGLE_LINE;
                    break;
                case '*':
                    state = MULTI_LINE;
                    break;
                default:
                    putchar('/');
                    putchar(ch);
                    state = SEARCH;
                    break;
            }
            break;

        case SINGLE_LINE:
            switch (ch) {
                case '\n':
                    putchar('\n');
                    state = SEARCH;
                    break;
                default:
                    state = SINGLE_LINE;
                    break;
            }
            break;

        case MULTI_LINE:
            switch (ch) {
                case '*':
                    state = MULTI_LINE_SEMI;
                    break;
            }
            break;

        case MULTI_LINE_SEMI:
            switch (ch) {
                case '/':
                    state = SEARCH;
                    break;
                default:
                    state = MULTI_LINE;
                    break;
            }
            break;

        case STR:
            switch (ch) {
                case '\\':
                    state = STR_ESC;
                    break;
                case '"':
                    putchar('"');
                    state = SEARCH;
                    break;
                default:
                    putchar(ch);
                    break;
            }
            break;

        case STR_ESC:
            putchar('\\');
            putchar(ch);
            state = STR;
            break;

        case CHAR:
            switch (ch) {
                case '\\':
                    state = CHAR_ESC;
                    break;
                case '\'':
                    putchar('\'');
                    state = SEARCH;
                    break;
                default:
                    putchar(ch);
                    break;
            }
            break;

        case CHAR_ESC:
            putchar('\\');
            putchar(ch);
            state = CHAR;
            break;
    }
}

int main()
{
    int ch;
    while ((ch = getchar()) != EOF) {
        processChar(ch);
    }
}
