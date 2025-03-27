#pragma once
#include <sqlite3.h>
#include "databasestructure.h"
#include <vector>
class database {
public:
	static void CreateTable();
	static void InsertPlayer(const char* name, int points); // &int?
	static std::vector<databasestructure> GetLeaderboard();
	// Delete ?
	// Update ?
	static void Initialize();

	static void Close();

private:
	static sqlite3* db;
};