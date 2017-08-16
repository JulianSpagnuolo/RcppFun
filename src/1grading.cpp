#include <iostream>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Requires:
 variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)

Write a program that allows the user to enter the grade scored in a programming class (0-100).
If the user scored a 100 then notify the user that they got a perfect score.

★ Modify the program so that if the user scored a 90-100 it informs the user that they scored an A

★★ Modify the program so that it will notify the user of their letter grade
0-59 F 60-69 D 70-79 C 80-89 B 90-100 A
 */

// [[Rcpp::export]]
String grading(double x) {
  if(x == 100){
    std::cout << "Perfect score, you got an A!" << std::endl;
  } else if((x > 90) && (x < 100)) {
    std::cout << "You scored an A" << std::endl;
  } else if((x > 80) && (x < 90)) {
    std::cout << "You scored a B" << std::endl;
  } else if((x > 70) && (x < 80)) {
    std::cout << "You scored a C" << std::endl;
  } else if((x > 60) && (x < 70)) {
    std::cout << "You scored a D" << std::endl;
  } else if(x < 60) {
    std::cout << "You failed! F" << std::endl;
  }
  return 0;
}

