# include <iostream>
# include <string>

void PrintIntroduction();
std::string GetPlayerGuess();
void PrintGuessFeedback(std::string PlayerGuess);
void BreakTheInternet(std::string PlayerGuess);

constexpr int WORD_LENGTH = 5;

// Only outputs strings, does nothing else
void PrintIntroduction()
{
	std::cout << "Welcome to Bulls and Cows, a word guessing game!\n\n";

	std::cout << "Every hidden word in this game is an isogram.\n";
	std::cout << "An isogram is a word with no repeating letters.\n";
	std::cout << "To play, simply guess a word.\n";
	std::cout << "Then we will give you hints on how to improve your guess!\n";
	std::cout << "If you get a COW, then one of your letters is right, but in the wrong place.\n";
	std::cout << "If you get a BULL, then one of your letters is right AND in the right place.\n\n";
}

// This is the first thing our code does, the entrypoint of our program
int main()
{
	PrintIntroduction();
	std::string Guess = GetPlayerGuess();
	std::cout << "\n\nHello World\n\n";
	BreakTheInternet(Guess);

	return 0;
}


// Receives player's input for their guess
std::string GetPlayerGuess()
{
	std::cout << "Can you guess the --> " << WORD_LENGTH << " <-- letter word I'm thinking of?\n";
	std::cout << "________________________________________________________________________________\n\n";

	std::string Guess = "";
	while (Guess != "despacito")
	{
		std::cout << "Please enter your guess:\n";
		std::getline(std::cin, Guess);
		PrintGuessFeedback(Guess);
	}
	return Guess;
}

// After receiving the player's guess, we repeat it to them
void PrintGuessFeedback(std::string PlayerGuess)
{
	std::cout << "Your guess was: " << PlayerGuess << "\n\n";
}

// When the player enters THAT word, we print it infinitely until the end of time and beyond
void BreakTheInternet(std::string PlayerGuess)
{
	while (true)
	{
		std::cout << PlayerGuess << "\n";
	}
}