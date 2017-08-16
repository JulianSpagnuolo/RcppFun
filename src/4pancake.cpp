#include <algorithm>
#include <iterator>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Pancake Glutton
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Write a program that asks the user to enter the number of pancakes eaten for breakfast by 10 different people
 (Person 1, Person 2, ..., Person 10)
Once the data has been entered the program must analyze the data and output which person ate the most pancakes for breakfast.

★ Modify the program so that it also outputs which person ate the least number of pancakes for breakfast.

★★★★ Modify the program so that it outputs a list in order of number of pancakes eaten of all 10 people.
i.e.
Person 4: ate 10 pancakes
Person 3: ate 7 pancakes
Person 8: ate 4 pancakes
...
Person 5: ate 0 pancakes
 */
// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::export]]
void pancake(IntegerVector eaten) {
  
  IntegerVector ordered;
  ordered = eaten.sort(true);
  
  // This solution to index the people does not deal with duplicates in eaten.
  IntegerVector person;
  for(int i = 0; i < eaten.size(); i++) {
    int x = ordered[i];
    auto it = std::find(std::begin(eaten), std::end(eaten), x);
    int p = std::distance(std::begin(eaten), it);
    person[i] = p + 1;
  }
  
  
  for(int i = 0; i < eaten.size(); i++) {
    Rcout << "Person " << person[i] << " ate " << ordered[i] << " pancakes." << std::endl;
  }
}

