#include "helpers.h"
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
#include <fmt/core.h>

std::string Helpers::GenerateLetters()
{
    srand(time(0));

    const std::string vowels = "aeiou";
    const std::string consonants = "bcdfghjklmnpqrstvwxyz";

    char firstChar, secondChar;
    bool isFirstVowel = rand() % 2; // Randomly decide if the first character is a vowel

    if (isFirstVowel) {
        firstChar = vowels[rand() % vowels.size()];
        secondChar = consonants[rand() % consonants.size()];
    }
    else {
        firstChar = consonants[rand() % consonants.size()];
        secondChar = vowels[rand() % vowels.size()];
    }

    return fmt::format("{}{}", firstChar, secondChar);
}
