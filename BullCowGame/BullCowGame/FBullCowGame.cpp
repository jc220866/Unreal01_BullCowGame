# include "FBullCowGame.h"
# include <string>

// This constructor is where the game instance 'BCGame' gets its data from. 
// Values set in the constructor are RUN-TIME values. They overwrite the private variables which are COMPILE-TIME values.
FBullCowGame::FBullCowGame() { Reset(); }


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


// our Reset() method is simply meant to re-initialize our variables, effectively resetting the gamestate
void FBullCowGame::Reset()
{
	constexpr int WORD_LENGTH = 5;			// The biggest problem I had was solved by removing the 'int' in front of the variables here.
	HiddenWordLength = WORD_LENGTH;			// By putting int there, I was initializing new variables, instead of making changes to the existing ones like I actually wanted to.

	constexpr int CURRENT_GUESS = 1;			
	MyCurrentGuess = CURRENT_GUESS;

	constexpr int MAX_GUESSES = 5;
	MyMaximumGuesses = MAX_GUESSES; 

	return;
}

bool FBullCowGame::IsGuessValid(std::string PlayerGuess)
{
	return false;
}