#include <iostream>
#include <cstdlib>
#include <Rcpp.h>

using namespace std;
using namespace Rcpp;

/*
 * Bracketing Search
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
psudo random numbers

Write a program that calculates a random number 1 through 100. The program then asks the user to guess the number.
If the user guesses too high or too low then the program should output "too high" or "too low" accordingly.
The program must let the user continue to guess until the user correctly guesses the number.

★ Modify the program to output how many guesses it took the user to correctly guess the right number.

★★ Modify the program so that instead of the user guessing a number the computer came up with, 
 the computer guesses the number that the user has secretely decided.
 The user must tell the computer whether it guesed too high or too low.

★★★★ Modify the program so that no matter what number the user thinks of (1-100) the computer can guess it in 7 or less guesses.
 */
// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::export]]
void bracket(bool master) {
  
  srand (time(NULL));
  
  int i = 1;
  if(master == false) {
    Rcout << "What number between 1 and 100 am I thinking of?" << std::endl;
    int secret = rand() % 100 + 1;
    
    Rcpp::Environment base = Environment("package:base");
    Rcpp::Function readline = base["readline"];
    Rcpp::Function as_integer = base["as.integer"];
    int guess;
    
    do {
      Rcout << "Pick a number" << std::endl;
      guess = Rcpp::as<int>(as_integer(readline("> ")));
      
      if(guess < secret) {
        Rcout << "Your guess was too low" << std::endl;
        i++;
      }
      if(guess > secret) {
        Rcout << "Your guess was too high" << std::endl;
        i++;
      }
    } while (guess != secret);
    Rcout << "You guessed correctly in " << i << " guesses" << std::endl;
  }
  
  else {
    /// Needs modification to prevent it from choosing the same number twice when the range gets smaller.
    Rcpp::Environment base = Environment("package:base");
    Rcpp::Function readline = base["readline"];
    Rcpp::Function as_integer = base["as.integer"];
    
    Rcout << "Pick a number between 1 and 100" << std::endl;
    int secret = Rcpp::as<int>(as_integer(readline("> ")));
    
    int guess = rand() % 100 + 1;
    Rcout << guess << std::endl;
    int i = 1;
    int hi_prior = 100;
    int range;
    int init = guess;
    int low_prior = 1;
    
    do {
        if(guess < secret) {
          low_prior = guess;
          range = hi_prior - low_prior;
          guess = rand() % range + low_prior;
          
        }
        if(guess > secret) {
          hi_prior = guess;
          range = hi_prior - low_prior;
          guess = rand() % range + low_prior;
          
      }
        Rcout << guess << std::endl;
      i++;
    } while (guess != secret);
    Rcout << "I guessed correctly in " << i << " guesses" << std::endl;
  }
}

