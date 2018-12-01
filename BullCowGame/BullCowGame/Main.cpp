# include <iostream>
# include <string>
# include "FBullCowGame.h" // "Most other classes are prefixed by F" - Unreal standards

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
	FBullCowGame BCGame; /*Instance of our class.

	My understanding is: When we instantiate a class, we are simply making a big block of variables
	with default values as set in the header file. This means that we can quite easily create (and
	keep track of the data of) a second game by creating BCGame2, for example.

		Now that we have our class instantiated, we can edit any part of it and the changes will be saved
	to that instance (BCGame, in this case). It's like the class is a template, a baseline for variables, and
	we are doing a 'copy and paste' so we can make our own copy of that template and change it as we desire.
	*/

	int WordLength = BCGame.GetWordLength();
	int MaxGuesses = BCGame.GetMaximumGuesses();
	int CurrentGuess = BCGame.GetCurrentGuess();

	do
	{
		PrintIntroPrompt(WordLength);
		/*
		for (int CurrentGuess = 1; CurrentGuess <= MaxGuesses; CurrentGuess++)

		initially this was 'for (int CurrentGuess = 1)' because we were instantiating the guess inside the for loop
		Now, however, we have instantiated it above to fit with our class, and we can simply say the following:
		*/
		for (CurrentGuess; CurrentGuess <= MaxGuesses; CurrentGuess++)
		{
			std::string Guess = GetPlayerGuess();
			PrintGuessFeedback(Guess, CurrentGuess, MaxGuesses);
		}
	} while (AskToPlayAgain()); // Remember, boolean variables should be prefixed with a small 'b' - Unreal standards
}

// Prints a prompt containing the word length that is separate from the introduction
void PrintIntroPrompt(int WordLength)
{
	std::cout << "________________________________________________________________________________\n";
	std::cout << "Can you guess the --> " << WordLength << " <-- letter word I'm thinking of?\n";
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
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess, int MaxGuesses)
{
	int RemainingGuesses = (MaxGuesses - CurrentGuess);

	if (RemainingGuesses == 1)		{ std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guess left. -----"; }
	else if (RemainingGuesses == 0) { std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guesses left. ---"; }
	else							{	std::cout << "\n--- You scored 0 bulls and 0 cows -------------------------- " << RemainingGuesses << " guesses left. ---"; }

	std::cout << "________________________________________________________________________________";
	std::cout << std::endl;
}

// Once the player has ran out of guesses, we taunt them for it
void PrintGameOver()
{
	// std::cout << "________________________________________________________________________________\n";
	std::cout << "You lost. Probably. I can't really tell, but 0 isn't a lot of guesses. Loser.\n";
}

// Once the player has given a response to this prompt, we return 'true' if the first letter of response was the letter 'Y'
bool AskToPlayAgain()
{
	std::string PlayerInput = "";

	PrintGameOver();
	std::cout << "________________________________________________________________________________\n";
	std::cout << "Do you want to play again?\n";
	std::cout << std::endl;

	std::getline(std::cin, PlayerInput);

	return (PlayerInput[0] == 'Y') || (PlayerInput[0] == 'y');

	/*
	// As it turns out, the double pipe operator needs booleans either side of it, so 'Y' || 'y' is actually invalid.
	// Furthermore, the solution given is far, far simpler and neater.
	// Actually, I kind of want it to keep asking for either Y or N specifically, rather than "PotATO" = False

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
