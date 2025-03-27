#include "game.h"
#include <fmt/core.h>
#include <iostream>
#include "helpers.h"
#include "Dictionary/dictionaryapi.h"
#include <chrono>
#include "Database/database.h"

int Game::Run()
{
	std::cout << "\nUsername: ";

	std::cin >> name;

	fmt::println("{} is a good name!", name);

	std::string word;
	while (true) 
	{
		system("cls");
		fmt::println("Name: {0} | Lives: {1}", name, lives);
		std::string words;
		for (char c : chars_used)
		{
			words += fmt::format("{} ", c);
		}
		fmt::println("Letters guessed: {0}\n", words);
		std::string chars = Helpers::GenerateLetters();
		fmt::println("Letters: {0}", chars);

		auto timestamp = std::chrono::steady_clock::now();
		while (true) 
		{
			fmt::print("Word: ");
			std::cin >> word;
			auto now = std::chrono::steady_clock::now();
			int timespent = std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count();
			fmt::println("Time left: {}(s)", 30 - timespent);
			if (timespent >= 30) {
				fmt::println("Duration: {}(s)", std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count());
				fmt::println("Moving on to the next word");
				lives--;
				break;
			}

			if (word.length() <= 1) {
				fmt::println("The word must be at least 1 letter...");
				continue;
			}

			if (word.find(chars) == std::string::npos)
			{
				fmt::println("The sequence of letters is not found");
				continue;
			}
			
			if (dictionaryapi::WordExists(word.c_str())) {

				AddChars(word);
				this->points++;
				break;
			}
		}

		if (lives <= 0) {
			fmt::println("Game over!");
			database::InsertPlayer(name.c_str(), points);
			return 0;
		}
	}
}

void Game::AddChars(std::string word) {
	for (char c : word) {
		if (Letters.find(c) == std::string::npos) {
			continue;
		}

		if (count(chars_used.begin(), chars_used.end(), c) > 0)
		{
			continue;
		}
		this->chars_used.push_back(c);
	}
	CheckChars();
}

void Game::CheckChars()
{
	if (chars_used.size() != 26)
	{
		return;
	}
	lives++;
	fmt::println("You have recieved an extra life bcz u used all of the letters!");
	chars_used.clear();
}