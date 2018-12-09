# pragma once
# include "FBullCowGame.h"
# include <string>
# include <iostream>// Input output stream in this file is exclusively used for the 'report bug' function.
# include <map>		// We use a map to check if the player's guess is an isogram by storing letters and marking them as 'seen' with a boolean.
# include <random>	// We use random to choose a random word from our array of possible hidden words.

// To shorten typing time, improve readability and adhere to Unreal coding standards.
using FString = std::string;
using int32 = int;

// We put Reset() in the constructor so that Reset() is called when we define a game instance at the start of our game in the main.cpp
FBullCowGame::FBullCowGame() { Reset(); } 

// All of our 'getter' methods are grouped together and made const. Their only purpose is to return a variable when called.
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentAttempt() const { return MyCurrentAttempt; }
int32 FBullCowGame::GetMaximumGuesses() const { return MyMaximumGuesses; }
bool FBullCowGame::IsGameWon() const {return bGameIsWon; }

// Our Reset() method is simply meant to re-initialize our variables, effectively resetting the gamestate.
void FBullCowGame::Reset()
{
	// To calculate the amount of elements in our array (for the random function), we need to get the total bytes of the array and divide it by the total bytes of one element.
	int random = rand() % (sizeof(PossibleHiddenWords) / sizeof(PossibleHiddenWords[0])); 
	const FString HIDDEN_WORD = PossibleHiddenWords[rand() % random]; 
	MyHiddenWord = HIDDEN_WORD;

	constexpr int32 CURRENT_GUESS = 0;
	MyCurrentAttempt = CURRENT_GUESS;

	constexpr int32 MAX_GUESSES = 9; // Here is the ONLY place where we determine the amount of attempts the player has to guess the hidden word.
	MyMaximumGuesses = MAX_GUESSES;

	bGameIsWon = false;

	return;
}

// We pass the players guess into here before 'submitting' it. We need to check that it is a valid, alphabetical isogram of appropriate length.
// If a guess fails any of these checks, the enum value we return decides what feedback we give to the player to improve their next guess.
EGuessStatus FBullCowGame::IsGuessValid(FString PlayerGuess)
{
	if (PlayerGuess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length; 
	}
	else if ( ! IsAlphabetical(PlayerGuess))
	{
		return EGuessStatus::Not_Alphabetical;
	}
	else if ( ! IsIsogram(PlayerGuess))
	{
		return EGuessStatus::Repeating_Letters;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// Checks to see if any single character in a guess appears twice. We use the term 'character' as this function also works for numbers and symbols.
bool FBullCowGame::IsIsogram(FString PlayerGuess) const
{
	// We treat 0 and 1 length guesses as isograms, they can't contain repeating characters. We do this to prevent the rest of this code from running, improving performance.
	if (PlayerGuess.length() <= 1) { return true; } 

	TMap<char, bool> CharacterSeen; // Here we will store each letter of a guess and mark them as 'seen' with the value of 'true'.

	for (auto Character : PlayerGuess)
	{
		Character = tolower(Character); // Because our map doesn't see capital 'X' and lowercase 'x' as the same letter.

		// This if-statement adds the character to the map (if it wasn't already) and checks if it has a value of 'true' (in other words, 'already seen').
		if (CharacterSeen[Character])
		{
			return false;
		}
		else  // Else the character wasn't already 'seen' and didn't have the value of 'true'.
		{
			CharacterSeen[Character] = true;  // Set the value to 'true' so that next time we check the character, we will know we have already 'seen' it.
		}
	}
	return true;
}

bool FBullCowGame::IsAlphabetical(FString PlayerGuess) const
{
	if (PlayerGuess.length() == 0) { return false; } // If the guess is empty, it's not alphabetical.

	FString Alphabet = "abcdefghijklmnopqrstuvwxyz"; // We will use this string to check if a character is or is not in the alphabet.

	for (auto Character : PlayerGuess) // For every character in the guess.
	{
		Character = tolower(Character); // TODO We could have included capital letters in our 'Alphabet' string instead, we should check to see which case has best performance.
		int PositionOfCharacterInAlphabet = Alphabet.find(Character);

		if (PositionOfCharacterInAlphabet == -1) // The .find() function returns -1 if the character is NOT found in our string 'Alphabet'.
		{
			return false;
		}
		else
		{
			break; // Do nothing. We don't want to return 'true' until we have interrogated ALL characters in the guess.
		}
	}
	return true;
}

// Once a guess is deemed 'valid', we remove one of the player's remaining turns, compare the guess against the hidden word, count the 'bulls' and 'cows' & check if game is won.
FBullCowCount FBullCowGame::SubmitGuess(FString PlayerGuess)
{
	MyCurrentAttempt++;
	FBullCowCount FBullCowCount; // Instead of modifying our struct, we create a 'copy' exclusively for this guess to prevent us needing to reset the values to 0 afterwards.

	for (int32 g = 0; g < GetHiddenWordLength(); g++) // For all letters in 'Guess'.
	{
		for (int32 h = 0; h < GetHiddenWordLength(); h++) // For all letters in 'HiddenWord'.
		{ 
			if (tolower(PlayerGuess[g]) == tolower(MyHiddenWord[h])) // Here we check if any letter in 'Guess' matches any letter in 'HiddenWord', while making them lowercase.
			{ 
				if (g == h) // If a letter in 'Guess' is found in 'HiddenWord', we check if it's in the right place. If it is, it is a 'bull'.
				{ 
					FBullCowCount.Bulls++;
				}
				else        // Else the letter must be in the wrong place, it is a 'cow'.
				{ 
					FBullCowCount.Cows++;
				}
			}
		}			
	}

	// Instead of checking if 'Guess' matches 'HiddenWord', we check if every individual letter is correct. This allows us to accept mixed-case letters in a valid guess.
	if (FBullCowCount.Bulls == GetHiddenWordLength()) 
	{
		bGameIsWon = true;
	}
	return FBullCowCount; 
}
