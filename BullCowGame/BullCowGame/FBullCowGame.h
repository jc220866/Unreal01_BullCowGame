# pragma once
# include <string>
# include <array>	// We use an array to store the list of hidden words that the game randomly chooses from.

// To shorten typing time, improve readability and adhere to Unreal coding standards.
#define TArray std::array 
#define TMap std::map
using FString = std::string;
using FText = std::string;
using int32 = int;

// Here is the declaration for every function found in 'Main.cpp', excluding 'main()'.
void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt(int32 WordLength, int32 MaxGuesses);
FString GetPlayerGuess();
void PrintBullsAndCows(FText PlayerGuess, int32 CurrentGuess, int32 MaxGuesses, struct FBullCowCount);
void PrintGuessFeedback(enum EGuessStatus GuessStatus, FText PlayerGuess);
void PrintGameSummary();
bool AskToPlayAgain();

// We create a copy of this struct when checking a guess against the hidden word, allowing our return type to contain two named integer values.
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// This enum contains all possible 'errors' a guess can have, while providing us a way to name and distinguish each error, helping us to give appropriate feedback to the player.
enum EGuessStatus
{
	Default,
	Wrong_Length,
	Not_Alphabetical,
	Repeating_Letters,
	OK
};

class FBullCowGame
{
public:

	FBullCowGame(); // This is a constructor.

	void Reset();

	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;
	int32 GetCurrentAttempt() const;
	int32 GetMaximumGuesses() const;
	bool IsGameWon() const;

	EGuessStatus IsGuessValid(FString PlayerGuess);
	FBullCowCount SubmitGuess(FString PlayerGuess);

private:

	// These variables are all assigned values in the 'Reset()' method, which is called every time a new game starts.
	FString MyHiddenWord;
	int32 MyCurrentAttempt;
	int32 MyMaximumGuesses;
	bool bGameIsWon;

	// These two helper-functions are used by 'IsValidGuess()' to check if a guess has repeating letters or non-alphabet characters respectively.
	bool IsIsogram(FString PlayerGuess) const;
	bool IsAlphabetical(FString PlayerGuess) const;

	// If one wishes to add words to or remove words from this array, the number [25] must be changed according to how many words the array contains.
	// TODO Remember, every word in this list must be an isogram. A function to alert the developer if the list contains any non-isogram words would be useful.
	FString PossibleHiddenWords[25] = 
	{ 
		"Loser", "Slime", "Plane", "Right", "Score", 
		"Alien", "Robin", "Corny", "Extra", "Handy", 
		"Dingo", "Rifle", "Shark", "Topaz", "Oscar", 
		"Ripen", "Minty", "Brown", "Quiet", "Squid", 
		"Rainy", "Noise", "Tiger", "Snake", "Brine" 
	};
};
