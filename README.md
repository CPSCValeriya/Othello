# Othello
My Othello game in C++ done for a school assignment. 

The game is human vs computer. The computer uses basic AI to choose its move.

To get the best move for the computer I first create a vector of valid moves (O(n^2)), then I calculate the amount of swaps 
for each move (8 * O(n)). 
The number of swaps is what I call points.
I run calculateMostPoints() function for each value in the valid moves vector (8 * O(n)) and save their points result to a vector called points.
Then I find the max_element of that points vector and choose it to be the value I choose to do the outflank with.

Summary:
The computer finds every valid move it can play and chooses to play the move which gives it the most points (swaps). 

Complexity: O(n^2)
