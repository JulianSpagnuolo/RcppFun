# RcppFun
A bunch of exercises I found on a forum (http://www.cplusplus.com/forum/articles/12974/) that I decided to do using Rcpp as a way of learning both Rcpp and some basics of C++ at the same time. My solutions are in the src files along with the exercise descriptions (these will also be in the git readme). Tictactoe and dungeon functions are two "games" playable within the R console.

The post from the forum is copied below. Many thanks to the OP, these exercises were a great self-directed learning tool.

Suggested Study Order:

• variables, data types, and numerical operators
• basic input/output
• logic ( if statements, switch statements )
• loops ( for, while, do-while )
• arrays
• pseudo random number generation
• strings & string functions
• functions
• structures/classes
• enumerated data
• file input/output
• pointers
• sorting
• linked lists
• advanced classes
• recursion


_________________________________________________________________________________
Grading Program
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)

Write a program that allows the user to enter the grade scored in a programming class (0-100).
If the user scored a 100 then notify the user that they got a perfect score.

★ Modify the program so that if the user scored a 90-100 it informs the user that they scored an A

★★ Modify the program so that it will notify the user of their letter grade
0-59 F 60-69 D 70-79 C 80-89 B 90-100 A


_________________________________________________________________________________
Cola Machine
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)

Write a program that presents the user w/ a choice of your 5 favorite beverages (Coke, Water, Sprite, ... , Whatever).
Then allow the user to choose a beverage by entering a number 1-5.
Output which beverage they chose.

★ If you program uses if statements instead of a switch statement, modify it to use a switch statement.
If instead your program uses a switch statement, modify it to use if/else-if statements.

★★ Modify the program so that if the user enters a choice other than 1-5 then it will output "Error. choice was not valid, here is your money back."


_________________________________________________________________________________
While( user == gullible )
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)

Write a program that ccontinues to asks the user to enter any number other than 5 until the user enters the number 5.
Then tell the user "Hey! you weren't supposed to enter 5!" and exit the program.

★ Modify the program so that after 10 iterations if the user still hasn't entered 5 will tell the user "Wow, you're more patient then I am, you win." and exit.

★★ Modify the program so that it asks the user to enter any number other than the number equal to the number of times they've been asked to enter a number. (i.e on the first iteration "Please enter any number other than 0" and on the second iteration "Please enter any number other than 1"m etc. etc. The program must behave accordingly exiting when the user enters the number they were asked not to.)


_________________________________________________________________________________
Pancake Glutton
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Write a program that asks the user to enter the number of pancakes eaten for breakfast by 10 different people (Person 1, Person 2, ..., Person 10)
Once the data has been entered the program must analyze the data and output which person ate the most pancakes for breakfast.

★ Modify the program so that it also outputs which person ate the least number of pancakes for breakfast.

★★★★ Modify the program so that it outputs a list in order of number of pancakes eaten of all 10 people.
i.e.
Person 4: ate 10 pancakes
Person 3: ate 7 pancakes
Person 8: ate 4 pancakes
...
Person 5: ate 0 pancakes


_________________________________________________________________________________
Bracketing Search
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

★★ Modify the program so that instead of the user guessing a number the computer came up with, the computer guesses the number that the user has secretely decided. The user must tell the computer whether it guesed too high or too low.

★★★★ Modify the program so that no matter what number the user thinks of (1-100) the computer can guess it in 7 or less guesses.


_________________________________________________________________________________
Tic Tac Toe
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Make a two player tic tac toe game.

★ Modify the program so that it will announce when a player has won the game (and which player won, x or o)

★★ Modify the program so that it is a one player game against the computer (with the computer making its moves randomly)

★★★★ Modify the program so that anytime the player is about to win (aka, they have 2 of 3 x's in a row, the computer will block w/ an o)


_________________________________________________________________________________
Dungeon Crawl
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


Allow the user (marked by G in the example) to move either up, down, left, or right each turn. If the player steps on a trap then they lose. If the make it to the treasure 'X' then they win.

★★ Add enemies that move randomly in any direction once per turn. (enemies just like traps cause the player to lose if touched)

HINT: Don't let the player move off the gameboard! You program will crash if they move off the top or bottom of the board!
(the same holds true for enemies)

_________________________________________________________________________________
Fun with Functions
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

★★★ Make a function called half() that takes an integer argument. The function must print the number it received to the screen, then the program should divide that number by two to make a new number. If the new number is greater than zero the function then calls the function half() passing it the new number as its argument. If the number is zero or less than the function exits

Call the function half() with an argument of 100, the screen output should be
100
50
25
...
...
1.


_________________________________________________________________________________
Strings are your friends, until they betray you.
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


_________________________________________________________________________________
Graduation:
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
If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny.
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
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny. (if no empty square exits then the baby bunny isn't born)

★★★★★ Modify the program so that it saves each turn to a file and can play back at accelearted speed all subsequent turns.
