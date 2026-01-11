/*
 * Implementation of a Reverse Polish Notation Calculator.
 * This file has all the exercises from exercise 4-3 to exercise 4-10
 * The book separates the functions into many files, but because I have kept a
 * single file per exercise, I'm doing everything here.
 */

/*
 * Algorithm
 * ==========
 * WHILE the next token is not EOF
 *      IF token type is NUMBER
 *          PUSH into STACK
 *      IF token type is OPERATOR
 *          POP operands and perform operation based on operator.
 *          PUSH result into STACK
 *      IF token type is NEWLINE
 *          POP and return the result.
 */
/*
 * CHANGES wrt to the book
 * 1) I have made the a function, which returns the result instead of directly
 * finding the result from stdin. 2) This allows me to test the code. 3) No
 * getch and ungetch as the program takes a char array as argument.
 */
/*
 * NOTE:
 * For assignment statements, I have used infix notation instead of RPN because
 * it is much easier to implement For example a b 1 + = --> Should be
 * interpreted as a = b + 1 Which is more complex as the program will not know
 * whether the value of a should be set or used.
 * One workaround is to use a token stack, where instead of just storing the
 * values, The program will store the tokens and then decide whether to set or
 * use the value.
 */
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum OPType {
    OP_SIN,
    OP_COS,
    OP_TAN,
    OP_COT,
    OP_EXP,
    OP_POW,
    OP_LOG,
    OP_LOG10,
    OP_LOGN,
    OP_ABS,
    OP_CEIL,
    OP_FLOOR,
    OP_SQRT,
    OP_FACTORIAL,
    OP_MOD,
    OP_BIT_NOT
} OPType;
typedef enum TokenType {
    NUMBER,
    IDENTIFIER,
    // Operators
    PLUS,
    MINUS,
    FORWARD_SLASH,
    STAR,
    MODULUS,
    EXCLAMATION,
    ASSIGNMENT,
    BIT_LSHIFT,  // <<
    BIT_RSHIFT,  // >>
    BIT_AND,     // &
    BIT_OR,      // |
    BIT_NOT,     /// ~
    BIT_XOR,     // ^

    DEBUG_CHAR,  // Temporary Send @ to toggle debug mode

    END_OF_FILE,
    NEWLINE,
    UNKNOWN
} TokenType;

typedef struct Token {
    TokenType type;  // Type of the token
    char* src;       // Pointer to the string which contains the token
    int index;       // Position of token
    int length;      // Length of the token.
} Token;

// GLOBAL Variables here
// ===================================
#define MAX_OPERANDS 1024
#define BUFFER_SIZE 512
#define RADIAN 1
#define DEGREE 2
#define VERSION "1.0.0"
double op_stack[MAX_OPERANDS] = {0}; /* Stack to store the operands */
int sp = -1;                         /* Stack index */
int cp = 0; /* Character index which is the index of the current character to be
               considered*/
char src_string[BUFFER_SIZE] = {'\0'};
char buffer[512] = {'\0'};
/* Temporary buffer to store numbers, to convert them */
// Some config options
int TOKEN_DEBUG_ENABLED = 1; /* Whether to print token details or not */
int err_occured = 0;
int stack_shown = 1;
int show_errors = 1;
int display_prompt = 1;
int clear_screen = 1;
int angle_measure = RADIAN;
int running = 1;
// Only uppercase variables are supported as some math constants are in
// lowercase Add a variable lookup table for 26 variables

double variable_lookup[26] = {0};
int variables_set[26] = {0};
char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// ===================================
// Functions for safely handling the source string
// by including length checks
// These functions consider a null char at the end of src_string, i.e. at index
// BUFFER_SIZE -1 So they check if the index is less than BUFFER_SIZE - 1
//
// Functions
// ===============
// Functions for the operand stack
double valueAt(int n);
int pop(double* var);
int peek(double* var);
int push(double var);
void displayStack();

// Functions for handling the expression string.
char peekChar();
char peekNextChar();
char charAt(int n);
char getChar();
void setChar(char c);

// Function for handling unary, binary and functions
void unaryop(OPType type);
void binaryfunc(OPType type);
void binop(char op);

// Functions related to tokens
Token processIdentifier();
Token processNumber();
void consumeNumber();
Token getNextToken();
void displayToken(Token t);

// Helper functions
long int factorial(int n);
void reset();
int getline_(char buffer_[], int bufferSize);
void clearScreen();
void printHelpMessage();
void displayMemory();

// Main functions
void calculate();
int main();

// Functions to handle configuration of display
void enableDisplay()
{
    stack_shown = 1;
    show_errors = 1;
    display_prompt = 1;
}
void disableDisplay()
{
    stack_shown = 0;
    show_errors = 0;
    display_prompt = 0;
}

