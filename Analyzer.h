#pragma once
#include "Video.h"
#include "Pair.h"
#include <sstream>
#include <iterator>
#include <queue>

class Analyzer
{
public:
	Analyzer(vector<Video>& videos);
	void Buzzwords_Comments(int);
	void Buzzwords_Titles(int);

private:
	vector<Video> _videos;
};

