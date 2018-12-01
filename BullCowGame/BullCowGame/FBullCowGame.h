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
	void Reset(); // TODO change this from void to a more rich return value
	bool IsGameWon();
	int GetWordLength();
	int GetMaximumGuesses();
	int GetCurrentGuess();
	bool IsGuessValid(std::string PlayerGuess);
	


	int MyPublicVariable;
private:
	int HiddenWordLength = 5;
	int MyCurrentGuess = 1;
	int MyMaximumGuesses = 5;  // This private variable is only accessible via the functions inside of our class.
					// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example
};