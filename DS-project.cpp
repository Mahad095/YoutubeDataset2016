#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include<unordered_map>
#include<vector>

using namespace std;

namespace fs = experimental::filesystem;

class Video
{
public:
    string id;
    string title;
    int categoryId;
    vector<string> comments;
    
    static Video&& CreateVideo(fs::path& p)
    {
        Video vid;
        fstream obj(p);
    }
};

int main()
{
    string path = "2016";
    vector<Video> videos(200000);

    for (auto& p : fs::recursive_directory_iterator(path))
        cout << p.path() << endl;


}