#include <Rcpp.h>

using namespace Rcpp;

/*
 * Cola Machine
 Requires:
 variables, data types, and numerical operators
 basic input/output
 logic (if statements, switch statements)
 
 Write a program that presents the user w/ a choice of your 5 favorite beverages (Coke, Water, Sprite, ... , Whatever).
 Then allow the user to choose a beverage by entering a number 1-5.
 Output which beverage they chose.
 
 ★ If you program uses if statements instead of a switch statement, modify it to use a switch statement.
 If instead your program uses a switch statement, modify it to use if/else-if statements.
 
 ★★ Modify the program so that if the user enters a choice other than 1-5 then it will output "
 Error. choice was not valid, here is your money back."
 */

// [[Rcpp::export]]
Rcpp::String cola() {
  Rcpp::Rcout << "Pick a drink:\n" << "1 - Espresso\n" << "2 - Americano\n" << "3 - Latte\n" << "4 - Cafe dopio\n" << "5 - Tea\n" << std::endl;
  Rcpp::Environment base = Environment("package:base"); //1 These 4 lines take input from R console
  Rcpp::Function readline = base["readline"]; //2
  Rcpp::Function as_integer = base["as.integer"]; //3
  int drink = Rcpp::as<int>(as_integer(readline("> "))); //4
  std::string out;
  switch(drink) {
  case 1: out = "Here is your Espresso";
    break;
  case 2: out = "Here is your Americano";
    break;
  case 3: out = "Here is your Latte";
    break;
  case 4: out = "Here is your Cafe dopio";
    break;
  case 5: out = "Here is your Tea";
    break;
  default:
    out = "Error. Choice was not valid, here is your money back.";
  break;
  }
  return out;
}



