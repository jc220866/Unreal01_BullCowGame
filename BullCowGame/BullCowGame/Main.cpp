# pragma once
# include <iostream>
# include <string>
# include "FBullCowGame.h" // "Most other classes are prefixed by F" - Unreal standards.

// FText vs FString = FStrings are mutable and can be manipulated, FText are immutable and generally used for interaction with the player.
using FText = std::string;
using int32 = int;

FBullCowGame BCGame; /* Instance of our class. This also effectively calls the BCGame.Reset() function.

					 My understanding is: When we instantiate a class, we are simply making a big block of variables
					 with default values as set in the 'constructor'. This means that we can quite easily create (and
					 keep track of the data of) a second game by creating BCGame2, for example.

					 Now that we have our class instantiated, we can edit any part of it and the changes will be saved
					 to that instance (BCGame, in this case). It's like the class is a template, a baseline for variables, and
					 we are doing a 'copy and paste' so we can make our own copy of that template and change it as we desire.
					 */

// Anything in 'main()' is the first thing our code does, the entry-point of our program.
int main()
{
	PrintIntroduction();

	do { PlayGame(); }
	while ( AskToPlayAgain() ); // Remember, boolean variables should be prefixed with a small 'b' - Unreal standards.

	return 0;
}

// Only outputs simple strings, does nothing else.
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

	return;
}

// Runs 'get guess' and 'print feedback' in a loop until the player is out of guesses.
void PlayGame()
{
	// Everything before the for loop is simply initializing the variables of our game (and printing a prompt).
	// The for loop itself simply plays the game an amount of times equal to 'MaxGuesses'.

	BCGame.Reset(); // For now, Reset() is useless because our 'CurrentGuess' is not tied to the game instance at all.
	int32 WordLength = BCGame.GetHiddenWordLength();
	int32 MaxGuesses = BCGame.GetMaximumGuesses();
	FText Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::Default;

	PrintIntroPrompt(WordLength, MaxGuesses);
	/*
	for (int CurrentGuess = 1; CurrentGuess <= MaxGuesses; CurrentGuess++)

	initially this was 'for (int CurrentGuess = 1)' because we were instantiating the guess inside the for loop
	Now, however, we have instantiated it above to fit with the variables we created above , and we can simply say the following:	
	*/
	while ( ( ! BCGame.IsGameWon() ) && ( BCGame.GetCurrentAttempt() < MaxGuesses ) )
	{
		do // loops until the guess is valid
		{
			Guess = GetPlayerGuess();
			GuessStatus = BCGame.IsGuessValid(Guess);
			PrintGuessFeedback(GuessStatus, Guess);
		}
		while (GuessStatus != EGuessStatus::OK);

		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		PrintBullsAndCows(Guess, BCGame.GetCurrentAttempt(), MaxGuesses, BullCowCount);
	}
	PrintGameSummary();

	return;
}

// Prints a prompt containing the word length that is separate from the introduction.
void PrintIntroPrompt(int32 WordLength, int32 MaxGuesses)
{
	std::cout << "________________________________________________________________________________\n";
	std::cout << "----------- Can you guess the --> " << WordLength << " <-- letter word I'm thinking of? -----------\n\n";

	std::cout << "-------------------- You have --> " << MaxGuesses << " <-- Chances to guess. ----------------------";
	std::cout << "________________________________________________________________________________\n";
}

// Receives player's input for their guess, repeats until they enter a valid guess.
FText GetPlayerGuess()
{
	FText Guess = "";

	std::cout << "Please enter your guess: ";
	std::getline(std::cin, Guess);

	return Guess;
}

// After receiving the player's guess, we give them the bulls and cows of their guess.
void PrintBullsAndCows(FText PlayerGuess, int32 CurrentGuess, int32 MaxGuesses, FBullCowCount BullCowCount)
{
	int32 RemainingGuesses = (MaxGuesses - CurrentGuess);
	int32 Bulls = BullCowCount.Bulls;
	int32 Cows = BullCowCount.Cows;

	if (RemainingGuesses == 1)	{ std::cout << "\n--- You scored " << Bulls << " bulls and " << Cows << " cows -------------------------- " << RemainingGuesses << " guess left. -----"; }
	else						{ std::cout << "\n--- You scored " << Bulls << " bulls and " << Cows << " cows -------------------------- " << RemainingGuesses << " guesses left. ---"; }

	std::cout << "________________________________________________________________________________";
	std::cout << std::endl;

	return;
}

void PrintGuessFeedback(enum EGuessStatus GuessStatus, FText PlayerGuess)
{
	switch (GuessStatus)
	{
	case EGuessStatus::Wrong_Length:
		std::cout << "\nBoi your shit too short. Or too long. One of the two.\n";
		std::cout << "________________________________________________________________________________\n";
		break;

	case EGuessStatus::Not_Alphabetical:
		std::cout << "\nBoi that ain't even a word.\n";
		std::cout << "________________________________________________________________________________\n";
		break;

	case EGuessStatus::Repeating_Letters:
		std::cout << "\nBoi that ain't no isogram, there's repeating letters.\n";
		std::cout << "________________________________________________________________________________\n";
		break;

	default: // If guess status is none of the above three, we assume the guess is OK.
		break;
	}

	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) // The user has correctly guessed the word before running out of guesses.
	{
		std::cout << "It appears that you are victorious. The hidden word was indeed '" << BCGame.GetHiddenWord() << "'.\n\n";
		
		if (BCGame.GetCurrentAttempt() == 1) // If they only took 1 guess to win (to avoid grammatical error).
		{
			std::cout << "You only used --> " << BCGame.GetCurrentAttempt() << " <-- guess. I suppose a congratulations is in order?\n\n";
		}
		else // They took multiple guesses to win.
		{
			std::cout << "You used a total of --> " << BCGame.GetCurrentAttempt() << " <-- guesses. I suppose a congratulations is in order?\n\n";
		}
		std::cout << "Running congratulations.exe...\n";
	}
	else // If we got here, the user must have ran out of guesses.
	{
		std::cout << "You have definitely lost. I can tell, because you're out of guesses. " << BCGame.GetHiddenWord() << ".\n";
	}
	return;
}

// Once the player has given a response to this prompt, we return 'true' if the first letter of response was the letter 'Y'.
bool AskToPlayAgain()
{	
	FText PlayerInput = ""; 
	char FirstLetter = '0'; // FirstLetter needs to be initialized outside of the 'do' loop, any single character value would work here.

	do 
	{
		std::cout << "________________________________________________________________________________\n";
		std::cout << "Do you want to play again?\n";
		std::cout << std::endl;

		std::getline(std::cin, PlayerInput);
		FirstLetter = tolower(PlayerInput[0]);
	} 
	while ((FirstLetter != 'y') && (FirstLetter != 'n')); // This will prompt the player to enter until they give us a Y or an N.

	return (FirstLetter == 'y');
	/*
	// As it turns out, the double pipe operator needs booleans either side of it, so 'Y' || 'y' is actually invalid.
	// Furthermore, the solution given is far, far simpler and neater.
	// Actually, I kind of want it to keep asking for either Y or N specifically, rather than "PotATO" = False.

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