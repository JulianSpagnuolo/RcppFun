#include <Rcpp.h>
using namespace Rcpp;

/*
 * Strings are your friends, until they betray you.
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
functions
strings & string functions


Write a program that asks for a user first name and last name separately.
The program must then store the users full name inside a single string and out put it to the string.
i.e.
Input:
John
Smith
Output:
John Smith

★ Modify the program so that it then replaces every a, e, i , o, u w/ the letter z.
i.e.
John Smith -> Jzhn Smzth

★★ Modify the Program so that it reverses the users name
i.e.
John Smith -> htimS nhoJ
 */

// [[Rcpp::export]]
NumericVector string_betrayal(NumericVector x) {
  return x * 2;
}

