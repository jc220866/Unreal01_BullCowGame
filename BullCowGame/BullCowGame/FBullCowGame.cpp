# include "FBullCowGame.h"
# include <string>

int FBullCowGame::GetWordLength() const { return HiddenWordLength; }
/*
When I was implementing MyCurrentGuess from a class instead of inside a for loop,
it was giving me 6 turns. That's because I forgot to say 'return MyCurrentGuess',
it said 'return 0;', so it was returning '0', giving me an extra turn. Oops!
*/
int FBullCowGame::GetCurrentGuess() const { return MyCurrentGuess; }

int FBullCowGame::GetMaximumGuesses() const { return MyMaximumGuesses; } 

bool FBullCowGame::IsGameWon() const { return false; }
/*	A const after a function means the function cannot change any variables
	A function should be const if its only purpose is to get information or answer a question

	However, functions that are not a member of a class cannot be const.	*/

// This constructor is where the game instance 'BCGame' gets its data from. 
// Values set in the constructor are RUN-TIME values. They overwrite the private variables which are COMPILE-TIME values.
FBullCowGame::FBullCowGame() { Reset(); }

// our Reset() method is simply meant to re-initialize our variables, effectively resetting the gamestate
void FBullCowGame::Reset()
{
	int HiddenWordLength = 5;
	int MyCurrentGuess = 1;

	constexpr int MAX_TRIES = 5;
	int MyMaximumGuesses = MAX_TRIES;

	return;
}

bool FBullCowGame::IsGuessValid(std::string PlayerGuess)
{
	return false;
}