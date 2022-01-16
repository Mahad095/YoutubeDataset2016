#pragma once
#include<iostream>
#include"Video.h"
#include "Analyzer.h"
#include "Chunker.h"
class Menu
{
public:
    Menu();
    void MainLoop();
private:
    bool TakeUserInput();
    vector<Video> videos;
    Analyzer analyser;
    string path;
    int uInput;
    int numBuzzWords;
};

