# pragma once
# include <string>

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt(int WordLength, int MaxGuesses); // remember to define the type of our parameter, here it is an 'int'
std::string GetPlayerGuess();
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess, int MaxGuesses);
void PrintGameOver();
bool AskToPlayAgain();

class FBullCowGame
{
public:
	FBullCowGame(); // this is a constructor

	int GetWordLength() const;
	int GetCurrentGuess() const;
	int GetMaximumGuesses() const;
	bool IsGameWon() const;

	void Reset(); // TODO change this from void to a more rich return value
	bool IsGuessValid(std::string PlayerGuess);
	

	int MyPublicVariable; // this is an example
private:
	// These private variables are only accessible via the functions inside of our class.
	// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example

	// These variables are 'declared' in private, but they are initialized (assigned values) in the constructor
	
	int HiddenWordLength = 10;
	int MyCurrentGuess = -19;
	int MyMaximumGuesses;
	
	/*
	a 'const' before a variable means the variable cannot be changed
	initially, 'MyMaximumGuesses' was a constant variable
	however, this lead to me being unable to assign it a value in the constructor!
	*/
};