void printHelpMessage()
{
    printf("%s %s\n",
           "Welcome to Shankar's RPN (Reverse polish notation) Calculator",
           VERSION);
    printf("%s%s\n", "Version: ", VERSION);
    printf("Max supported length of a single line of input: %d\n", BUFFER_SIZE);
    printf("Max number of operands supported: %d\n", MAX_OPERANDS);
    printf("\n");

    printf("Enter the expression through standard input\n");
    printf("Type \"help\" and press enter to get this help message\n");
    printf("%s\n", "Type @ and press enter to toggle debug mode");
    printf("%s\n", "============================");
    printf("Operators\n");
    printf("%s\n", "============================");
    printf("%-16s%s\n", "+", "Add two numbers and push result on stack");
    printf("%-16s%s\n", "-",
           "Subtract two numbers and push result on the stack");
    printf("%-16s%s\n", "*",
           "Multiply two numbers and push result on the stack");
    printf("%-16s%s\n", "/", "Divide two numbers and push result on the stack");
    printf("%-16s%s\n", "%",
           "Find the modulus of two numbers and push result on stack");
    printf("%-16s%s\n", "&", "Bitwise AND");
    printf("%-16s%s\n", "|", "Bitwise OR");
    printf("%-16s%s\n", "~", "Bitwise NOT");
    printf("%-16s%s\n", "^", "Bitwise XOR");
    printf("%-16s%s\n", ">>", "Right shift");
    printf("%-16s%s\n", "<<", "Left shift");
    // printf("%-16s%s\n", "", "");
    printf("\n");
    printf("Mathematical functions\n");
    printf("%s\n", "============================");
    printf("%-16s%s\n", "sin", "Finds the sine of the number");
    printf("%-16s%s\n", "cos",
           "Finds the cosine the of top number of the stack");
    printf("%-16s%s\n", "tan", "Finds the tan of a number");
    printf("%-16s%s\n", "cot", "Finds the cot of a number");
    printf("%-16s%s\n", "exp", "Finds the exp of a number");
    printf("%-16s%s\n", "pow",
           "Finds the value of a raised to b, Example: a b pow");
    printf("%-16s%s\n", "log", "Finds the log of a number, Example: a log");
    printf("%-16s%s\n", "log10",
           "Finds the log to base 10 of a number, Example a log10");
    printf("%-16s%s\n", "logn",
           "Finds the log to base n of a number, Example a b logn is "
           "equivalent to log to base b, a");
    printf("%-16s%s\n", "abs", "Finds the aboslute value of a number");
    printf("%-16s%s\n", "ceil", "Finds the ceil value of a a number");
    printf("%-16s%s\n", "floor", "Finds the floor value of a a number");
    printf("%-16s%s\n", "sqrt", "Finds the square root of a a number");
    printf("%-16s%s\n", "mod",
           "Finds the remainder, Example a b mod is equivalent to a % b");
    printf("\n");
    printf("Mathematical constants\n");
    printf("%s\n", "============================");
    printf("%-16s%s\n", "e",
           "Pushes the value of e, Euler's number 2.718... on the stack");
    printf("%-16s%s\n", "pi", "Pushes the value of Pi 3.1415.... on the stack");
    printf("\n");
    printf("Commands\n");
    printf("%s\n", "============================");
    printf("%-16s%s\n", "deg",
           "Sets the program to use degrees for angle measure");
    printf("%-16s%s\n", "rad",
           "Sets the program to use radian for angle measure");
    printf("%-16s%s\n", "exit", "Exits the rpn interactive prompt");
    printf("%-16s%s\n", "quit", "Same as exit, quits the rpn calculator");
    printf("%-16s%s\n", "help", "Prints this help message");
    printf("%-16s%s\n", "dup",
           "Duplicates the element at the top of the stack");
    printf("%-16s%s\n", "peek | print",
           "Prints the value of the top of the stack");
    printf("%-16s%s\n", "pop", "Remove the topmost element from the stack");
    printf("%-16s%s\n", "swap", "Swaps the two topmost elements");
    printf("%-16s%s\n", "mem", "Displays the memory of the calculator");
    printf("%-16s%s\n", "sum", "Finds the sum of all elements of the stack");
    printf("%-16s%s\n", "prod",
           "Finds the product of all elements of the stack");
    printf("%-16s%s\n", "clear", "Clears the stack");
    printf("%-16s%s\n", "clrtop",
           "Clears all elements of stack except top element");
    printf("%-16s%s\n", "clearmem", "Clears the memory of the calculator");
    printf("%-16s%s\n", "show_stack", "Displays stack after every calculation");
    printf("%-16s%s\n", "no_show_stack", "Disables display of stack");
    printf("%-16s%s\n", "debug", "Enables debug mode");
    printf("%-16s%s\n", "no_debug", "Disables debug mode");
    printf("%-16s%s\n", "show_errors", "Displays error (if any)");
    printf("%-16s%s\n", "no_show_errors", "Suppress display of errors");
    printf("%-16s%s\n", "display_prompt", "Displays the >> Before input");
    printf("%-16s%s\n", "no_display_prompt", "Disables display of prompt(>>)");
    printf("%-16s%s\n", "clear_screen", "Clears the screen after every input");
    printf("%-16s%s\n", "no_clear_screen",
           "Disables clearing screen after input");
    printf("%-16s%s\n", "display",
           "Enables display of all information (except debug)\n");
    printf("%-16s%s\n", "no_display",
           "Disables display of all information (except debug)\n");

    printf("\n");
    printf(
        "Sample list of commands when this program's output is used by another "
        "program\n");
    printf(
        "no_debug no_show_errors no_show_stack no_clear_screen "
        "no_display_prompt <expression> pop\n");
    /* printf("%-16s%s\n", "", "");
     * printf("%-16s%s\n", "", ""); */
    printf("\n");
    printf("Variables\n");
    printf("%s\n", "============================");
    printf(
        "This RPN calculator supports variables, you can use variables in any "
        "expression\n");
    printf("Variable names must be single letter long and in uppercase only\n");
    printf("Syntax for setting a variable:\n");
    printf("set <variable_name> = <expression>\n");
    printf("Examples:\n");
    printf("set A = 3 2 +\n");
    printf("The above example sets A to 5\n");
    printf(
        "NOTE: If the expression part is omitted, then the topmost element of "
        "the stack is popped and the variable is set to that value\n");
    printf("Example:\n");
    printf(">> 3 2\n");
    printf(">> set A = \n");
    printf("This sets A to 2 and 2 is removed from the stack\n");
    printf(
        "If the expression part is omitted and the stack is empty, the "
        "variable will assume the value of 0\n");
    // printf("\n");
    // printf("%-16s%s\n", "", "");
    // printf("%-16s%s\n", "", "");
}
char peekChar()
{
    // Gets the character at index cp without incrementing cp.
    if ((cp >= (BUFFER_SIZE - 1)) || (cp < 0)) {
        // Returns null character if the string has finished processing.
        printf("====== WARNING ====== [%s] %d\n",
               "Out of bound access at peekChar()", cp);
        return '\0';
    }
    return src_string[cp];
}

