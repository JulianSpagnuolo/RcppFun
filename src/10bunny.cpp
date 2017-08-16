#include <iostream>
#include <cstdlib>
#include <random>
#include <array>
#include <list>
#include <time.h>
#include <Rcpp.h>
using namespace Rcpp;

/*
 * Graduation:
 Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays
pseudo random number generation
strings & string functions
functions
structures/classes
enumerated data
file input/output
pointers
sorting
linked lists
advanced classes

Write a program that creates a linked list of bunny objects.
Each bunny object must have
Sex: Male, Female (random at creation 50/50)
color: white, brown, black, spotted
age : 0-10 (years old)
Name : randomly chosen at creation from a list of bunny names.
radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true)

At program initialization 5 bunnies must be created and given random colors.
Each turn afterwards the bunnies age 1 year.
So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older;
a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
New bunnies born should be the same color as their mother.

If a bunny becomes older than 10 years old, it dies.
If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into
a radioactive vampire bunny.
(if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
 
Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
Radioactive vampire bunnies do not die until they reach age 50.
 
The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age.
The program should also output each turns events such as
"Bunny Thumper was born!
Bunny Fufu was born!
Radioactive Mutant Vampire Bunny Darth Maul was born!
Bunny Julius Caesar died!
The program should write all screen output to a file.
When all the bunnies have died the program terminates.
If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)

★ Modify the program to run in real time, with each turn lasting 2 seconds, and a one second pause between each announement.

★★ Allow the user to hit the 'k' key to initiate a mass rabit cull! which causes half of all the rabits to be killed (randomly chosen).

★★★★ Modify the program to place the rabits in an 80x80 grid. Have the rabits move one space each turn randomly.
Mark juvenile males with m, adult males w/ M,
juvenile females w/ f, adult femails w/ F
radioactive mutant vampire bunnies with X

Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny.
 (if no empty square exits then the baby bunny isn't born)

★★★★★ Modify the program so that it saves each turn to a file and can play back at accelearted speed all subsequent turns.
 */

// [[Rcpp::plugins(cpp17)]]
struct bunny {
  int id;
  std::string sex;
  std::string colour;
  int age;
  std::string name;
  bool mutant;
  int born;
  int died;
  int mutated;
  bool alive;
  bunny *next;
};

class list {
private:
  bunny *head;
  bunny *tail;
  std::array<std::string, 4> colour = {{"white","brown","black","spotted"}};
  
public:
  list()
  {
    head=NULL;
    tail=NULL;
  }
  
  int countbunnies(){
    int count = 0;
    bunny* temp = head;
    while(temp != NULL){
      count++;
      temp = temp->next;
    }
    return count;
  }
  
  int bunnycull(int i){
    srand(time(NULL));
    int living = 0;
    bunny *temp = head;
    while(temp != NULL){
      if(temp->alive == true){
        living++;
        temp = temp->next;
      }
      else{
        temp = temp->next;
      }
    }
    if(living >= 1000){
      // perform the random cull.
      // population may not be culled in half since in temp->alive == false, then the node will be skipped and no killing will occur for
      // that iteration even if rand() % n == 0
      // This method needs improving.
      Rcout << "culling bunnies" << std::endl;
      for(int cull = 0; cull < living/2; cull++){
        bunny* temp = head;
        for(int n = 2; temp != NULL; n++){
          if(rand() % n == 0){
            if(temp->alive == true){
              temp->alive = false;
              temp->died = i;
            }
          }
          else{temp = temp->next;}
        }
      }
      Rcout << "Culling is over!" << std::endl;
    }
    return living;
  }
  
  // make new bunnies
  void createbunny(std::vector<std::string> bunnyCols, StringMatrix nameslist, int i, int b){
    srand(time(NULL));
    std::random_device gen;
    
    bunny *temp=new bunny;
    temp->id = countbunnies();
    temp->age = 0;
    temp->born = i;
    temp->alive = true;
    temp->died = -1;
    
    if(bunnyCols.size() < 1){
      std::uniform_int_distribution<int> coldist(0,3);
      temp->colour = colour[coldist(gen)];
    }
    else(temp->colour = bunnyCols[b]);
    
    std::uniform_int_distribution<int> namedist(0,nameslist.nrow() - 1);
    int n = namedist(gen);
    temp->name = nameslist(n,0);
    temp->sex = nameslist(n,1);
    
    std::uniform_int_distribution<int> mutdist(0,99);
    int mutate = mutdist(gen);
    if(mutate < 2){
      temp->mutant = true;
      temp->mutated = i;
    } else{
      temp->mutant = false;
      temp->mutated = -1;
      }
    
    temp->next=NULL;
    if(head==NULL){
      head=temp;
      tail=temp;
      temp=NULL;
    }
    else{
      tail->next=temp;
      tail=temp;
    }
  }
  
