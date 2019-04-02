#pragma once
#include <String>
#include <vector>

struct FBullCowCount {
	int Bulls = 0;
	int Cows = 0;
};
enum class EWordStatus {
	OK,
	Not_Isogram,
	Input_Length_To_Large,
	Input_Length_To_Small,
	Input_Contains_Non_ASCII,
	Input_Contains_Numbers,
	Input_Not_Lowercase,
	Unspecified_Error
};

class FBullCowGame {
public:
	FBullCowGame();
	int GetCurrentTry() const;
	int GetMaxTries() const;
	std::string GetWord() const;
	bool ContainsDigit(std::string) const;
	bool ContainsNonASCCIChars(std::string) const;
	EWordStatus CheckGuessValidity(std::string) const;
	void Reset(); // TODO Make a return value based on reset
	FBullCowCount SubmitGuess(std::string);
	std::string MakeWord(int);
	
private:
	//See contruct for initialization.
	int CurrentTry;
	int MaxTries;
	int WordLength;
	std::string Word;
	bool IsIsorgram(std::string) const;
	bool IsAllLowerCase(std::string) const;
	bool ConvertDictionaryToIsogramDictionary(std::string, std::string);
	std::vector<std::vector<std::string>> MakeVectorFromIsogramFile(std::string IFilePath);
	std::vector<std::vector<std::string>> IsogramLists;
	std::vector<std::string> GetWordList(int);
};