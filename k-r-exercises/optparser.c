/*
 * My implementation of a custom command line argument parser
 */
// NOTE:
// 1. Only single letter options are supported
// 2. If the option has an argument, it should be after the option with an =, no
// spaces are allowed
// 3. = is only supported with multi char options
//
// Pseudocode
// For each command line argument
//      If the argument starts with a "-"
//          Get the next character, if it is also a "-"
//              It is a multicharacter option
//                  If there is an equals(=) sign
//                      Return type="optval", ptr to third char of argument,
//                      (after the --), ptr to the next character after "="
//                      (valptr)
//                  Else
//                      Return type="opt", ptr to third char of arg(after --),
//                      valptr=NULL
//          Else
//              It is a group of single character options
//              return type="sopt", list of separate chars, valptr=NULL
//
//      Else
//          It is an argument
//              Return type="arg", ptr to the argument, valptr=NULL


