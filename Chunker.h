#pragma once
#include <filesystem>
#include <fstream>
#include"Video.h"
#include <string>
#include <sys/stat.h>
namespace fs = std::filesystem;
class Chunker
{
private:
	int VideoBufferSize = 1000;
	int totalVideoCount = 0;
	int* idcount;
	int list[14];
public:
	vector<Video> videos;
	Chunker(string mainDatasetPath);
	void MakeDirectories();
	void FillDirectories();
	void DeleteDirectories();
};

