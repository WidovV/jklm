#pragma once
#include <ctime>
#include <string>

class databasestructure {
public:
    databasestructure();
    std::string toString();
    int id;
    int points;
    std::string playername;
    std::string playdate;
    bool operator < (const databasestructure& str) const
    {
        return (points < str.points);
    }
};