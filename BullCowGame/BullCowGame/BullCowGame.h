#pragma once

void PrintIntroduction();
void PlayGame();
void PrintIntroPrompt();
std::string GetPlayerGuess();
void PrintGuessFeedback(std::string PlayerGuess, int CurrentGuess);
void PrintGameOver();
bool AskToPlayAgain();

constexpr int WORD_LENGTH = 5;
constexpr int MAX_GUESSES = 5;