long int factorial(int n)
{
    int f = 1;
    for (int j = 1; j <= n; j++) f = f * j;
    return f;
}

void clearScreen()
{
    // I couldn't find a proper way of clearing the console
    // (especially for displaying the stack)
    // So this method is slightly portable and works in *nix and windows
    system("cls||clear");
}

void displayStack()
{
    printf("%s\n", "============================");
    for (int k = 0; k <= sp; k++) {
        printf("[%d: ", k);
        // printf("%.*g ", DBL_DECIMAL_DIG, valueAt(k));
        // I am not using DBL_DECIMAL_DIG, as it prints 1.4999999... for 1.5
        printf("%.15g ", valueAt(k));
        printf("%s", " ]\n");
    }
}
void displayMemory()
{
    // printf("%s\n", "============================");
    printf("MEMORY: [");
    for (int i = 0; i < 26; i++) {
        if (variables_set[i]) {
            printf("%c: %.15g ", alphabets[i], variable_lookup[i]);
        }
    }
    printf("]\n");
}

char peekNextChar()
{
    // Gets the next character at index cp+1, without incrementing.
    if (((cp + 1) >= (BUFFER_SIZE - 1)) || ((cp + 1) < 0)) {
        // Returns null character if the string has finished processing.
        printf("====== WARNING ====== [%s] %d\n",
               "Out of bound access at peekNextChar()", cp + 1);
        return '\0';
    }
    return src_string[cp + 1];
}

double valueAt(int n)
{
    // Gets the character at the given index
    if ((n >= MAX_OPERANDS) || (n < 0)) {
        printf("====== WARNING ====== [%s] %d\n",
               "Out of bound access at valueAt()", n);
        return '\0';
    }
    return op_stack[n];
}

char charAt(int n)
{
    // Gets the operand at the given index from the stack
    if (((n) >= (BUFFER_SIZE - 1)) || ((n) < 0)) {
        // Returns null character if the string has finished processing.
        printf("====== WARNING ====== [%s] %d\n",
               "Out of bound access at charAt()", n);
        return '\0';
    }
    return src_string[n];
}

char getChar()
{
    // Gets the character at index cp and also increments cp.
    char c = peekChar();
    cp++;
    return c;
}

void setChar(char c)
{
    if ((cp >= (BUFFER_SIZE - 1)) || (cp < 0)) {
        printf("Fatal error: Array index out of bounds %d", cp);
        err_occured = 1;
        return;
    }
    src_string[cp] = c;
}
// ===================================
int pop(double* var)
{
    /*
     * Function which pops an element from the stack and sets the passed element
     * to that value. If the stack is empty, 0 will be returned
     */
    if (sp < 0) {
        if (var) *var = 0;
        return 0;
    }
    else {
        if (var) *var = op_stack[sp--];
        return 1;
    }
}

int peek(double* var)
{
    /*
     * Function which peeks an element from the stack and sets the passed
     * element to that value. If the stack is empty, 0 will be returned
     */
    if (sp < 0) {
        if (var) *var = 0;
        return 0;
    }
    else {
        if (var) *var = op_stack[sp];
        return 1;
    }
}

int push(double var)
{
    /*
     * Function which pushes an element to the stack
     * If the stack is full, 0 will be returned and 1 in case of success
     */
    if (sp == (MAX_OPERANDS - 1)) {
        if (TOKEN_DEBUG_ENABLED)
            printf("%s\n", "[WARNING: Operator stack is full]");
        return 0;
    }
    else {
        op_stack[++sp] = var;
        return 1;
    }
}

