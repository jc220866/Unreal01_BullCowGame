# pragma once
# include <string>

// FText vs FString = FStrings are mutable and can be manipulated, FText are immutable and generally used for interaction with the player.
using FString = std::string;
using int32 = int;

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt(int32 WordLength, int32 MaxGuesses); // Remember to define the type of our parameter. For example, here it is an 'int'.
FString GetPlayerGuess();
void PrintGuessFeedback(FString PlayerGuess, int32 CurrentGuess, int32 MaxGuesses);
void PrintGameOver();
bool AskToPlayAgain();

class FBullCowGame
{
public:
	FBullCowGame(); // This is a constructor.

	int32 GetWordLength() const;
	int32 GetCurrentGuess() const;
	int32 GetMaximumGuesses() const;
	bool IsGameWon() const;

	void Reset(); // TODO change this from void to a more rich return value
	bool IsGuessValid(FString PlayerGuess);
	// here will be a function that counts bulls and cows, submits a VALID guess and then increases the turn count
	
private:
	// These private variables are only accessible via the functions inside of our class.
	// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example.

	// These variables are 'declared' AND 'initialized' here in private at compile-time, but are assigned NEW values in the constructor at run-time.
	int32 HiddenWordLength;
	int32 MyCurrentGuess;
	int32 MyMaximumGuesses;
	
	/*
	A 'const' before a variable means the variable cannot be changed.
	Initially, 'MyMaximumGuesses' was a constant variable. However, this lead to me being unable to change its value in the constructor!
	The solution was to create a constant variable, then assign MyMaximumGuesses the value of that constant variable.
	*/
};