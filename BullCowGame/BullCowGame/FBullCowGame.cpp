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
When I was implementing MyCurrentAttempt from a class instead of inside a for loop,
it was giving me 6 turns. That's because I forgot to say 'return MyCurrentAttempt',
it said 'return 0;', so it was returning '0', giving me an extra turn. Oops!
*/
int32 FBullCowGame::GetCurrentAttempt() const { return MyCurrentAttempt; }

int32 FBullCowGame::GetMaximumGuesses() const { return MyMaximumGuesses; } 

bool FBullCowGame::IsGameWon() const 
{ 
	return bGameIsWon; 
}
/*	
A const after a function means the function cannot change any variables
A function should be const if its only purpose is to get information or answer a question
However, functions that are not a member of a class cannot be const.	
*/

// Our Reset() method is simply meant to re-initialize our variables, effectively resetting the gamestate.
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "Loser"; // TODO get this to choose from a list (or a set/array) of words
	MyHiddenWord = HIDDEN_WORD;						
													
	constexpr int32 CURRENT_GUESS = 0;			
	MyCurrentAttempt = CURRENT_GUESS;			// The biggest problem I had was solved by removing the 'int' in front of the new (non-const) variables here.  
											// By putting int there, I was initializing new variables, instead of making changes to the existing ones like I actually wanted to.
	constexpr int32 MAX_GUESSES = 5;
	MyMaximumGuesses = MAX_GUESSES; 

	bGameIsWon = false;

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
	else if ( ! IsIsogram(PlayerGuess))
	{
		return EGuessStatus::Repeating_Letters;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString PlayerGuess) const
{
	// treat 0 and 1 length guesses as isograms, they can't possibly contain repeating characters
	if (PlayerGuess.length() <= 1) { return true; }

	// create a map of chars and bools
	TMap<char, bool> CharacterSeen;

	// for each letter in guess
	for (auto Character : PlayerGuess)
	{
		// do tolower() on the letter
		Character = tolower(Character);

		// if the letter IS already in the map
		if (CharacterSeen[Character])
		{ 
			// return false (as the guess is not an isogram)
			return false;
		}
		// else the letter is not already in the map
		else
		{ 
			// add the letter to the map (along with value of 'true' which means 'letter has been seen')
			CharacterSeen[Character] = true;
		}
	}
	return true;
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
			if (tolower(PlayerGuess[g]) == tolower(MyHiddenWord[h])) // if the letter is in the Hidden Word
			{ 
				if (g == h) // if the letter is in the right place
				{ 
					FBullCowCount.Bulls++;
				}
				else        // else the letter must be in the wrong place
				{ 
					FBullCowCount.Cows++;
				}
			}
		}			
	}
	MyCurrentAttempt++;

	if (FBullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}

	return FBullCowCount; 
}
