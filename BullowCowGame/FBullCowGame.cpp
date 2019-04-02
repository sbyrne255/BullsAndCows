#include "FBullCowGame.h"
#include <algorithm>
#include <String>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>


FBullCowGame::FBullCowGame() {
	Reset();
	//ConvertDictionaryToIsogramDictionary("C:\\Users\\Steven\\Desktop\\dict.txt", "isodict.txt");
	IsogramLists = MakeVectorFromIsogramFile("isodict.txt");
	return;
}
void FBullCowGame::Reset() {
	MaxTries = 6;
	CurrentTry = 1;
	Word = "planet";
	WordLength = Word.length();//Initialize after Word variable is set.
	return;
}
int FBullCowGame::GetCurrentTry() const	{ return CurrentTry; }
int FBullCowGame::GetMaxTries() const		{ return MaxTries; }
std::string FBullCowGame::GetWord() const		{ return Word; }
bool FBullCowGame::ContainsDigit(std::string input) const { return std::any_of(input.begin(), input.end(), ::isdigit); }
bool FBullCowGame::ContainsNonASCCIChars(std::string input) const { return input.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos; }


EWordStatus FBullCowGame::CheckGuessValidity(std::string Guess) const {
	int GuessLength = Guess.length();
	if (GuessLength > WordLength) { return EWordStatus::Input_Length_To_Large; }
	else if (GuessLength < WordLength) { return EWordStatus::Input_Length_To_Small; }
	else if (!IsIsorgram(Guess)) { return EWordStatus::Not_Isogram; }
	else if (ContainsDigit(Guess)) { return EWordStatus::Input_Contains_Numbers; }
	else if (!IsAllLowerCase(Guess)) { return EWordStatus::Input_Not_Lowercase; }
	else if (ContainsNonASCCIChars(Guess)) { return EWordStatus::Input_Contains_Non_ASCII; }

	return EWordStatus::OK;
}

/// <summary>Increments Bulls & Cows & increments guess count.</summary>
/// <param name="Guess">std::string Guess is passed AFTER validation to be checked against secret word.</param>  
/// <returns>Returns BullCowCount data-type with updated values from last guess.</returns> 
FBullCowCount FBullCowGame::SubmitGuess(std::string Guess) {
	CurrentTry++;
	FBullCowCount BullCowCount;
	//Considered using Hashmap, but assuming words will be small we will continue to loop.
	for (unsigned int HWChar = 0; HWChar < Word.size(); HWChar++) {
		for (unsigned int j = 0; j < Word.size(); j++) {
			if (Word[HWChar] == Guess[j]) {
				if (HWChar == j) { BullCowCount.Bulls++; }
				else{ BullCowCount.Cows++; }
			}
		}
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsorgram(std::string Guess) const
{
	std::map<char, bool> knownLetters;
	if (Guess.length() <= 1 && Guess.length() != Word.length()) { return false; }
	for (char x : Guess) {
		if (knownLetters[x]) { return false; }//Contains
		else { knownLetters[x] = true; }//add
	}
	
	return true;
}

bool FBullCowGame::IsAllLowerCase(std::string Guess) const
{
	for (char letter : Guess) {if (isupper(letter)) { return false; }}
	return true;
}

// TODO Break this function into 4 functions;
// Convert Dictionary file to ISOGRAM file (run onces) DONE
// Convert ISOGRAM file to Vector<Vector<String>> (look at serializing so I only have to run once) DONE

// Convert Vector<Vector<String>> to Vector<String> (run once per new word size)
// Randomly select List[r] and use as word at start of game. (once per game).

bool FBullCowGame::ConvertDictionaryToIsogramDictionary(std::string IFPath, std::string OPath)
{
	std::ifstream ifs(IFPath);
	std::ofstream outfile;
	std::string line;
	outfile.open(OPath, std::ios_base::app);

	while (std::getline(ifs, line))
	{
		std::cout << line;
		//If there are no Non ASCCI chars, and it's an ISOGRAM, append it to our out file.
		if ((!ContainsNonASCCIChars(line)) && (IsIsorgram(line))) {
			outfile << line << "\n";//Write line to file...
		}
	}
	return true;
}
// TODO Doesn't work properly, sets are missing and not getting allot of words into the list, feels like a double initalized vector?
std::vector<std::vector<std::string>> FBullCowGame::MakeVectorFromIsogramFile(std::string IFilePath) {
	//Open file, loop through, foreach vector entry check if first subset is the size of our word, if it IS append it, if it's NOT create new entry.
	std::vector<std::vector<std::string>> WordLists;
	std::ifstream ifs(IFilePath);
	std::ofstream infile;
	std::string line;
	int lineSize = 1;
	bool match = false;
	infile.open(IFilePath, std::ios_base::app);

	while (std::getline(ifs, line))
	{
		lineSize = line.size();

		for (unsigned int i = 0; i < WordLists.size(); i++) {//Outter
			for (unsigned int j = 0; j < WordLists[i].size(); j++) {
				int IsogramLineSize = atoi(WordLists[i][j].c_str());
				if (IsogramLineSize == lineSize) {//Word length is the same as our vector's designated length set, therefor add to it!
					match = true;
					WordLists[i][j].append(line);
					std::cout << "Adding line, word: " << line << std::endl;
					break;
				}
				else { break; }//Go to next list of words if there is one (don't look subvector as only first index holds size information)
			}
			if (match) { break; }
		}
		if (!match) {
			std::vector<std::string> x{ std::to_string(line.size()), line };//Initialize vector with size value from line.
			WordLists.push_back(x);//Add vector.
			std::cout << line;
			std::cout << std::endl;
			match = false;
		}
	}
	//Either get word length, then find if there is an existing List witht that length in slot 0.
	//If that length is in slot 0, store the value there, if not...
		//create a new list, initialize with length in slot 0, insert value.
	//When all lines are done, iterate each list (have a list of lists, 1 hold the list itself, the inner list holding the values)
	//Write to the file list[i]innerlist[j] with CSV format, then \n for list seperation, to read back, run...
	//split("\n") then split(",") per list.

	if (WordLists.size() > 0) {
		WordLists.shrink_to_fit();
		return WordLists;
	}
	else {
		return std::vector<std::vector<std::string>> {};
	}
}

std::vector<std::string> FBullCowGame::GetWordList(int WordSize) {
	std::cout << IsogramLists.size();

	for (unsigned int i = 0; i < IsogramLists.size(); i++) {//Outter
		for (unsigned int j = 0; j < IsogramLists[i].size(); j++) {
			int IsogramLineSize = atoi(IsogramLists[i][j].c_str());
			if (IsogramLineSize == WordSize) {//Word length is the same as our vector's designated length set, therefor add to it!
				return IsogramLists[i];
			}
			else { break; }//Go to next list of words if there is one (don't look subvector as only first index holds size information)
		}
	}
	return std::vector<std::string>{};

}
std::string FBullCowGame::MakeWord(int WordSize)
{
	std::vector<std::string> isograms = GetWordList(WordSize);
	if (isograms.size() < 1) {
		std::cout << "Well, this is embarrasing, we don't have ANY isograms with that length in our dictionary :/ " << std::endl;
	}
	else {
		Word = isograms[(rand() % isograms.size() + 1)];
		return Word;
	}

	return std::string();
}
// TODO add dictionary and randomly select a word. At game end, give option for new or same word.
// TODO Maybe keep track of high scores? Could be nice to implement a basic DB for this (SQLite)
// TODO

