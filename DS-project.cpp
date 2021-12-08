#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include<unordered_map>
#include<vector>
#include <sstream>
using namespace std;

namespace fs = experimental::filesystem;

class Video
{
public:
    string id;
    string title;
    int categoryId;
    vector<string> comments;
    
    static Video CreateVideo(fs::path p)
    {
        Video vid;
        fstream file(p);
        string tempStr;
        
        getline(file, tempStr);
        vid.id = tempStr.substr(tempStr.find(':') + 1);

        getline(file, tempStr);
        vid.title = tempStr.substr(tempStr.find(':') + 1);

        getline(file, tempStr);
        vid.categoryId = stoi(tempStr.substr(tempStr.find(':') + 1));
        file.close();
        return vid;
    }

    void Display()
    {
        cout << this->id << '\n';
        cout << this->title << '\n';
        cout << this->categoryId << '\n';
        cout << "\n";
    }

};

int main()
{
    string path = "Subset1";
    vector<Video> videos;
    videos.reserve(10);

    for (auto& p : fs::recursive_directory_iterator(path))
        videos.push_back(Video::CreateVideo(p.path()));


    for (Video& v : videos)
    {
        v.Display();
    }
}