#include <string>
#include <vector>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Fun with Functions
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
functions

Write a function titled say_hello() that outputs to the screen "Hello"

★ Modify the function so that it takes an integer argument and says hello a number of times equal to the value passed to it.

★★ Make another function that takes two integers arguments and then returns an integer that is the product of the two integers.
(i.e., integer1: 4, Integer2: 5 returns: 20)

★★★ Make a function called half() that takes an integer argument. 
The function must print the number it received to the screen, then the program should divide that number by two to make a new number.
If the new number is greater than zero the function then calls the function half() passing it the new number as its argument.
If the number is zero or less then the function exits

Call the function half() with an argument of 100, the screen output should be
100
50
25
...
...
1.
 */



// [[Rcpp::plugins(cpp11)]]

void say_hello(int n){
  for(int i = 0; i < n; i++){
    Rcout << "Hello" << std::endl;
  }
}

int product(int a, int b){
  int res;
  res = a*b;
  return res;
}

void half(int c){
  while(c > 0){
    Rcout << c << std::endl;
    c = c/2;
  }
}

// [[Rcpp::export]]
void funfunc(int x, int y, int z) {
  say_hello(x);
  
  int res;
  res = product(x,y);
  Rcout << res << std::endl;
  
  half(z);
  
}

