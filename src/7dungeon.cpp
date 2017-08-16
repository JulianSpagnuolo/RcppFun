#include <cstdlib>
#include <iostream>
#include <array>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Dungeon Crawl
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Make a program that outputs a simple grid based gameboard to the screen using either numbers or characters.
i.e.

. . . . . . . . . .
. G . . . . . . . .
. . . . . . T . . .
. . . . . . . . . .
. . . . T . . . . .
. . . . . . T . . .
. . . . . . . . . X

or

0 0 0 0 0 0 0 0 0 0
0 5 0 0 6 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 7 0 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 4


Allow the user (marked by G in the example) to move either up, down, left, or right each turn.
 If the player steps on a trap then they lose. If the make it to the treasure 'X' then they win.

★★ Add enemies that move randomly in any direction once per turn. (enemies just like traps cause the player to lose if touched)

HINT: Don't let the player move off the gameboard! You program will crash if they move off the top or bottom of the board!
(the same holds true for enemies)
 */

// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::export]]
void dungeon() {
  
  Rcout << "Initialising dungeon" << std::endl;
  
  Rcpp::Environment base = Environment("package:base");
  Rcpp::Function readline = base["readline"];
  Rcpp::Function as_char = base["as.character"];
  char move;
  
  srand(time(NULL));
  
  struct entity{
    int row; // initial or current position
    int col;
    int temprow; // initial or new position
    int tempcol;
    int poscond; // is position on an edge or corner
    char symbol;
    bool dead;
  };
  
  const char tile = '.';
  const char trap = 'T';
  const char enemy = 'e';
  
  int emove;
  
  bool win = false;
  bool end = false;
  
  std::array<std::array<char, 10>, 10> dungeon =  {{
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}},
    {{'.','.','.','.','.','.','.','.','.','.'}}
    }};
  
  
  entity player;
  entity treasure;
  entity trap1;
  entity trap2;
  entity trap3;
  entity enemy1;
  entity enemy2;
  entity enemy3;
  
  player.symbol = 'P';
  treasure.symbol = 'X';
  trap1.symbol = 'T';
  trap2.symbol = 'T';
  trap3.symbol = 'T';
  enemy1.symbol = 'e';
  enemy2.symbol = 'e';
  enemy3.symbol = 'e';
  
  player.dead = false;
  enemy1.dead = false;
  enemy2.dead = false;
  enemy3.dead = false;
  
  // Place the treasure
  treasure.row = rand() % 10 + 0;
  treasure.col = rand() % 10 + 0;
  dungeon[treasure.row][treasure.col] = treasure.symbol;
  
  // Place traps
  do{
    trap1.row = rand() % 10 + 0;
    trap1.col = rand() % 10 + 0;
  } while (dungeon[trap1.row][trap1.col] != tile);
  dungeon[trap1.row][trap1.col] = trap1.symbol;
  
  do{
    trap2.row = rand() % 10 + 0;
    trap2.col = rand() % 10 + 0;
  } while (dungeon[trap2.row][trap2.col] != tile);
  dungeon[trap2.row][trap2.col] = trap2.symbol;
  
  do{
    trap3.row = rand() % 10 + 0;
    trap3.col = rand() % 10 + 0;
  } while (dungeon[trap3.row][trap3.col] != tile);
  dungeon[trap3.row][trap3.col] = trap3.symbol;
  
  // Place enemies
  do{
    enemy1.row = rand() % 10 + 0;
    enemy1.col = rand() % 10 + 0;
  } while (dungeon[enemy1.row][enemy1.col] != tile);
  dungeon[enemy1.row][enemy1.col] = enemy;
  enemy1.temprow = enemy1.row;
  enemy1.tempcol = enemy1.col;
  // restrict enemy movement possibilities
  if((enemy1.row == 0) && (enemy1.col == 0)) {enemy1.poscond = 1;}
  if((enemy1.row == 0) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 2;}
  if((enemy1.row == 0) && (enemy1.col == 9)) {enemy1.poscond = 3;}
  if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col == 0)) {enemy1.poscond = 4;}
  if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 5;}
  if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col == 9)) {enemy1.poscond = 6;}
  if((enemy1.row == 9) && (enemy1.col == 0)) {enemy1.poscond = 7;}
  if((enemy1.row == 9) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 8;}
  if((enemy1.row == 9) && (enemy1.col == 9)) {enemy1.poscond = 9;}
  
  do{
    enemy2.row = rand() % 10 + 0;
    enemy2.col = rand() % 10 + 0;
  } while (dungeon[enemy2.row][enemy2.col] != tile);
  dungeon[enemy2.row][enemy2.col] = enemy;
  enemy2.temprow = enemy2.row;
  enemy2.tempcol = enemy2.col;
  // restrict enemy movement possibilities
  if((enemy2.row == 0) && (enemy2.col == 0)) {enemy2.poscond = 1;}
  if((enemy2.row == 0) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 2;}
  if((enemy2.row == 0) && (enemy2.col == 9)) {enemy2.poscond = 3;}
  if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col == 0)) {enemy2.poscond = 4;}
  if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 5;}
  if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col == 9)) {enemy2.poscond = 6;}
  if((enemy2.row == 9) && (enemy2.col == 0)) {enemy2.poscond = 7;}
  if((enemy2.row == 9) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 8;}
  if((enemy2.row == 9) && (enemy2.col == 9)) {enemy2.poscond = 9;}
  
  do{
    enemy3.row = rand() % 10 + 0;
    enemy3.col = rand() % 10 + 0;
  } while (dungeon[enemy3.row][enemy3.col] != tile);
  dungeon[enemy3.row][enemy3.col] = enemy;
  enemy3.temprow = enemy3.row;
  enemy3.tempcol = enemy3.col;
  // restrict enemy movement possibilities
  if((enemy3.row == 0) && (enemy3.col == 0)) {enemy3.poscond = 1;}
  if((enemy3.row == 0) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 2;}
  if((enemy3.row == 0) && (enemy3.col == 9)) {enemy3.poscond = 3;}
  if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col == 0)) {enemy3.poscond = 4;}
  if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 5;}
  if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col == 9)) {enemy3.poscond = 6;}
  if((enemy3.row == 9) && (enemy3.col == 0)) {enemy3.poscond = 7;}
  if((enemy3.row == 9) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 8;}
  if((enemy3.row == 9) && (enemy3.col == 9)) {enemy3.poscond = 9;}
  
  // Place the player
  do{
    player.row = rand() % 10 + 0;
    player.col = rand() % 10 + 0;
  } while (dungeon[player.row][player.col] != tile);
  dungeon[player.row][player.col] = player.symbol;
  // initialise temp position at initial coords
  player.temprow = player.row;
  player.tempcol = player.col;
  
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      Rcout << dungeon[i][j] << " ";
    }
    Rcout << std::endl;
  }
  
  do {
    // Player move
    Rcout << "Player move (use: w, a, s, d):" << std::endl;
    move = Rcpp::as<char>(as_char(readline("> ")));
    // convert wasd input to int
    switch(move){
    case 'w': player.temprow = player.row - 1;
      break;
    case 's': player.temprow = player.row + 1;
      break;
    case 'a': player.tempcol = player.col - 1;
      break;
    case 'd': player.tempcol = player.col + 1;
      break;
    default: Rcout << "Invalid move, try again" << std::endl;
    break;
    }
    // check new player position for entities
    if(dungeon[player.temprow][player.tempcol] == trap) {
      player.dead = true;
      end = true;
      } 
    if(dungeon[player.temprow][player.tempcol] == enemy) {
      player.dead = true;
      end = true;
      }
    if((player.temprow == treasure.row) && (player.tempcol == treasure.col)) {
      win = true;
      end = true;
      }
    else {
      dungeon[player.temprow][player.tempcol] = player.symbol; // move the player
      dungeon[player.row][player.col] = tile; // cover their tracks
      player.row = player.temprow; // update position
      player.col = player.tempcol;}
    
    // enemy move
    if(enemy1.dead == false) {
      switch(enemy1.poscond){
      case 1:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 2:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col + 1;
          break;
        case 2: 
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 3:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 4:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 2:
          enemy1.tempcol = enemy1.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 5:
        emove = rand() % 4 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 2:
          enemy1.tempcol = enemy1.col + 1;
          break;
        case 3:
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 6:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row + 1;
          break;
        case 1:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 2:
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 7:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 8:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col + 1;
          break;
        case 2:
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 9:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy1.temprow = enemy1.row - 1;
          break;
        case 1:
          enemy1.tempcol = enemy1.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      }
    }
    // check new enemy position for entities
    if(dungeon[enemy1.temprow][enemy1.tempcol] == trap) {
      enemy1.dead = true;
      dungeon[enemy1.temprow][enemy1.tempcol] = trap;
    } 
    if(dungeon[enemy1.temprow][enemy1.tempcol] == enemy) {
      enemy1.dead = true;
      dungeon[enemy1.temprow][enemy1.tempcol] = tile;
    }
    else {
      dungeon[enemy1.temprow][enemy1.tempcol] = enemy1.symbol; // move the player
      dungeon[enemy1.row][enemy1.col] = tile; // cover their tracks
      enemy1.row = enemy1.temprow; // update position
      enemy1.col = enemy1.tempcol;}
    if(dungeon[enemy1.temprow][enemy1.tempcol] == player.symbol) {player.dead = true;} // move outside the switch
    if((enemy1.row == 0) && (enemy1.col == 0)) {enemy1.poscond = 1;}
    if((enemy1.row == 0) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 2;}
    if((enemy1.row == 0) && (enemy1.col == 9)) {enemy1.poscond = 3;}
    if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col == 0)) {enemy1.poscond = 4;}
    if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 5;}
    if((enemy1.row > 0) && (enemy1.row < 9) && (enemy1.col == 9)) {enemy1.poscond = 6;}
    if((enemy1.row == 9) && (enemy1.col == 0)) {enemy1.poscond = 7;}
    if((enemy1.row == 9) && (enemy1.col > 0) && (enemy1.col < 9)) {enemy1.poscond = 8;}
    if((enemy1.row == 9) && (enemy1.col == 9)) {enemy1.poscond = 9;}
    
    if(enemy2.dead == false) {
      switch(enemy2.poscond){
      case 1:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 2:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col + 1;
          break;
        case 2: 
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 3:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 4:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 2:
          enemy2.tempcol = enemy2.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 5:
        emove = rand() % 4 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 2:
          enemy2.tempcol = enemy2.col + 1;
          break;
        case 3:
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 6:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row + 1;
          break;
        case 1:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 2:
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 7:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 8:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col + 1;
          break;
        case 2:
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 9:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy2.temprow = enemy2.row - 1;
          break;
        case 1:
          enemy2.tempcol = enemy2.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      }
    }
    // check new enemy position for entities
    if(dungeon[enemy2.temprow][enemy2.tempcol] == trap) {
      enemy2.dead = true;
      dungeon[enemy2.temprow][enemy2.tempcol] = trap;
    } 
    if(dungeon[enemy2.temprow][enemy2.tempcol] == enemy) {
      enemy2.dead = true;
      dungeon[enemy2.temprow][enemy2.tempcol] = tile;
    }
    else {
      dungeon[enemy2.temprow][enemy2.tempcol] = enemy2.symbol; // move the player
      dungeon[enemy2.row][enemy2.col] = tile; // cover their tracks
      enemy2.row = enemy2.temprow; // update position
      enemy2.col = enemy2.tempcol;}
    if(dungeon[enemy2.temprow][enemy2.tempcol] == player.symbol) {player.dead = true;} // move outside the switch
    if((enemy2.row == 0) && (enemy2.col == 0)) {enemy2.poscond = 1;}
    if((enemy2.row == 0) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 2;}
    if((enemy2.row == 0) && (enemy2.col == 9)) {enemy2.poscond = 3;}
    if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col == 0)) {enemy2.poscond = 4;}
    if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 5;}
    if((enemy2.row > 0) && (enemy2.row < 9) && (enemy2.col == 9)) {enemy2.poscond = 6;}
    if((enemy2.row == 9) && (enemy2.col == 0)) {enemy2.poscond = 7;}
    if((enemy2.row == 9) && (enemy2.col > 0) && (enemy2.col < 9)) {enemy2.poscond = 8;}
    if((enemy2.row == 9) && (enemy2.col == 9)) {enemy2.poscond = 9;}
    
    if(enemy3.dead == false) {
      switch(enemy3.poscond){
      case 1:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 2:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col + 1;
          break;
        case 2: 
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 3:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 4:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 2:
          enemy3.tempcol = enemy3.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 5:
        emove = rand() % 4 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 2:
          enemy3.tempcol = enemy3.col + 1;
          break;
        case 3:
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 6:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row + 1;
          break;
        case 1:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 2:
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 7:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col + 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 8:
        emove = rand() % 3 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col + 1;
          break;
        case 2:
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      case 9:
        emove = rand() % 2 + 0;
        switch(emove){
        case 0:
          enemy3.temprow = enemy3.row - 1;
          break;
        case 1:
          enemy3.tempcol = enemy3.col - 1;
          break;
        default:
          Rcout << "emove rand range too big" << std::endl;
        break;
        }
        break;
      }
    }
    // check new enemy position for entities
    if(dungeon[enemy3.temprow][enemy3.tempcol] == trap) {
      enemy3.dead = true;
      dungeon[enemy3.temprow][enemy3.tempcol] = trap;
    } 
    if(dungeon[enemy3.temprow][enemy3.tempcol] == enemy) {
      enemy3.dead = true;
      dungeon[enemy3.temprow][enemy3.tempcol] = tile;
    }
    else {
      dungeon[enemy3.temprow][enemy3.tempcol] = enemy3.symbol; // move the player
      dungeon[enemy3.row][enemy3.col] = tile; // cover their tracks
      enemy3.row = enemy3.temprow; // update position
      enemy3.col = enemy3.tempcol;}
    if(dungeon[enemy3.temprow][enemy3.tempcol] == player.symbol) {player.dead = true;} // move outside the switch
    if((enemy3.row == 0) && (enemy3.col == 0)) {enemy3.poscond = 1;}
    if((enemy3.row == 0) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 2;}
    if((enemy3.row == 0) && (enemy3.col == 9)) {enemy3.poscond = 3;}
    if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col == 0)) {enemy3.poscond = 4;}
    if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 5;}
    if((enemy3.row > 0) && (enemy3.row < 9) && (enemy3.col == 9)) {enemy3.poscond = 6;}
    if((enemy3.row == 9) && (enemy3.col == 0)) {enemy3.poscond = 7;}
    if((enemy3.row == 9) && (enemy3.col > 0) && (enemy3.col < 9)) {enemy3.poscond = 8;}
    if((enemy3.row == 9) && (enemy3.col == 9)) {enemy3.poscond = 9;}
    
    // reprint treasure tile incase it got over written by enemy.
    if(dungeon[treasure.row][treasure.col] == enemy) {
      dungeon[treasure.row][treasure.col] = '!';
    }
    else {dungeon[treasure.row][treasure.col] = treasure.symbol;}
    
    // Reprint Trap tiles (cant figure out why the reprint when stepped on by enemy isn't working)
    dungeon[trap1.row][trap1.col] = trap1.symbol;
    dungeon[trap2.row][trap2.col] = trap2.symbol;
    dungeon[trap3.row][trap3.col] = trap3.symbol;
    
    
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        Rcout << dungeon[i][j] << " ";
      }
      Rcout << std::endl;
    }
    
  } while (end == false);
  
  
  // end game responses
  if(player.dead == true) {
    Rcout << "You died. Game over" << std::endl;
  }
  if(win == true) {
    Rcout << "You win. Game over" << std::endl;
  }
  
}

