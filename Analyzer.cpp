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

Analyzer::Analyzer(vector<Video>& videos) : _videos(videos) { }

void Analyzer::Analyze() {
	ParseComments();    // Process Cleaned Comment Data into individual words
	LoadStopWords();    // Load StopWords (words not classified as keywords)
	FilterStopWords();  // Remove StopWords from Word Data

	// Note: Title data currently not included
}

void Analyzer::LoadStopWords() {
	fstream file("stopwords.txt");
	string word;

	while (getline(file, word)) {
		_stopwords[word];
	}
	file.close();
}

void Analyzer::FilterStopWords() {
	unordered_map<string, int>::iterator p;
	unordered_map<string, int>::iterator it;

	for (p = _stopwords.begin(); p != _stopwords.end(); p++) {
		if (_words.find(p->first) != _words.end()) {
			//cout << "Removing Stopword: " << p->first << endl;
			it = _words.find(p->first);
			_words.erase(it);
			p->second++;
		}
	}
}

void Analyzer::ParseComments() {
	for (int i = 0; i < _videos.size(); i++) {
		for (int j = 0; j < _videos[i].NumberOfComments(); j++) {
			vector<string> words = split(_videos[i].comments[j], ' ');
			for (int k = 0; k < words.size(); k++) {
				++_words[words[k]];
			}
		}
	}
}

void Analyzer::BuzzwordAnalysis(int num) {
	std::priority_queue<Pair*, vector<Pair*>, Compare> topWords;

	unordered_map<string, int>::iterator p;
	for (p = _words.begin(); p != _words.end(); p++) {
		topWords.push(new Pair(p->first, p->second));
	}

	for (int i = 0, limit = 0; i < topWords.size() && limit < num; limit++, i++) {
		cout << topWords.top()->key << " : " << topWords.top()->value << "\n";
		topWords.pop();
	}
	cout << "\n\n";
}

