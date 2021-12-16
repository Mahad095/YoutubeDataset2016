#pragma once
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

namespace filter {

    bool InvalidChar(char c);
    void StripUnicode(string& str);
    void StripNonAplhaNumericCharacters(string& s);
    void ConvertToLowerCase(string& s);
}

