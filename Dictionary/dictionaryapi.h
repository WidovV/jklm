#pragma once
#include <fmt/core.h>
class dictionaryapi {
public:
	static bool WordExists(const char* word);

private:
	static constexpr const char* baseUrl = "https://api.dictionaryapi.dev/api/v2/entries/en/";
};