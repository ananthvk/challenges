# Programs which were not done by me

0. entab and detab program from exercise 1
1. Complete exercise-5-6, i.e implement other functions using pointers - I have only implemented getline using pointers.
2. Exercise-5-7 - This program is about sorting strings using quick sort, which I have not understood - Revisit this problem after learning quicksort.
3. Exercise-5-11, Exercise-5-12 - Not done as I have not done the entab and detab from exercise 1
4. Exercise 5-17. Add a field-searching capability  - Not done as i have to learn how to sort using two columns
5. Exercise 5-18 and others, based on dcl, a.k.a c declarations, do this after learning about recursive descent parser 
6. Exercise 5-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
the input and number conversion.
7. Correct exercise-7-6 as it prints each file in two parts, also refactor the code to make it more readable

7. Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of
named files or, if no files are named as arguments, from the standard input. Should the file
name be printed when a matching line is found?

Exercise 6-6
===============
What I learnt?
1. There can be weird bugs such as in the process token function, wherein a
space or newline character was printed twice
2. The fix is to use if-else if-else ladder instead of plain ifs

## TODO:
This program is not fully complete and there are a few more features which are necessary.
1. Does not handle quoted strings/chars in define.
2. Does not ignore #define and replacement in comments/strings
3. This code can be organized in a much better way
4. Display syntax error when the define is not correct as in the middle of lines, not having a single identifier after define, etc