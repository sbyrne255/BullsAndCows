//Declar includes
#include <iostream>
#include <string>
#include "FBullCowGame.h"
using FText = std::string;
//using int = int;

//Prototype/Declar functions.
FText GetGuess();
void WelcomeMenu();
void PlayGame();
bool AskToPlayAgain();
void AskForWordLength();
FBullCowGame BCGame;

int main() {	
	do {
		WelcomeMenu();
		AskForWordLength();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

/// <summary>Prints a welcome screen before the game starts</summary>
/// <returns>No return value given, outputs to screen.</returns> 
void WelcomeMenu() {
	std::cout
		<< "--------------------------------------------------------------------------------" << "\n"
		<< "----------------------------Welcome to Bulls and Cows---------------------------" << "\n"
		<< "--------------------------------------------------------------------------------" << "\n"
		<< "\n"
		<< "Guess the isogram! Each word is "
		<< BCGame.GetWord().length()
		<< " letters long with no repeating letters."
		<< std::endl;
	return;
}

void AskForWordLength() {
	FText size = "";
	std::cout << "Please enter the length of the isogram you'd like to try an guess: ";
	std::getline(std::cin, size);
	std::cout << std::endl;
	int IsogramWordSize = atoi(size.c_str());
	BCGame.MakeWord(IsogramWordSize);
	return;
}
/// <summary>Asks user for Guess, runs verification guess is valid.</summary>
/// <returns>Returns FText IF guess meets validation else repeats until valid input is given. </returns> 
FText GetGuess() {
	EWordStatus GuessStatus = EWordStatus::Unspecified_Error;
	FText Guess = "";
	do {
		std::cout << "Enter Guess: ";
		std::getline(std::cin, Guess);
		GuessStatus = BCGame.CheckGuessValidity(Guess);
		switch (GuessStatus) {
		case EWordStatus::Input_Length_To_Large:
			std::cout << "Input to large, please enter a " << BCGame.GetWord().length() << " letter word. \n";
			break;
		case EWordStatus::Input_Length_To_Small:
			std::cout << "Input to small, please enter a " << BCGame.GetWord().length() << " letter word. \n";
			break;
		case EWordStatus::Input_Contains_Numbers:
			std::cout << "Input contains numbers. Please use only ASCII letters. \n";
			break;
		case EWordStatus::Input_Contains_Non_ASCII:
			std::cout << "Input contains none ASCII text. Please only use ASCII letters. \n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Input is not an isogram (no repeating letters). \n";
			break;
		case EWordStatus::Input_Not_Lowercase:
			std::cout << "Input is not in lower case, please submit all guesses as lower case. \n";
			break;
		default:
			break;
		}
	} while (GuessStatus != EWordStatus::OK);
	return Guess;
}

// TODO Keep array of guess, if guess already been tried, reject it.
void PlayGame() {
	BCGame.Reset();
	do {
		FBullCowCount BullCows = BCGame.SubmitGuess(GetGuess());
		if (BullCows.Bulls == BCGame.GetWord().length()) {//You won!
			//Call win function
			std::cout << "YOU WON!" << std::endl;
			return;
		}
		std::cout << "Bulls = " << BullCows.Bulls;
		std::cout << " Cows = " << BullCows.Cows << std::endl; 
	} while (BCGame.GetCurrentTry() < BCGame.GetMaxTries());
	//Call loose function



}
bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return ((Response[0] == 'Y') || (Response[0] == 'y'));
}
