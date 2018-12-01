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
	return 0;
}

int FBullCowGame::GetMaximumGuesses()
{
	return MyMaximumGuesses;
}

int FBullCowGame::GetCurrentTry()
{
	return 0;
}

bool FBullCowGame::IsGuessValid(std::string PlayerGuess)
{
	return false;
}
