# include <iostream>
# include <string>
# include "BullCowGame.h"

// This is the (first?) thing our code does, the entrypoint of our program
int main()
{
	PrintIntroduction();
	PlayGame();

	return 0;
}

// Only outputs simple strings, does nothing else
void PrintIntroduction()
{

	std::cout << "________________________________________________________________________________\n";
	std::cout << "Welcome to Bulls and Cows, a word guessing game!\n";
	std::cout << "________________________________________________________________________________\n";

	std::cout << "Every hidden word in this game is an isogram.\n";
	std::cout << "An isogram is a word with no repeating letters.\n\n";

	std::cout << "To play, simply guess a word.\n";
	std::cout << "Then we will give you hints on how to improve your guess!\n\n";

	std::cout << "If you get a COW, then one of your letters is right, but in the wrong place.\n";
	std::cout << "If you get a BULL, then one of your letters is right AND in the right place.\n";
}

// Runs 'get guess' and 'print feedback' in a loop until the player is out of guesses
void PlayGame()
{
	do
	{
		PrintIntroPrompt();

		for (int CurrentGuess = 1; CurrentGuess <= MAX_GUESSES; CurrentGuess++)
		{
			std::string Guess = GetPlayerGuess();
			PrintGuessFeedback(Guess, CurrentGuess);
		}
	} while (AskToPlayAgain());
}

// Prints a prompt containing the word length that is separate from the introduction
void PrintIntroPrompt()
{
	std::cout << "________________________________________________________________________________\n";
	std::cout << "Can you guess the --> " << WORD_LENGTH << " <-- letter word I'm thinking of?\n";
	std::cout << "________________________________________________________________________________\n";
}

// Receives player's input for their guess
std::string GetPlayerGuess()
{
	std::string Guess = "";
	std::cout << "Please enter your guess: ";
	std::getline(std::cin, Guess);
	
	return Guess;
}

// After receiving the player's guess, we give them the bulls and cows of their guess
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess)
{
	int RemainingGuesses = (MAX_GUESSES - CurrentGuess);

	if (RemainingGuesses == 1)		{ std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guess left. -----"; }
	else if (RemainingGuesses == 0) { std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guesses left. ---"; }
	else							{	std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guesses left. ---"; }

	std::cout << "________________________________________________________________________________";
	std::cout << std::endl;
}

void PrintGameOver()
{
	// std::cout << "________________________________________________________________________________\n";
	std::cout << "You lost. Probably. I can't really tell, but 0 isn't a lot of guesses. Loser.\n";
}

bool AskToPlayAgain()
{
	std::string WantsToPlayAgain = "";

	PrintGameOver();
	std::cout << "________________________________________________________________________________\n";
	std::cout << "Do you want to play again?\n";
	std::cout << std::endl;

	std::getline(std::cin, WantsToPlayAgain);

	return (WantsToPlayAgain[0] == 'Y') || (WantsToPlayAgain[0] == 'y');

	/*
	// As it turns out, the double pipe operator needs booleans either side of it, so 'Y' || 'y' is actually invalid.
	// Furthermore, the solution given is far, far simpler and neater.
	// Actually, I kind of want it to keep asking for either Y or N specifically.

	while (WantsToPlayAgain[0] != 'Y' || 'y' || 'N' || 'n')
	{
		std::cout << "________________________________________________________________________________\n";
		std::cout << "Do you want to play again?\n";
		std::cout << std::endl;

		std::getline(std::cin, WantsToPlayAgain);

		if (WantsToPlayAgain[0] == 'Y' || 'y')
		{
			return true;
		}
		else if (WantsToPlayAgain[0] == 'N' || 'n')
		{
			return false;
		}
		std::cout << "\n\nPlease enter either 'Y' or 'N'";
	}
	*/
}
