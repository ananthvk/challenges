#include <stdio.h>
// Max level of nesting is 5000
#define MAX_STACK_SIZE 5000
enum State {
    PROGRAM,
    STRING,
    STR_ESC,
    CHAR,
    CHAR_ESC,
    SINGLE_COMMENT,
    SINGLE_COMMENT_PARTIAL
    // NOTE: I am not handling comments and their related check in this program
    // As it requires me to combine the previous program, detect comment and do
    // other things.
    // So this program is not in full generality.
    // Also this program does not check the length of char.
    //    COMMENT
    // )
    // Implemented feature for ignoring parenthesis in single line comments.
    // NOTE: The program reports no error even if the above line (with a ) ) is
    // uncommented.
};
char stack[MAX_STACK_SIZE];
int stackPtr = -1;
enum State state = PROGRAM;

int main()
{
    int ch;
    int l = 1;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') l++;
        switch (state) {
            case PROGRAM:
                if (ch == '"') {
                    state = STRING;
                    break;
                }
                else if (ch == '\'') {
                    state = CHAR;
                    break;
                }
                else if (ch == '/') {
                    state = SINGLE_COMMENT_PARTIAL;
                }
                else if (ch == '{' || ch == '(' || ch == '[') {
                    if (stackPtr >= (MAX_STACK_SIZE - 1)) {
                        printf("%s\n",
                               "Maximum nesting level supported by the program "
                               "exceeded");
                        return -1;
                    }
                    stack[++stackPtr] = (char)ch;
                }
                else if (ch == '}' || ch == ')' || ch == ']') {
                    if (stackPtr < 0) {
                        printf("Line %d: Syntax error - Unmatched '%c'\n", l,
                               ch);
                    }
                    else {
                        if ((stack[stackPtr] == '[' && ch == ']') ||
                            (stack[stackPtr] == '{' && ch == '}') ||
                            (stack[stackPtr] == '(' && ch == ')')) {
                            // The braces match.
                            stackPtr -= 1;
                        }
                        else {
                            printf(
                                "Line %d: Syntax error - Opening parenthesis "
                                "'%c' does not match closing parenthesis "
                                "'%c'\n",
                                l, stack[stackPtr], ch);
                        }
                    }
                }
                break;
            case STRING:
                if (ch == '\\') {
                    state = STR_ESC;
                }
                else if (ch == '"') {
                    state = PROGRAM;
                }
                else if (ch == '\n') {
                    printf("Line %d: Unterminated string\n", l);
                    state = PROGRAM;
                }
                break;
            case STR_ESC:
                state = STRING;
                break;

            case CHAR:
                if (ch == '\\') {
                    state = CHAR_ESC;
                }
                else if (ch == '\'') {
                    state = PROGRAM;
                }
                else if (ch == '\n') {
                    printf("Line %d: Unterminated character\n", l);
                    state = PROGRAM;
                }
                break;
            case CHAR_ESC:
                state = CHAR;
                break;

            case SINGLE_COMMENT:
                if (ch == '\n') {
                    state = PROGRAM;
                }
                break;
            case SINGLE_COMMENT_PARTIAL:
                if (ch == '/') {
                    state = SINGLE_COMMENT;
                }
                else {
                    state = PROGRAM;
                }
                break;
            default:
                printf("<<<<<<%s>>>>>>\n", "SERIOUS ERROR - NO SUCH STATE");
                return -1;
        }
    }
    if (stackPtr > 0) {
        printf("Syntax error - %s \n", "Unmatched parenthesis");
    }
    else {
        printf("No errors:%d\n", stackPtr);
    }
}
// Test Case #1
/** (){}
 * ()()()
 * ()()()[][][]
 * ()()(){[][][]}
 * ()[][][] */
