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
	void Analyze();
	void BuzzwordAnalysis(int, int category);
	void ParseComments();
	void LoadStopWords();
	void FilterStopWords();
	void resetMap();

private:
	vector<Video>& _videos;
	unordered_map<string, int> _words;
	unordered_map<string, int> _stopwords;
};