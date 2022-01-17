#pragma once
#include <string>

class Pair
{
public:
	std::string key;
	int value;

	Pair(std::string str, int n) : key(str), value(n) { };
};

