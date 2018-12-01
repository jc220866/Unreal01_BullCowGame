# pragma once
# include <string>

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt();
std::string GetPlayerGuess();
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess, int MaxGuesses);
void PrintGameOver();
bool AskToPlayAgain();

constexpr int WORD_LENGTH = 5;

class FBullCowGame
{
public:
	void Reset(); // TODO change this from void to a more rich return value
	bool IsGameWon();
	int GetWordLength();
	int GetMaximumGuesses();
	int GetCurrentTry();
	bool IsGuessValid(std::string PlayerGuess);
	


	int MyPublicVariable;
private:
	int MyCurrentTry;
	int MyMaximumGuesses = 5;  // This private variable is only accessible via the functions inside of our class.
					// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example
};