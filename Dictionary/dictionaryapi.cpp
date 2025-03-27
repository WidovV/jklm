#include "dictionaryapi.h"
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>
#include <iostream>
using json = nlohmann::json;

bool dictionaryapi::WordExists(const char* word)
{
	if (word == nullptr || strlen(word) <= 1)
	{
		return false;
	}
	
	std::string url = fmt::format("{0}{1}", baseUrl, word);
	cpr::Response resp = cpr::Get(cpr::Url{ url });

	return resp.status_code == 200 && resp.text.find("No Definitions Found") == std::string::npos;

}