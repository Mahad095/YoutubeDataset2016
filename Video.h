#pragma once
#include "filter.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include<unordered_map>
#include<vector>
#include <sstream>

using namespace std;
namespace fs = filesystem;

class Video
{
public:
    string id;
    string title;
    int categoryId;
    vector<string> comments;
    bool invalid;

    size_t NumberOfComments();
    Video() {};
    Video(fs::path p);
    Video(fs::path p, int);
    void Display();
};