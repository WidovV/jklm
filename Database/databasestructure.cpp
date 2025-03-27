#include "databasestructure.h"
#include <fmt/core.h>
#include <string>

databasestructure::databasestructure() : id(0), points(0), playername(""), playdate("") {}

std::string databasestructure::toString()
{
	try
	{
		return fmt::format("[#{0}] Name: {1} | Points: {2} | Date: {3}", id, playername, points, playdate);
	}
	catch (const std::exception& e)
	{
		throw e;
	}

}
