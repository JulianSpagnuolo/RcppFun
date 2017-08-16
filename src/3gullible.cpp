#include <Rcpp.h>
using namespace Rcpp;

/*
 * While( user == gullible )
 Requires:
 variables, data types, and numerical operators
 basic input/output
 logic (if statements, switch statements)
 loops (for, while, do-while)
 
 Write a program that ccontinues to asks the user to enter any number other than 5 until the user enters the number 5.
 Then tell the user "Hey! you weren't supposed to enter 5!" and exit the program.
 
 ★ Modify the program so that after 10 iterations if the user still hasn't entered 5 will tell the user 
 "Wow, you're more patient then I am, you win." and exit.
 
 ★★ Modify the program so that it asks the user to enter any number other than the number equal to the number of times they've been asked 
 o enter a number. (i.e on the first iteration "Please enter any number other than 0" and on the second iteration
 "Please enter any number other than 1"m etc. etc. The program must behave accordingly exiting when the user enters the number they
 were asked not to.)
 */

// [[Rcpp::export]]
NumericVector gullible() {
  Environment base = Environment("package:base");
  Rcpp::Function readline = base["readline"];
  Rcpp::Function as_integer = base["as.integer"];
  int i = 0;
  int num;
  do {
    Rcout << " Pick a number other than 5 or " << i << std::endl;
    num = Rcpp::as<int>(as_integer(readline("> ")));
    if(num == 5 || num == i){
      Rcout << "You weren't supposed to pick 5 or " << i << std::endl;
      }
    if(i == 9) {
      Rcout << "Wow, you're more patient then I am, you win." << std::endl;
      }
    i++;
    } while((i < 10) && (num != 5 || num != i));
  return 0;
  }

