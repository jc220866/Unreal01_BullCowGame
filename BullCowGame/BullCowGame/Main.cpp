# include <iostream>
# include <string>

int main()
{
	constexpr int WORD_LENGTH = 5;

	std::cout << "Welcome to Bulls and Cows!\n\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " word I'm thinking of?\n\n";

	std::string Guess = "";
	while (Guess != "despacito")
	{ 
		std::cout << "Please enter your guess:\n";
		std::getline (std::cin, Guess);
		std::cout << "Your guess was: " << Guess << ".\n\n";
	}

	return 0;
}