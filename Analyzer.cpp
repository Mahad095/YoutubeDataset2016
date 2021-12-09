#include "Analyzer.h"

template <typename T>
void split(const std::string& s, char delim, T result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}


struct Compare {
	bool operator()(Pair* p1, Pair* p2) {
		return (p1->value < p2->value);
	}
};

Analyzer::Analyzer(vector<Video>& videos) : _videos(videos){

}

void Analyzer::Buzzwords_Comments(int num) {
	unordered_map<string, int> wordCount;
	std::priority_queue<Pair*, vector<Pair*>, Compare> topWords;

	for (int i = 0; i < _videos.size(); i++) {
		for (int j = 0; j < _videos[i].NumberOfComments(); j++) {
			vector<string> words = split(_videos[i].comments[j], ' ');	
			for (int k = 0; k < words.size(); k++) {
				++wordCount[words[k]];
			}
		}
	}

	unordered_map<string, int>::iterator p;
	for (p = wordCount.begin(); p != wordCount.end(); p++) {
		topWords.push(new Pair(p->first, p->second));
	}

	int limit = 0;
	/*
	unordered_map<string, int>::iterator p;
	for (p = wordCount.begin(); p != wordCount.end() && limit < num; p++, limit++) {
		cout << p->first << ": " << p->second << endl;
	}*/


	for (int i = 0; i < topWords.size() && limit < num; limit++, i++) {
		cout << topWords.top()->key << " : " << topWords.top()->value << "\n";
		topWords.pop();
	}

	cout << "\n\n";
}

void Analyzer::Buzzwords_Titles(int num) {

}

