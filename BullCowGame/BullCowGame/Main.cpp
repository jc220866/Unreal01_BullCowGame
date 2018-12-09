# pragma once
# include <iostream>
# include <string>
# include "FBullCowGame.h" // "Most other classes are prefixed by F" - Unreal standards.

// To shorten typing time, improve readability and adhere to Unreal coding standards.
using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // Instance of our class. This also effectively calls the BCGame.Reset() function, because it calls the 'constructor'.

// Anything in 'main()' is the first thing our code does, the entry-point of our program.
int main()
{
	PrintIntroduction();

	do { PlayGame(); }
	while ( AskToPlayAgain() ); // If 'AskToPlayAgain() returns 'false', we leave the do-while loop and the program exits.

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

// This function is where everything short of "do you want to play again?" happens, including initializing and resetting all variables of the game.
void PlayGame()
{
	// Everything before the for loop is simply initializing the variables of our game (and printing a prompt).
	BCGame.Reset();
	int32 WordLength = BCGame.GetHiddenWordLength(); // We define variables for WordLength and MaxGuesses to improve readability.
	int32 MaxGuesses = BCGame.GetMaximumGuesses();	// We can afford to do this because neither of these values could possibly change until a new game starts.
	FText Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::Default;  // We set a default value to 'GuessStatus' to say that the guess (which doesn't exist yet) is neither valid nor invalid.

	PrintIntroPrompt(WordLength, MaxGuesses);

	while ( ( ! BCGame.IsGameWon() ) && ( BCGame.GetCurrentAttempt() < MaxGuesses ) )
	{
		do // Loops until the guess is valid.
		{
			Guess = GetPlayerGuess();
			GuessStatus = BCGame.IsGuessValid(Guess);
			PrintGuessFeedback(GuessStatus, Guess);	 // - - - - - - - - - - - - - - - - -  This function prints feedback for each INVALID guess.
		}
		while (GuessStatus != EGuessStatus::OK);

		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		PrintBullsAndCows(Guess, BCGame.GetCurrentAttempt(), MaxGuesses, BullCowCount); // This function prints feedback for each VALID guess.
	}
	PrintGameSummary();  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  This function prints feedback once the game is either won or lost.

	return;
}

// Prints a prompt containing the word length that is separate from the introduction.
// TODO Windows 10's cmd window can be varied in size, causing our game to look messy. Either find a way to lock the size or a way to work around a window with adjustable size.
void PrintIntroPrompt(int32 WordLength, int32 MaxGuesses)
{
	std::cout << "________________________________________________________________________________\n";
	std::cout << "----------- Can you guess the --> " << WordLength << " <-- letter word I'm thinking of? -----------\n\n";

	std::cout << "-------------------- You have --> " << MaxGuesses << " <-- Chances to guess. ----------------------";
	std::cout << "________________________________________________________________________________\n";
}

// Receives player's input for their guess. Returns the player's guess.
FText GetPlayerGuess()
{
	FText Guess = "";

	std::cout << "Please enter your guess: ";
	std::getline(std::cin, Guess);

	return Guess;
}

// Prints feedback for invalid guesses, guiding the player towards entering a valid, alphabetical isogram of appropriate length.
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

// After submitting the player's guess (after checking it was valid), we give them the bulls and cows of their guess.
void PrintBullsAndCows(FText PlayerGuess, int32 CurrentGuess, int32 MaxGuesses, FBullCowCount BullCowCount)
{
	int32 RemainingGuesses = (MaxGuesses - CurrentGuess); // Instead of telling the player what turn they're on, we tell them how many they have left.
	int32 Bulls = BullCowCount.Bulls;
	int32 Cows = BullCowCount.Cows;

	if (RemainingGuesses == 1) // To avoid grammatical errors in cases where the player has only 1 guess remaining. "1 guesses left" sounds strange.
	{ 
		std::cout << "\n--- You scored " << Bulls << " bulls and " << Cows << " cows -------------------------- " << RemainingGuesses << " guess left. -----"; 
	}
	else 
	{ 
		std::cout << "\n--- You scored " << Bulls << " bulls and " << Cows << " cows -------------------------- " << RemainingGuesses << " guesses left. ---"; 
	}
	std::cout << "________________________________________________________________________________";
	std::cout << std::endl;

	return;
}

// Once a game has finished, we let the user know how many guesses they took to win (or we taunt them with the hidden word if they lost).
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "It appears that you are victorious. The hidden word was indeed '" << BCGame.GetHiddenWord() << "'.\n\n";
		
		if (BCGame.GetCurrentAttempt() == 1) // If they only took 1 guess to win (to avoid grammatical error).
		{
			std::cout << "You only used --> " << BCGame.GetCurrentAttempt() << " <-- guess. I suppose a congratulations is in order?\n\n";
		}
		else
		{
			std::cout << "You used a total of --> " << BCGame.GetCurrentAttempt() << " <-- guesses. I suppose a congratulations is in order?\n\n";
		}
		std::cout << "Running congratulations.exe...\n";
	}
	else // If we got here, the user must have ran out of guesses and subsequently, lost.
	{
		std::cout << "You have definitely lost. I can tell, because you're out of guesses. " << BCGame.GetHiddenWord() << ".\n";
	}
	return;
}

// Uses the first letter of the player's input to determine whether they want to play another game.
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
		FirstLetter = tolower(PlayerInput[0]); // Changing FirstLetter to lowercase allows us to accept mixed-case "Y" and "y" as valid input,
	} 
	while ((FirstLetter != 'y') && (FirstLetter != 'n')); // This will prompt the player to enter until they give us a Y or an N.

	return (FirstLetter == 'y');  // If the player said 'yes', we return true and the game restarts. If the player said "no", the game returns false and the program closes.
}
