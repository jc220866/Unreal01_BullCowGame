# include "FBullCowGame.h"
# include <string>

using FString = std::string;
using int32 = int;

// This constructor is where the game instance 'BCGame' gets its data from. 
// Values set in the constructor are RUN-TIME values. They overwrite the private variables which are COMPILE-TIME values.
FBullCowGame::FBullCowGame() { Reset(); }


FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
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
													
	constexpr int32 CURRENT_GUESS = 1;			
	MyCurrentGuess = CURRENT_GUESS;			// The biggest problem I had was solved by removing the 'int' in front of the new (non-const) variables here.  
											// By putting int there, I was initializing new variables, instead of making changes to the existing ones like I actually wanted to.
	constexpr int32 MAX_GUESSES = 5;
	MyMaximumGuesses = MAX_GUESSES; 

	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString PlayerGuess)
{
	// if the guess is not the same length as the hidden word
	if (PlayerGuess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	// if the guess is not entirely alphabetical
	else if (false)
	{
		return EGuessStatus::Not_Alphabetical;
	}
	// if the guess has repeating letters
	else if (false)
	{
		return EGuessStatus::Repeating_Letters;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
/*
FBullCowCount FBullCowGame::SubmitGuess(FString PlayerGuess)
{
	return FBullCowCount();
}

Remember to go through the class when creating definitions for class functions.
*/
// here will be a function that counts bulls and cows, submits a VALID guess and then increases the turn count
FBullCowCount FBullCowGame::SubmitGuess(FString PlayerGuess)
{
	FBullCowCount FBullCowCount;

	for (int32 g = 0; g < GetHiddenWordLength(); g++) // For all letters in 'Guess'
	{
		for (int32 h = 0; h < GetHiddenWordLength(); h++) // For all letters in 'HiddenWord'
		{ 
			if (PlayerGuess[g] == MyHiddenWord[h]) // if the letter is in the Hidden Word
			{ 
				if (g == h) // if the letter is in the right place
				{ 
					FBullCowCount.Bulls++;
				}
				else                      // else the letter must be in the wrong place
				{ 
					FBullCowCount.Cows++;
				}
			}
		}			
	}
	MyCurrentGuess++;

	return FBullCowCount;  // This function has a return type of 'struct'. I'm not sure why we need parentheses after the struct...
}