void consumeNumber()
{
    // Increments cp until the character at that index is not a number.
    while (isdigit(peekChar())) {
        cp++;
    }
}

Token processIdentifier()
{
    int tmp = cp;
    if (peekChar() == '_') cp++;
    while (isalnum(peekChar()) || peekChar() == '_') {
        cp++;
    }
    return (Token){IDENTIFIER, src_string, tmp, cp - tmp};
}

Token processNumber()
{
    // Tries to find a number from the index cp in src_string
    // At the first non numeric character(except dot), the function returns.
    int tmp = cp;
    if (peekChar() == '-') {
        // Negative number
        cp++;
    }

    consumeNumber();

    if (peekChar() == '.') {
        // Decimal number
        cp++;
        consumeNumber();
    }
    if (peekChar() == 'e' || peekChar() == 'e') {
        // Exponential notation.
        cp++;
        consumeNumber();
        // Handle negative number of exponents
        if (peekChar() == '-') {
            cp++;
            consumeNumber();
        }
    }
    // cp - tmp is the length of the token.
    return (Token){NUMBER, src_string, tmp, cp - tmp};
}

Token getNextToken()
{
    // This function works like a lexer, it takes the input string and returns
    // tokens.
    if (cp == -1) return (Token){END_OF_FILE, src_string, cp, 0};

    while (peekChar() != '\0') {
        // Ignore whitespaces and tabs
        if (peekChar() == ' ' || peekChar() == '\t') {
            cp++;
            continue;
        }

        // Debug char
        if (peekChar() == '@') {
            TOKEN_DEBUG_ENABLED = TOKEN_DEBUG_ENABLED ? 0 : 1;
            cp++;
            continue;
        }
        // Single character tokens
        if (peekChar() == '*') return (Token){STAR, src_string, cp++, 1};
        if (peekChar() == '/')
            return (Token){FORWARD_SLASH, src_string, cp++, 1};
        if (peekChar() == '+') return (Token){PLUS, src_string, cp++, 1};
        if (peekChar() == '%') return (Token){MODULUS, src_string, cp++, 1};
        if (peekChar() == '!') return (Token){EXCLAMATION, src_string, cp++, 1};
        if (peekChar() == '=') return (Token){ASSIGNMENT, src_string, cp++, 1};

        if (peekChar() == '&') return (Token){BIT_AND, src_string, cp++, 1};
        if (peekChar() == '|') return (Token){BIT_OR, src_string, cp++, 1};
        if (peekChar() == '~') return (Token){BIT_NOT, src_string, cp++, 1};
        if (peekChar() == '^') return (Token){BIT_XOR, src_string, cp++, 1};

        if (peekChar() == '>' && peekNextChar() == '>')
            return (Token){BIT_RSHIFT, src_string, cp++, 1};
        if (peekChar() == '<' && peekNextChar() == '<')
            return (Token){BIT_LSHIFT, src_string, cp++, 1};
        if (peekChar() == '-') {
            if (isdigit(peekNextChar())) {
                // If the next character after minus is a digit
                // It is a negative number
                return processNumber();
            }
            else {
                return (Token){MINUS, src_string, cp++, 1};
            }
        }
        if (peekChar() == '\n') return (Token){NEWLINE, src_string, cp++, 1};

        // Multi character tokens like numbers or variables
        else {
            // Handle numbers
            if (isdigit(peekChar())) {
                return processNumber();
            }
            // Handle identifers
            // Identifier is defined as a sequence of alphanumeric characters
            // starting with underscore or an alphabet
            if (isalpha(peekChar()) || peekChar() == '_') {
                return processIdentifier();
            }
            return (Token){UNKNOWN, src_string, cp++, 1};
        }
    }
    cp = -1;
    return (Token){END_OF_FILE, src_string, cp, 0};
}

void reset()
{
    // Resets all variables to initial state
    // Reset stack pointer if you want to clear the state
    // I want the elements of the stack to remain
    sp = -1;
    cp = 0;
    memset(src_string, 0, sizeof(src_string));
    err_occured = 0;
}

void displayToken(Token t)
{
    putchar('<');
    switch (t.type) {
        // I know, this is ugly, but I dont want to do dynamic memory
        // allocation.
        case NUMBER:
            printf("%s", "NUMBER");
            break;
        case IDENTIFIER:
            printf("%s", "IDENTIFIER");
            break;
        case PLUS:
            printf("%s", "PLUS");
            break;
        case MINUS:
            printf("%s", "MINUS");
            break;
        case FORWARD_SLASH:
            printf("%s", "SLASH");
            break;
        case STAR:
            printf("%s", "STAR");
            break;
        case MODULUS:
            printf("%s", "MODULUS");
            break;
        case EXCLAMATION:
            printf("%s", "EXCLAMATION");
            break;
        case ASSIGNMENT:
            printf("%s", "ASSIGNMENT");
            break;
        case END_OF_FILE:
            printf("%s>\n", "EOF");
            // Returns for EOF as it is not printable
            return;
        case NEWLINE:
            printf("%s>\n", "EOL");
            // Returns for EOF as it is not printable
            return;
        case UNKNOWN:
            printf("%s", "UKNWN");
            break;
        default:
            printf("%s", "*UKNWN");
            break;
    }
    // Add a space
    putchar(' ');

    if (t.length == 1) {
        // Code for handling single character tokens only.
        printf("%c", t.src[t.index]);
    }
    else {
        for (int i = 0; i < t.length; i++) {
            assert((t.index + i) < (BUFFER_SIZE - 1));
            assert((t.index + i) >= 0);
            putchar(t.src[t.index + i]);
        }
    }

    putchar('>');
    putchar('\n');
}

