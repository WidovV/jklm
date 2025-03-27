#pragma once
#include <vector>
#include <string>
class Game {
public:
	int Run();
	std::string Letters = "abcdefghijklmnopqrstuvwxyz";
private:
	int lives = 3;
	std::vector<char> chars_used;
	std::string name;
	void AddChars(std::string word);
	void CheckChars();
	int points = 0;
};