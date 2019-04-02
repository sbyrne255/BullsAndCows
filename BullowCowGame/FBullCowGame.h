#pragma once
#include <String>
#include <vector>
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
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
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	FString GetWord() const;
	bool ContainsDigit(FString) const;
	bool ContainsNonASCCIChars(FString) const;
	EWordStatus CheckGuessValidity(FString) const;
	void Reset(); // TODO Make a return value based on reset
	FBullCowCount SubmitGuess(FString);
	FString MakeWord(int);
	
private:
	//See contruct for initialization.
	int32 CurrentTry;
	int32 MaxTries;
	int32 WordLength;
	FString Word;
	bool IsIsorgram(FString) const;
	bool IsAllLowerCase(FString) const;
	bool ConvertDictionaryToIsogramDictionary(FString, FString);
	std::vector<std::vector<std::string>> MakeVectorFromIsogramFile(FString IFilePath);
	std::vector<std::vector<std::string>> IsogramLists;
	std::vector<std::string> GetWordList(int);
};