void unaryop(OPType type)
{
    // Function to handle functions or operators which take a single operand
    // like sin, cos, etc.
    double rhs, result = 0;
    // Only for trigonometric functions
    if (!pop(&rhs)) {
        if (show_errors)
            printf(
                "ERROR: Not enough operands for the given function/operator\n");
        err_occured = 1;
        return;
    }
    double trig_rhs =
        (angle_measure == RADIAN) ? rhs : (3.1415926535 / 180) * rhs;
    switch (type) {
        case OP_SIN:
            result = sin(trig_rhs);
            break;
        case OP_COS:
            result = cos(trig_rhs);
            break;
        case OP_TAN:
            result = tan(trig_rhs);
            break;
        case OP_EXP:
            result = exp(trig_rhs);
            break;
        case OP_COT:
            result = cos(trig_rhs) / sin(trig_rhs);
            break;
        case OP_LOG:
            result = log(rhs);
            break;
        case OP_LOG10:
            result = log10(rhs);
            break;
        case OP_SQRT:
            if (rhs < 0) {
                if (show_errors)
                    printf("%s\n", "ERROR: Square root of negative number");
                err_occured = 1;
                push(rhs);
                return;
            }
            result = sqrt(rhs);
            break;
        case OP_ABS:
            result = fabs(rhs);
            break;
        case OP_CEIL:
            result = ceil(rhs);
            break;
        case OP_FLOOR:
            result = floor(rhs);
            break;
        case OP_FACTORIAL:
            result = (double)(factorial((int)rhs));
            break;
        case OP_BIT_NOT:
            result = ~(int)rhs;
            break;
        default:
            if (show_errors)
                printf("%s\n", "INTERNAL ERROR: Unknown unary operator");
            err_occured = 1;
            return;
    }
    if (!push(result)) {
        if (show_errors) printf("ERROR: %s\n", "Stack is full");
        err_occured = 1;
        return;
    }
}

void binaryfunc(OPType type)
{
    double result = 0, lhs, rhs;
    int rhs_success = 0;

    if (!pop(&rhs)) {
        if (show_errors)
            printf("ERROR: Not enough operands for function taking 2 args\n");
        err_occured = 1;
        return;
    }
    // If control has come here, it means that pop(&rhs) didn't fail
    rhs_success = 1;
    if (!pop(&lhs)) {
        if (rhs_success) push(rhs);
        if (show_errors)
            printf("ERROR: Not enough operands for function taking 2 args\n");
        err_occured = 1;
        return;
    }

    if (type == OP_POW) {
        result = pow(lhs, rhs);
    }
    if (type == OP_MOD) {
        result = fmod(lhs, rhs);
    }
    if (type == OP_LOGN) {
        result = log(lhs) / log(rhs);
    }
    if (!push(result)) {
        if (show_errors) printf("ERROR: %s\n", "Stack is full, Internal error");
        err_occured = 1;
        return;
    }
}

void binop(char op)
{
    // Function to handle operators which expect two operands such as +, - etc
    double result = 0, lhs, rhs;
    int rhs_success = 0;

    if (!pop(&rhs)) {
        if (show_errors)
            printf("ERROR: Not enough operands for operator '%c' (rhs)\n", op);
        err_occured = 1;
        return;
    }
    // If control has come here, it means that pop(&rhs) didn't fail
    rhs_success = 1;
    if (!pop(&lhs)) {
        // Suppose the input was 32 +
        // The program pops 32 and stores it in a variable
        // But it errors here as there is no lhs
        // So in this case, we have to push back that 32 (or whatever number)
        if (rhs_success) push(rhs);
        if (show_errors)
            printf("ERROR: Not enough operands for operator '%c' (lhs)\n", op);
        err_occured = 1;
        return;
    }

    switch (op) {
        case '+':
            result = lhs + rhs;
            break;
        case '-':
            result = lhs - rhs;
            break;
        case '*':
            result = lhs * rhs;
            break;
        // For these bitwise operators, the double is converted to int first
        case '&':
            result = (int)lhs & (int)rhs;
            break;
        case '|':
            result = (int)lhs | (int)rhs;
            break;
        case '^':
            result = (int)lhs ^ (int)rhs;
            break;
        case 'R':
            result = (int)lhs >> (int)rhs;
            break;
        case 'L':
            result = (int)lhs << (int)rhs;
            break;
        case '/':
            if (fabs(rhs) <= 1e-50) {
                if (show_errors) printf("%s\n", "ERROR: Division by zero");
                err_occured = 1;
                return;
            }
            else {
                result = lhs / rhs;
            }
            break;
        case '%':
            if (fabs(rhs) <= 1e-50) {
                if (show_errors) printf("%s\n", "ERROR: Modulus by zero");
                err_occured = 1;
                return;
            }
            else {
                // Using fmod instead of modulus operator because the all values
                // are represented as double.
                result = fmod(lhs, rhs);
            }
            break;

        default:
            if (show_errors) printf("ERROR: Unknown operator (%c) \n", op);
            err_occured = 1;
            break;
    }
    if (!push(result)) {
        if (show_errors) printf("ERROR: %s\n", "Stack is full, Internal error");
        err_occured = 1;
        return;
    }
}

