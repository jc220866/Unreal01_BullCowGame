# include "FBullCowGame.h"
# include <string>

using FString = std::string;
using int32 = int;

// This constructor is where the game instance 'BCGame' gets its data from. 
// Values set in the constructor are RUN-TIME values. They overwrite the private variables which are COMPILE-TIME values.
FBullCowGame::FBullCowGame() { Reset(); }


FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }

int32 FBullCowGame::GetWordLength() const { return HiddenWordLength; }
/*
When I was implementing MyCurrentGuess from a class instead of inside a for loop,
it was giving me 6 turns. That's because I forgot to say 'return MyCurrentGuess',
it said 'return 0;', so it was returning '0', giving me an extra turn. Oops!
*/
int32 FBullCowGame::GetCurrentGuess() const { return MyCurrentGuess; }

int32 FBullCowGame::GetMaximumGuesses() const { return MyMaximumGuesses; } 

bool FBullCowGame::IsGameWon() const { return false; }
/*	A const after a function means the function cannot change any variables
	A function should be const if its only purpose is to get information or answer a question

	However, functions that are not a member of a class cannot be const.	*/


// Our Reset() method is simply meant to re-initialize our variables, effectively resetting the gamestate.
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "Loser";
	MyHiddenWord = HIDDEN_WORD;

	constexpr int32 WORD_LENGTH = 5;			// The biggest problem I had was solved by removing the 'int' in front of the variables here.
	HiddenWordLength = WORD_LENGTH;			// By putting int there, I was initializing new variables, instead of making changes to the existing ones like I actually wanted to.

	constexpr int32 CURRENT_GUESS = 1;			
	MyCurrentGuess = CURRENT_GUESS;

	constexpr int32 MAX_GUESSES = 5;
	MyMaximumGuesses = MAX_GUESSES; 

	return;
}

bool FBullCowGame::IsGuessValid(FString PlayerGuess)
{
	return false;
}
/*
BullCowCount FBullCowGame::SubmitGuess(FString PlayerGuess)
{
	return BullCowCount();
}

Remember to go through the class when creating definitions for class functions.
*/
// here will be a function that counts bulls and cows, submits a VALID guess and then increases the turn count
BullCowCount FBullCowGame::SubmitGuess(FString)
{
	// increment current guess

	// Setup a return variable (why?)
	BullCowCount BullCowCount;

	// loop through all letters in the guess
	// compare letters against the hidden word

	return BullCowCount;  // This function has a return type of 'struct'. I'm not sure why we need parentheses after the struct...
}