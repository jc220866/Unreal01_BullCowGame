# pragma once
# include <string>
# include <map>

#define TMap std::map
/*
Incase you're wondering why we can't just use 'using' here, that's essentially because std::map requires parameters (<char, bool>).
We could say " using TMap = std::map<char, bool>; ", that would be valid, if not a little specific and restrictive.
https://community.gamedev.tv/t/using-std-map/34204/9
*/

/*
// TODO advanced data types to keep an eye on: 
Map (same as 'dict'?), 
Set (basically a list?),
Array (owo whats this), 
std::pair (used in structs to essentially create a tuple)
*/

// FText vs FString = FStrings are mutable and can be manipulated, FText are immutable and generally used for interaction with the player.
using FString = std::string;
using int32 = int;

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt(int32 WordLength, int32 MaxGuesses); // Remember to define the type of our parameter. For example, here it is an 'int'.
FString GetPlayerGuess();
void PrintBullsAndCows(FString PlayerGuess, int32 CurrentGuess, int32 MaxGuesses, struct FBullCowCount); // This shows an error because string's alias in main.cpp is 'FText'. 
void PrintGuessFeedback(enum EGuessStatus GuessStatus, FString PlayerGuess);
void PrintGameSummary();
bool AskToPlayAgain();

// Values of 'bulls' and 'cows' initialized to 0.
struct FBullCowCount
{
	int32 Bulls = 0; // A struct is the same as a class, except its members are public by default. This means structs are idea for grouping together variables of simple data types.
	int32 Cows = 0; // Our struct was causing errors around 'SubmitGuess()' when placed below the class.
};

// enum class EGuessStatus
enum EGuessStatus
{
	Default,			// It's good practice to make an initial value with which to declare the status.
	Wrong_Length,		// Length of the guess is not equal to the length of the hidden word.
	Not_Alphabetical,	// Non-letter characters were entered, such as '0' or '!'.
	Repeating_Letters,	// Letters are repeating, meaning the guess is not an isogram.
	OK
};

class FBullCowGame
{
public:
	FBullCowGame(); // This is a constructor.

	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;
	int32 GetCurrentAttempt() const;
	int32 GetMaximumGuesses() const;
	bool IsGameWon() const;

	void Reset(); // TODO change this from void to a more rich return value
	EGuessStatus IsGuessValid(FString PlayerGuess);

	FBullCowCount SubmitGuess(FString PlayerGuess);
	
private:
	// These private variables are only accessible via the functions inside of our class.
	// Whereas public variables would be accessible anywhere via BCGame.MyPublicVariable, for example.

	// These variables are 'declared' AND 'initialized' here in private at compile-time, but are assigned NEW values in the constructor at run-time.
	FString MyHiddenWord;
	int32 MyCurrentAttempt;
	int32 MyMaximumGuesses;
	bool bGameIsWon;
	/*
	A 'const' before a variable means the variable cannot be modified.
	Initially, 'MyMaximumGuesses' was a constant variable. However, this lead to me being unable to change its value in the constructor!
	The solution was to create a constant variable, then assign MyMaximumGuesses the value of that constant variable.
	*/

	bool IsIsogram(FString PlayerGuess) const;
	bool IsAlphabetical(FString PlayerGuess) const;
	void ReportBug(FString LocationOfError) const;
};
