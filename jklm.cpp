// jklm.cpp : Defines the entry point for the application.
//

#include "jklm.h"
#include <fmt/core.h>
#include <sqlite3.h>
#include <cpr/cpr.h>
#include "game.h"
#include "Database/database.h"
#include "Database/databasestructure.h"
#include <memory>
using namespace std;

enum class StringCode {
	Start,
	Leaderboard,
	Quit,
	unknown
};

StringCode hashString(const std::string& str) {
	if (str == "s" || str == "S") return StringCode::Start;
	if (str == "l" || str == "L")  return StringCode::Leaderboard;
	if (str == "q" || str == "Q")return StringCode::Quit;
	return StringCode::unknown;
}

int main()
{
	database::Initialize();
	fmt::println("Hello and welcome to the offline version of JKLM :)");
	fmt::println("The game works in the following way: ");
	fmt::println("1. You have 'x' amount of seconds to write a word where the characters is included");
	fmt::println("2. You'll find out the rest...");
	fmt::println("\n\n");
	
	bool running = true;
	while (running) {
		std::string option;
		fmt::print("[S]tart | [L]eaderboard | [Q]uit | -> ");
		std::cin >> option;
		switch (hashString(option)) {
		case StringCode::Start:
		{
			std::unique_ptr<Game> game = std::make_unique<Game>();
			try
			{
				game->Run();
			}
			catch (const std::exception& e)
			{
				fmt::println("Error: {}", e.what());
			}
			break;
		}
		case StringCode::Leaderboard:
		{
			std::vector<databasestructure> values = database::GetLeaderboard();
			std::sort(values.begin(), values.end());
			for (databasestructure player : values)
			{
				fmt::println("{}", player.toString());
			}
			break;
		}
		case StringCode::Quit:
			running = false;
			break;
		default: 
			break;
		}
	}
	return 0;
}