  //age and kill bunnies
  void aging(int i){
    bunny *temp=new bunny;
    temp=head;
    while(temp != NULL){
      // make bunnies older
      if(temp->alive == true){
        temp->age = i - temp->born;
      }
      // kill the bunnies
      /// normal bunnies
      if((temp->mutant == false) && (temp->age >= 10) && (temp->alive == true)){
        temp->died = i;
        temp->alive = false;
      }
      // mutant bunnies
      if((temp->mutant == true) && (temp->age >= 50) && (temp->alive == true)){
        temp->died = i;
        temp->alive = false;
      }
      temp=temp->next;
    }
  }
  
  // breeding
  void breed(StringMatrix nameslist, int i){
    int nMales = 0;
    int nFemales = 0;
    std::vector<std::string> mumCol;
    
    bunny *temp = new bunny;
    temp = head;
    while(temp != NULL){
      // count males of breeding age
      if((temp->sex == "male") && (temp->age >= 2) && (temp->mutant == false) && (temp->alive == true)){
        nMales++;
      }
      // count females of breeding age
      if((temp->sex == "female") && (temp->age >= 2) && (temp->mutant == false) && (temp->alive == true)){
        nFemales++;
        mumCol.push_back(temp->colour);
      }
      temp=temp->next;
    }
    if(nMales >= 1){
      // create a new bunny for every breeding age female IF there is at least 1 male bunny.
      for(int b = 0; b < nFemales; b++){
        createbunny(mumCol, nameslist, i, b);
      }
    }
  }
  
  // mutate a bunny for every mutant in the list
  void mutate(int i){
    srand(time(NULL));
    int nMutants = 0;
    bunny *temp = new bunny;
    temp=head;
    while(temp != NULL){
      if((temp->mutant == true) && (temp->alive == true)){
        nMutants++;
      }
      temp=temp->next;
    }
    // method to randomly select n non-mutant bunny in list.
    // Similar problem to random culling method exists here.
    if(nMutants != 0){
      for(int m = 0; m < nMutants; m++){
        bunny* temp = head;
        for(int n = 2; temp != NULL; n++){
          if(rand() % n == 0){
            if((temp->mutant == false) && (temp->alive == true)){
              temp->mutant = true;
              temp->mutated = i;
            }
          }
          else{temp = temp->next;}
        }
      }
    }
  }
  
  
  // output each bunny node
  void display(int i){
    bunny *temp=new bunny; // initialise a temp bunny node
    temp=head; // start at head of bunny list
    while(temp != NULL){ // run loop until node pointer == NULL
      Rcout << i << "\t";
      Rcout << temp->name << "\t";
      Rcout << temp->sex << "\t";
      Rcout << "born: " << temp->born << "\t";
      Rcout << "died: " << temp->died << "\t";
      Rcout << "age: " << temp->age << "\t";
      Rcout << temp->colour << "\t";
      Rcout << "mutant: "<< temp->mutant << "\t";
      Rcout << "id: " << temp->id << std::endl;
      temp=temp->next; // iterate through the list
    }
  }
  
  DataFrame getresults(){
    std::vector<int> id;
    std::vector<std::string> name;
    std::vector<std::string> sex;
    std::vector<int> age;
    std::vector<int> born;
    std::vector<int> died;
    std::vector<std::string> colour;
    std::vector<bool> mutant;
    std::vector<int> mutated;
    std::vector<bool> alive;
    
    bunny *temp=new bunny;
    temp=head;
    while(temp != NULL){
      id.push_back(temp->id);
      name.push_back(temp->name);
      sex.push_back(temp->sex);
      age.push_back(temp->age);
      born.push_back(temp->born);
      died.push_back(temp->died);
      colour.push_back(temp->colour);
      mutant.push_back(temp->mutant);
      mutated.push_back(temp->mutated);
      alive.push_back(temp->alive);
      temp=temp->next;
    }
    return DataFrame::create(Named("id")=id,
                             Named("name")=name,
                             Named("sex")=sex,
                             Named("age")=age,
                             Named("born")=born,
                             Named("died")=died,
                             Named("colour")=colour,
                             Named("mutant")=mutant,
                             Named("mutated")=mutated,
                             Named("alive")=alive);
  }
  
};

// [[Rcpp::export]]
DataFrame bunny_sim(int maxit, StringMatrix nameslist) { // switch void to DataFrame to return a DataFrame of results
  std::vector<std::string> empty;
  int i = 0;
  int b;
  int alive;
  // initialise the bunny horde
  list bunnylist;
  for(int x = 0; x < 5; x++){
    bunnylist.createbunny(empty, nameslist, i, b); // create 5 random bunnies at start
    alive = bunnylist.bunnycull(i);
  }
  
  // Start the bunny simulation
  while((alive > 0) && (i <= maxit)){
    bunnylist.aging(i);
    bunnylist.breed(nameslist, i);
    bunnylist.mutate(i);
    alive = bunnylist.bunnycull(i);
    //bunnylist.display(i);
    Rcout << alive << std::endl;
    i++;
  }
  
  return bunnylist.getresults();
  
  Rcout << "end of simulation" << std::endl;
}