void calculate()
{
    // Function calculates the value of the expression
    // Make sure to call reset() after calling this function
    // To reset the index variables and state
    Token t;
    int i;
    // var for temporary usage
    double var;
    do {
        if (err_occured) {
            // If any error had occured, do not continue scanning
            return;
        }
        t = getNextToken();
        if (t.type == UNKNOWN) {
            if (show_errors)
                printf("ERROR: Uknown character (%c) at index %d in input\n",
                       t.src[t.index], t.index);
            err_occured = 1;
            return;
        }
        else {
            switch (t.type) {
                case NUMBER:
                    for (i = 0; i < t.length; i++) {
                        assert((t.index + i) < (BUFFER_SIZE - 1));
                        assert((t.index + i) >= 0);
                        buffer[i] = t.src[t.index + i];
                    }
                    buffer[i] = '\0';
                    if (!push(atof(buffer))) {
                        if (show_errors)
                            printf("ERROR: %s\n",
                                   "Stack is full, Internal error");
                        err_occured = 1;
                        return;
                    }
                    break;
                case IDENTIFIER:
                    /* I removed all returns from the if statements and
                     * converted the if statements to else if. Using the return
                     * statements, I could not evaluate 2 sqrt floor Or the like
                     * of functions
                     */
                    // Copy to temporary buffer to do manipulations
                    for (i = 0; i < t.length; i++) {
                        assert((t.index + i) < (BUFFER_SIZE - 1));
                        assert((t.index + i) >= 0);
                        buffer[i] = t.src[t.index + i];
                    }
                    buffer[i] = '\0';

                    // Handle some variables such as e and pi
                    if (strcmp(buffer, "pi") == 0) {
                        if (!push(3.14159265358)) {
                            if (show_errors)
                                printf("ERROR: %s\n", "Stack is full");
                            err_occured = 1;
                            return;
                        }
                    }
                    else if (strcmp(buffer, "e") == 0) {
                        if (!push(2.71828182845))

                        {
                            if (show_errors)
                                printf("ERROR: %s\n", "Stack is full");
                            err_occured = 1;
                            return;
                        }
                    }

                    // Handle some commands
                    else if (strcmp(buffer, "exit") == 0 ||
                             strcmp(buffer, "quit") == 0) {
                        running = 0;
                    }
                    else if (strcmp(buffer, "help") == 0) {
                        printHelpMessage();
                    }
                    else if (strcmp(buffer, "dup") == 0) {
                        if (!peek(&var)) {
                            if (show_errors)
                                printf("%s\n",
                                       "ERROR: Unable to duplicate element as "
                                       "stack "
                                       "is empty");
                            err_occured = 1;
                            return;
                        }
                        if (!push(var)) {
                            if (show_errors)
                                printf("%s\n",
                                       "ERROR: Unable to duplicate element as "
                                       "stack is full");
                            err_occured = 1;
                            return;
                        }
                    }
                    else if (strcmp(buffer, "peek") == 0 ||
                             strcmp(buffer, "print") == 0) {
                        peek(&var);
                        printf("%.15g\n", var);
                    }
                    else if (strcmp(buffer, "pop") == 0) {
                        if (!pop(&var)) {
                            if (show_errors)
                                printf("%s\n",
                                       "ERROR: Unable to pop element as "
                                       "stack is empty");
                            err_occured = 1;
                            return;
                        }
                        printf("%.15g\n", var);
                    }
                    else if (strcmp(buffer, "rad") == 0) {
                        angle_measure = RADIAN;
                    }
                    else if (strcmp(buffer, "deg") == 0) {
                        angle_measure = DEGREE;
                    }
                    else if (strcmp(buffer, "show_stack") == 0) {
                        stack_shown = 1;
                    }
                    else if (strcmp(buffer, "no_show_stack") == 0) {
                        stack_shown = 0;
                    }
                    else if (strcmp(buffer, "clear_screen") == 0) {
                        clear_screen = 1;
                    }
                    else if (strcmp(buffer, "no_clear_screen") == 0) {
                        clear_screen = 0;
                    }
                    else if (strcmp(buffer, "display_prompt") == 0) {
                        display_prompt = 1;
                    }
                    else if (strcmp(buffer, "no_display_prompt") == 0) {
                        display_prompt = 0;
                    }
                    else if (strcmp(buffer, "debug") == 0) {
                        TOKEN_DEBUG_ENABLED = 1;
                    }
                    else if (strcmp(buffer, "no_debug") == 0) {
                        TOKEN_DEBUG_ENABLED = 0;
                    }
                    else if (strcmp(buffer, "show_errors") == 0) {
                        show_errors = 1;
                    }
                    else if (strcmp(buffer, "no_show_errors") == 0) {
                        show_errors = 0;
                    }
                    else if (strcmp(buffer, "display") == 0) {
                        // Enables display of everything
                        enableDisplay();
                    }
                    else if (strcmp(buffer, "no_display") == 0) {
                        disableDisplay();
                    }

                    else if (strcmp(buffer, "swap") == 0) {
                        // Stack: a b c d e f
                        // v1 = f
                        // v2 = e
                        // After pushing back again
                        // a b c f e
                        // The elements are swapped
                        double v1, v2;
                        int v1_success = 0;
                        if (!pop(&v1)) {
                            if (show_errors)
                                printf("%s\n",
                                       "ERROR: Unable to swap as "
                                       "there are not enough elements");
                            err_occured = 1;
                            return;
                        }
                        v1_success = 1;
                        if (!pop(&v2)) {
                            if (show_errors)
                                printf("%s\n",
                                       "ERROR: Unable to swap as "
                                       "there are not enough elements");
                            err_occured = 1;
                            if (v1_success) {
                                // One element has already been popped out.
                                // Push it back into the stack
                                push(v1);
                            }
                            return;
                        }
                        // No need to check if the stack is full because on
                        // calling pop() twice above, there will be 2 spaces
                        push(v1);
                        push(v2);
                    }
                    else if (strcmp(buffer, "clear") == 0) {
                        sp = -1;
                    }
                    else if (strcmp(buffer, "mem") == 0) {
                        displayMemory();
                    }
                    else if (strcmp(buffer, "clearmem") == 0) {
                        for (int j = 0; j < 26; j++) {
                            variable_lookup[j] = 0;  // Might not be necessary
                            variables_set[j] = 0;
                        }
                    }

                    // Handle math functions
                    else if (strcmp(buffer, "sin") == 0) {
                        unaryop(OP_SIN);
                    }
                    else if (strcmp(buffer, "cos") == 0) {
                        unaryop(OP_COS);
                    }
                    else if (strcmp(buffer, "tan") == 0) {
                        unaryop(OP_TAN);
                    }
                    else if (strcmp(buffer, "cot") == 0) {
                        unaryop(OP_COT);
                    }
                    else if (strcmp(buffer, "exp") == 0) {
                        unaryop(OP_EXP);
                    }

                    else if (strcmp(buffer, "log") == 0) {
                        unaryop(OP_LOG);
                    }
                    else if (strcmp(buffer, "log10") == 0) {
                        unaryop(OP_LOG10);
                    }
                    else if (strcmp(buffer, "abs") == 0) {
                        unaryop(OP_ABS);
                    }
                    else if (strcmp(buffer, "ceil") == 0) {
                        unaryop(OP_CEIL);
                    }
                    else if (strcmp(buffer, "floor") == 0) {
                        unaryop(OP_FLOOR);
                    }
                    else if (strcmp(buffer, "sqrt") == 0) {
                        unaryop(OP_SQRT);
                    }
                    else if (strcmp(buffer, "logn") == 0) {
                        binaryfunc(OP_LOGN);
                    }
                    else if (strcmp(buffer, "mod") == 0) {
                        binaryfunc(OP_MOD);
                    }
                    else if (strcmp(buffer, "pow") == 0) {
                        binaryfunc(OP_POW);
                    }
                    else if (strcmp(buffer, "sum") == 0) {
                        double result = 0;
                        for (int k = 0; k <= sp; k++) {
                            result += valueAt(k);
                        }
                        if (!push(result)) {
                            if (show_errors)
                                printf(
                                    "ERROR: Can't find sum of numbers because "
                                    "stack is full\n");
                            err_occured = 1;
                            return;
                        }
                    }
                    else if (strcmp(buffer, "prod") == 0) {
                        double result = 1;
                        for (int k = 0; k <= sp; k++) {
                            result *= valueAt(k);
                        }
                        if (!push(result)) {
                            if (show_errors)
                                printf(
                                    "ERROR: Can't find product of numbers "
                                    "because "
                                    "stack is full\n");
                            err_occured = 1;
                            return;
                        }
                    }
                    else if (strcmp(buffer, "clrtop") == 0) {
                        // Clears all elements of stack except top
                        if (sp > 0) {
                            double tmp = valueAt(sp);
                            sp = -1;
                            push(tmp);
                        }
                        else {
                            printf(
                                "WARN: clrtop failed as there are no elements "
                                "in the stack\n");
                        }
                    }

                    // Handle set command
                    else if (strcmp(buffer, "set") == 0)
                    {
                        // Example:
                        // set a = <expression>
                        // set a = 3 2 +  ----> Sets a to 5
                        // Grammer:
                        // set "single letter variable name" = "expression"
                        Token t2 = getNextToken();
                        Token t3;
                        if (t2.type == IDENTIFIER && t2.length == 1 &&
                            isupper(t2.src[t2.index])) {
                            t3 = getNextToken();
                            if (t3.type == ASSIGNMENT) {
                                calculate();
                                if (!err_occured) {
                                    double vars = 0;
                                    char ch = t2.src[t2.index];
                                    assert((ch - 'A') >= 0);
                                    assert((ch - 'A') < 26);

                                    pop(&vars);
                                    printf("Set the value of %c to %.15g\n", ch,
                                           vars);
                                    variable_lookup[ch - 'A'] = vars;
                                    variables_set[ch - 'A'] = 1;
                                }
                                else {
                                    if (show_errors)
                                        printf(
                                            "ERROR: Error occured on rhs "
                                            "expression\n");
                                }
                            }
                            else {
                                if (show_errors)
                                    printf("%s\n",
                                           "ERROR~~: Invalid use of set, no =");
                                cp = t2.index;
                                err_occured = 1;
                                return;
                            }
                        }
                        else {
                            if (show_errors)
                                printf(
                                    "%s\n",
                                    "ERROR~~: Invalid use of set, no variable "
                                    "after set command, or variable is not "
                                    "single uppercase letter");
                            cp = t2.index;
                            err_occured = 1;
                            return;
                        }
                    }

                    // Handle single letter variables
                    // Only uppercase variables are supported as some math
                    // constants are in lowercase
                    else if (t.length == 1)
                    {
                        if (t.src[t.index] >= 'A' && t.src[t.index] <= 'Z') {
                            int index = (int)(t.src[t.index] - 'A');
                            assert(index >= 0 && index < 26);
                            if (!variables_set[index]) {
                                if (show_errors)
                                    printf("ERROR: Variable %c not set\n",
                                           t.src[t.index]);
                                err_occured = 1;
                                return;
                            }
                            if (!push(variable_lookup[index])) {
                                if (show_errors)
                                    printf(
                                        "ERROR: Stack is full, unable to "
                                        "dereference variable\n");
                                err_occured = 1;
                                return;
                            }
                        }
                        else {
                            if (show_errors)
                                printf(
                                    "ERROR: Only uppercase variables are "
                                    "supported\n");
                            err_occured = 1;
                            return;
                        }
                    }
                    else
                    {
                        err_occured = 1;
                        printf("%s%s\n",
                               "Error: Unknown identifier or function - ",
                               buffer);
                        printf("%s\n",
                               "Type \"help\" to view all supported commands");
                        printf("%s\n",
                               "If you meant to assign a variable, only single "
                               "character variables are supported");
                        return;
                    }
                    break;

                case PLUS:
                    binop('+');
                    break;

                case MINUS:
                    binop('-');
                    break;

                case STAR:
                    binop('*');
                    break;

                case FORWARD_SLASH:
                    binop('/');
                    break;

                case MODULUS:
                    binop('%');
                    break;

                case EXCLAMATION:
                    unaryop(OP_FACTORIAL);
                    break;

                case BIT_LSHIFT:
                    binop('L');
                    break;
                case BIT_RSHIFT:
                    binop('R');
                    break;
                case BIT_AND:
                    binop('&');
                    break;
                case BIT_OR:
                    binop('|');
                    break;
                case BIT_NOT:
                    unaryop(OP_BIT_NOT);
                    break;
                case BIT_XOR:
                    binop('^');
                    break;

                case NEWLINE:
                case END_OF_FILE:
                    break;

                default:
                    printf("%s\n", "UNHANDLED");
            }
        }
        if (TOKEN_DEBUG_ENABLED) displayToken(t);
    } while (t.type != END_OF_FILE);
}

