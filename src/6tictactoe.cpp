#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Tic Tac Toe
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Make a two player tic tac toe game.

★ Modify the program so that it will announce when a player has won the game (and which player won, x or o)

★★ Modify the program so that it is a one player game against the computer (with the computer making its moves randomly)

★★★★ Modify the program so that anytime the player is about to win 
 (aka, they have 2 of 3 x's in a row, the computer will block w/ an o)
 */

// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::export]]
void tictactoe(bool TwoPlayer) {
  // initialise a 3x3 tic tac toe board.
  IntegerMatrix board(3,3);
  
  // initialise input from R console
  Rcpp::Environment base = Environment("package:base");
  Rcpp::Function readline = base["readline"];
  Rcpp::Function as_char = base["as.character"];
  Rcpp::Function as_integer = base["as.integer"];
  char column;
  int row;
  int col;
  bool won = false;
  bool won1 = false;
  bool won2 = false;
  IntegerVector winCond1(3,1);
  IntegerVector winCond2(3,2);
  
  const int player1 = 1;
  const int player2 = 2;
  int i = 0;
  
  Rcout << board << std::endl;
  if(TwoPlayer == true) {
    do {
      
      // Player 1 turn when i is even
      if(i % 2 == 0) {
        Rcout << "Player1: Pick column (a,b, or c)" << std::endl;
        column = Rcpp::as<char>(as_char(readline("> ")));
        
        Rcout << "Player1: Pick row (1,2, or 3)" << std::endl;
        row = Rcpp::as<int>(as_integer(readline("> ")));
        row = row - 1;
        
        // convert column char to col index
        switch(column) {
        case 'a':
        case 'A':
          col = 0;
          break;
        case 'b':
        case 'B':
          col = 1;
          break;
        case 'c':
        case 'C':
          col = 2;
          break;
        default:
          Rcout << "Invalid Selection. Try Again." << std::endl;
        }
        
        
        if((row < 3) && (board(row,col) != player2)) {
          board(row,col) = player1;
          i++;
        } else {Rcout << "Invalid Selection. Try Again." << std::endl;}

        // Return board to R for ggplot
        Rcout << board << std::endl;
      }
      
      // Player 2 turn when i is odd
      else {
        Rcout << "Player2: Pick column (a,b, or c)" << std::endl;
        column = Rcpp::as<char>(as_char(readline("> ")));
        Rcout << "Player2: Pick row (1,2, or 3)" << std::endl;
        row = Rcpp::as<int>(as_integer(readline("> ")));
        row = row - 1;
        
        // convert column char to col index
        switch(column) {
        case 'a':
        case 'A':
          col = 0;
          break;
        case 'b':
        case 'B':
          col = 1;
          break;
        case 'c':
        case 'C':
          col = 2;
          break;
        default:
          Rcout << "Invalid Selection. Try Again." << std::endl;
        }
        
        
        if((row < 3) && (board(row,col) != player1)) {
          board(row,col) = player2;
          i++;
        } else {Rcout << "Invalid Selection. Try Again." << std::endl;}

        
        // Return board to R for ggplot.
        Rcout << board << std::endl;
      }
      
      
      
      
      
      /*
       * ggplot(melt(x), aes(x=X2, y=X1)) +geom_point(aes(shape=factor(y$value, levels=c(1,2))), size=15) +scale_shape_manual(values=c(4,1)) +scale_y_continuous(breaks=c(1,2,3), limits=c(0.7,3.3)) +scale_x_continuous(breaks=c(1,2,3), limits=c(0.7,3.3), labels=c("A","B","C")) +theme_bw() +theme(aspect.ratio = 1, panel.grid.major = element_blank(), panel.grid.minor = element_line(colour="black", size=0.5), panel.grid.minor.x = element_line(colour="black", size=0.5), legend.position = "none", panel.border = element_blank(), axis.title = element_blank())
       */
      
      
      // Get the condition of board rows, columns and diagonals
      IntegerVector diag1 = IntegerVector::create(board(0,0), board(1,1), board(2,2));
      IntegerVector diag2 = IntegerVector::create(board(0,2), board(1,1), board(2,0));
      
      IntegerVector r1cond = IntegerVector::create(board(0,0), board(0,1), board(0,2));
      IntegerVector r2cond = IntegerVector::create(board(1,0), board(1,1), board(1,2));
      IntegerVector r3cond = IntegerVector::create(board(2,0), board(2,1), board(2,2));
      
      IntegerVector c1cond = IntegerVector::create(board(0,0), board(1,0), board(2,0));
      IntegerVector c2cond = IntegerVector::create(board(0,1), board(1,1), board(2,1));
      IntegerVector c3cond = IntegerVector::create(board(0,2), board(1,2), board(2,2));
      
      
      // win conditions
      if(all(r1cond == winCond1).is_true()) {won1 = true;}
      if(all(r2cond == winCond1).is_true()) {won1 = true;}
      if(all(r3cond == winCond1).is_true()) {won1 = true;}
      if(all(c1cond == winCond1).is_true()) {won1 = true;}
      if(all(c2cond == winCond1).is_true()) {won1 = true;}
      if(all(c3cond == winCond1).is_true()) {won1 = true;}
      if(all(diag1 == winCond1).is_true()) {won1 = true;}
      if(all(diag2 == winCond1).is_true()) {won1 = true;}
      
      if(all(r1cond == winCond2).is_true()) {won2 = true;}
      if(all(r2cond == winCond2).is_true()) {won2 = true;}
      if(all(r3cond == winCond2).is_true()) {won2 = true;}
      if(all(c1cond == winCond2).is_true()) {won2 = true;}
      if(all(c2cond == winCond2).is_true()) {won2 = true;}
      if(all(c3cond == winCond2).is_true()) {won2 = true;}
      if(all(diag1 == winCond2).is_true()) {won2 = true;}
      if(all(diag2 == winCond2).is_true()) {won2 = true;}
      
      if(won1 == true) {won = true;}
      if(won2 == true) {won = true;}
      
    } while (won == false);
    
    if(won1 == true) {Rcout << "Player 1 wins" << std::endl;}
    if(won2 == true) {Rcout << "Player 2 wins" << std::endl;}
    
  }
  
  
  // One player mode against computer
  // Crashes occasionally when PC makes a blocking move (or winning move).
  else {
    
    bool fu = false;
    srand(time(NULL));
    
    // Get the condition of board rows, columns and diagonals
    IntegerVector diag1 = IntegerVector::create(board(0,0), board(1,1), board(2,2));
    IntegerVector diag2 = IntegerVector::create(board(0,2), board(1,1), board(2,0));
    
    IntegerVector r1cond = IntegerVector::create(board(0,0), board(0,1), board(0,2));
    IntegerVector r2cond = IntegerVector::create(board(1,0), board(1,1), board(1,2));
    IntegerVector r3cond = IntegerVector::create(board(2,0), board(2,1), board(2,2));
    
    IntegerVector c1cond = IntegerVector::create(board(0,0), board(1,0), board(2,0));
    IntegerVector c2cond = IntegerVector::create(board(0,1), board(1,1), board(2,1));
    IntegerVector c3cond = IntegerVector::create(board(0,2), board(1,2), board(2,2));
    
    int diag1count = std::count(diag1.begin(), diag1.end(), 1);
    int diag2count = std::count(diag1.begin(), diag2.end(), 1);
    
    int r1count = std::count(r1cond.begin(), r1cond.end(), 1);
    int r2count = std::count(r2cond.begin(), r2cond.end(), 1);
    int r3count = std::count(r3cond.begin(), r3cond.end(), 1);
    
    int c1count = std::count(c1cond.begin(), c1cond.end(), 1);
    int c2count = std::count(c2cond.begin(), c2cond.end(), 1);
    int c3count = std::count(c3cond.begin(), c3cond.end(), 1);
    

    
    do {
      
      // Player 1 turn when i is even
      if(i % 2 == 0) {
        Rcout << "Player1: Pick column (a,b, or c)" << std::endl;
        column = Rcpp::as<char>(as_char(readline("> ")));
        
        // convert column char to col index
        switch(column) {
        case 'a':
        case 'A':
          col = 0;
          break;
        case 'b':
        case 'B':
          col = 1;
          break;
        case 'c':
        case 'C':
          col = 2;
          break;
        default:
          Rcout << "Invalid Selection. Try Again." << std::endl;
        }
        
        Rcout << "Player1: Pick row (1,2, or 3)" << std::endl;
        row = Rcpp::as<int>(as_integer(readline("> ")));
        row = row - 1;
        
        if((row < 3) && (board(row,col) != player2) && (board(row,col) != player1)) {
          board(row,col) = player1;
          i++;
        } else {Rcout << "Invalid Selection. Try Again." << std::endl;}
        
        
        // update PC cheating after players round
        // Get board condition at the end of each round
        diag1 = IntegerVector::create(board(0,0), board(1,1), board(2,2));
        diag2 = IntegerVector::create(board(0,2), board(1,1), board(2,0));
        
        r1cond = IntegerVector::create(board(0,0), board(0,1), board(0,2));
        r2cond = IntegerVector::create(board(1,0), board(1,1), board(1,2));
        r3cond = IntegerVector::create(board(2,0), board(2,1), board(2,2));
        
        c1cond = IntegerVector::create(board(0,0), board(1,0), board(2,0));
        c2cond = IntegerVector::create(board(0,1), board(1,1), board(2,1));
        c3cond = IntegerVector::create(board(0,2), board(1,2), board(2,2));
        
        diag1count = std::count(diag1.begin(), diag1.end(), 1);
        diag2count = std::count(diag1.begin(), diag2.end(), 1);
        
        r1count = std::count(r1cond.begin(), r1cond.end(), 1);
        r2count = std::count(r2cond.begin(), r2cond.end(), 1);
        r3count = std::count(r3cond.begin(), r3cond.end(), 1);
        
        c1count = std::count(c1cond.begin(), c1cond.end(), 1);
        c2count = std::count(c2cond.begin(), c2cond.end(), 1);
        c3count = std::count(c3cond.begin(), c3cond.end(), 1);
        
        // Return board to R for ggplot
        Rcout << board << std::endl;
      }
      
      // Player 2 turn when i is odd
      else {
        
        Rcout << "Computers turn:" << std::endl;
        
        if((diag1count == 2) || (diag2count == 2) || (r1count == 2) || (r2count == 2) || (r3count == 2) || (c1count == 2) || (c2count == 2) || (c3count == 2)){
          fu = true;
        } else {fu = false;}
        
        if(fu == false) {
          do {
            row = rand() % 3 + 0;
            col = rand() % 3 + 0;
          } while ((board(row,col) ==  player1) || (board(row,col) ==  player2));
        }
        else {
          if(r1count == 2) {
            auto ind = std::find(r1cond.begin(), r1cond.end(), 0);
            row = 0;
            col = std::distance(r1cond.begin(), ind);
          }
          if(r2count == 2) {
            auto ind = std::find(r2cond.begin(), r2cond.end(), 0);
            row = 1;
            col = std::distance(r2cond.begin(), ind);
          }
          if(r3count == 2) {
            auto ind = std::find(r3cond.begin(), r3cond.end(), 0);
            row = 2;
            col = std::distance(r3cond.begin(), ind);
          }
          if(c1count == 2) {
            auto ind = std::find(c1cond.begin(), c1cond.end(), 0);
            row = std::distance(c1cond.begin(), ind);
            col = 0;
          }
          if(c2count == 2) {
            auto ind = std::find(c2cond.begin(), c2cond.end(), 0);
            row = std::distance(c2cond.begin(), ind);
            col = 1;
          }
          if(c3count == 2) {
            auto ind = std::find(c3cond.begin(), c3cond.end(), 0);
            row = std::distance(c3cond.begin(), ind);
            col = 2;
          }
          if(diag1count == 2){
            auto ind = std::find(diag1.begin(), diag1.end(), 0);
            row = std::distance(diag1.begin(), ind);
            col = std::distance(diag1.begin(), ind);
          }
          if(diag2count == 2){
            auto ind = std::find(diag1.begin(), diag1.end(), 0);
            int pos = std::distance(diag1.begin(), ind);
            switch(pos){
            case 0:
              row = 2;
              col = 0;
              break;
            case 1:
              row = 1;
              col = 1;
              break;
            case 2:
              row = 0;
              col = 2;
              break;
            }
          }
          fu = false; // reset fu
        }
        
        
        board(row,col) = player2;
        i++;
        
        // Return board to R for ggplot.
        Rcout << board << std::endl;
      }
      

      // Get board condition at the end of each round
      diag1 = IntegerVector::create(board(0,0), board(1,1), board(2,2));
      diag2 = IntegerVector::create(board(0,2), board(1,1), board(2,0));
      
      r1cond = IntegerVector::create(board(0,0), board(0,1), board(0,2));
      r2cond = IntegerVector::create(board(1,0), board(1,1), board(1,2));
      r3cond = IntegerVector::create(board(2,0), board(2,1), board(2,2));
      
      c1cond = IntegerVector::create(board(0,0), board(1,0), board(2,0));
      c2cond = IntegerVector::create(board(0,1), board(1,1), board(2,1));
      c3cond = IntegerVector::create(board(0,2), board(1,2), board(2,2));
      
      /*
      * ggplot(melt(x), aes(x=X2, y=X1)) +geom_point(aes(shape=factor(y$value, levels=c(1,2))), size=15) +scale_shape_manual(values=c(4,1)) +scale_y_continuous(breaks=c(1,2,3), limits=c(0.7,3.3)) +scale_x_continuous(breaks=c(1,2,3), limits=c(0.7,3.3), labels=c("A","B","C")) +theme_bw() +theme(aspect.ratio = 1, panel.grid.major = element_blank(), panel.grid.minor = element_line(colour="black", size=0.5), panel.grid.minor.x = element_line(colour="black", size=0.5), legend.position = "none", panel.border = element_blank(), axis.title = element_blank())
      */
      
      // win conditions
      if(all(r1cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(r2cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(r3cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(c1cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(c2cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(c3cond == winCond1).is_true()) {won1 = true;won = true;}
      if(all(diag1 == winCond1).is_true()) {won1 = true;won = true;}
      if(all(diag2 == winCond1).is_true()) {won1 = true;won = true;}
      
      if(all(r1cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(r2cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(r3cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(c1cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(c2cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(c3cond == winCond2).is_true()) {won2 = true;won = true;}
      if(all(diag1 == winCond2).is_true()) {won2 = true;won = true;}
      if(all(diag2 == winCond2).is_true()) {won2 = true;won = true;}
      
    } while (won == false);
    
    if(won1 == true) {Rcout << "Player 1 wins" << std::endl;}
    if(won2 == true) {Rcout << "Computer wins!" << std::endl;}
  }
  
}
