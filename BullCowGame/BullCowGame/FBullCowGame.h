# pragma once
# include <string>

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt(int WordLength, int MaxGuesses); // Remember to define the type of our parameter. For example, here it is an 'int'.
std::string GetPlayerGuess();
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess, int MaxGuesses);
void PrintGameOver();
bool AskToPlayAgain();

class FBullCowGame
{
public:
	FBullCowGame(); // This is a constructor.

	int GetWordLength() const;
	int GetCurrentGuess() const;
	int GetMaximumGuesses() const;
	bool IsGameWon() const;

	void Reset(); // TODO change this from void to a more rich return value
	bool IsGuessValid(std::string PlayerGuess);
	
private:
	// These private variables are only accessible via the functions inside of our class.
	// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example.

	// These variables are 'declared' AND 'initialized' here in private at compile-time, but are assigned NEW values in the constructor at run-time.
	int HiddenWordLength;
	int MyCurrentGuess;
	int MyMaximumGuesses;
	
	/*
	A 'const' before a variable means the variable cannot be changed.
	Initially, 'MyMaximumGuesses' was a constant variable. However, this lead to me being unable to change its value in the constructor!
	The solution was to create a constant variable, then assign MyMaximumGuesses the value of that constant variable.
	*/
};