int getline_(char buffer_[], int bufferSize)
{
    int bufferIndex = 0, ch;
    while (bufferIndex < (bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        buffer_[bufferIndex++] = (char)ch;
        if (ch == '\n') break;
    }
    buffer_[bufferIndex] = '\0';
    return bufferIndex;
}


int main()
{
    int length;
    if (clear_screen) clearScreen();
    printf("%s %s\n",
           "Welcome to Shankar's RPN (Reverse polish notation) Calculator",
           VERSION);
    printf("Max supported length of a single line of input: %d\n", BUFFER_SIZE);
    printf("Max number of operands supported: %d\n", MAX_OPERANDS);
    printf(
        "$ rpn    - runs this calculator in interactive mode, Enter the "
        "expression through standard input\n");
    printf("%s\n", "Type @ and press enter to toggle debug mode");
    printf("Type \"help\" and press enter to get help\n");
    if (display_prompt) printf("%s", ">>");
    while ((length = getline_(src_string, 512))) {
        if (clear_screen) clearScreen();
        calculate();
        if (!running) {
            if (clear_screen) clearScreen();
            if (stack_shown) displayStack();
            break;
        }
        if (stack_shown) displayStack();
        // reset();
        cp = 0;
        err_occured = 0;
        if (display_prompt) printf("%s", ">>");
    }
}
// Sample formulae
// Formula to find the roots of a quadratic equation (set A, B, and C before)
// B -1 * B 2 pow 4 A * C * - sqrt + 2 A * /
// B -1 * B 2 pow 4 A * C * + sqrt + 2 A * /
//
// Example:
// set A = 1
// set B = -2
// set C = -3
//
