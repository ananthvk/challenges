// Exercise 7-9. Functions like isupper can be implemented to save space or to save time.
// Explore both possibilities.

// To save time, isspace can be implemented as a macro so that the function call overhead can be mitigated
// but this can cause bugs in the future if the character passed is incremented as it happens twice
// and leads to undefined behaviour

#define isspace(ch) ch >= 'A' && ch <= 'Z'