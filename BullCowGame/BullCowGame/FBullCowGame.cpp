# include "FBullCowGame.h"
# include <string>

void FBullCowGame::Reset()
{
	return;
}

bool FBullCowGame::IsGameWon()
{
	return false;
}

int FBullCowGame::GetWordLength()
{
	return HiddenWordLength;
}

int FBullCowGame::GetMaximumGuesses()
{
	return MyMaximumGuesses;
}

int FBullCowGame::GetCurrentGuess()
{
	return MyCurrentGuess; // When I was implementing MyCurrentGuess from a class instead of inside a for loop, 
						   // it was giving me 6 turns. That's because I forgot to say 'return MyCurrentGuess',
						   // it was returning '0', giving me an extra turn. Oops!
}

bool FBullCowGame::IsGuessValid(std::string PlayerGuess)
{
	return false;
}
