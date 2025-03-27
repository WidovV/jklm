#include "database.h"
#include <sqlite3.h>
#include <stdexcept>
#include <fmt/core.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <iomanip>

#include "databasestructure.h"

/**
* Creates the database table.
* Will fail every time except first time.
* No error handling implemented nor callback
**/
static int callback(void* data, int argcount, char** argvalue, char** azColName);
sqlite3* database::db = nullptr;

void database::CreateTable()
{
	if (db == nullptr) {
		throw std::invalid_argument("Db is null!");
	}
	const char* table =
		"CREATE TABLE jklm ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"playername TEXT NOT NULL, "
		"points INTEGER, "
		"playdate DATETIME DEFAULT CURRENT_TIMESTAMP "
		");";
	sqlite3_exec(db, table, NULL, NULL, NULL);
}


void database::InsertPlayer(const char* name, int points)
{
	if (name == nullptr)
	{
		fmt::print("Name cannot be null or empty, high score will not be inserted...");
		return;
	}

	char* zErrMsg = 0;
	int result = sqlite3_exec(db, fmt::format("INSERT INTO jklm (playername, points) VALUES (\"{0}\", {1});", name, points).c_str(), NULL, NULL, &zErrMsg);
	if (result != SQLITE_OK) {
		if (zErrMsg != nullptr) {
			fmt::print(zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}
}

std::vector<databasestructure> database::GetLeaderboard()
{
	std::vector<databasestructure> records;
	char* err = 0;
	int result = sqlite3_exec(db, "SELECT * FROM jklm;", callback, &records, &err);
	if (result != SQLITE_OK) {
		if (err != nullptr) {
			fmt::print(err);
		}
	}
	return records;
}

static int callback(void* data, int argcount, char** argvalue, char** azColName)
{
	std::vector<databasestructure>* records = static_cast<std::vector<databasestructure>*>(data);
	databasestructure record;
	for (int i = 0; i < argcount; i++) {
		if (std::string(azColName[i]) == "id") {
			record.id = std::stoi(argvalue[i]);
		}
		else if (std::string(azColName[i]) == "playername") {
			record.playername = argvalue[i];
		}
		else if (std::string(azColName[i]) == "points") {
			record.points = std::stoi(argvalue[i]);
		}
		else if (std::string(azColName[i]) == "playdate") {
			record.playdate = argvalue[i];
		}
	}
	records->push_back(record);
	return 0;
}


void database::Initialize()
{
	int result = sqlite3_open("jklm.db", &db);
	if (result == SQLITE_OK) {
		CreateTable();
		return;
	}

	throw std::invalid_argument(fmt::format("An error occured while trying to open the connection: {0}", result));
}

void database::Close()
{
	if (db != nullptr) {
		sqlite3_close(db);
		db = nullptr;
	}
}