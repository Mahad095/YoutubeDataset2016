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

namespace filter {

    bool InvalidChar(char c)
    {
        return !__isascii(c);
    }
    void StripUnicode(string& str)
    {
        str.erase(remove_if(str.begin(), str.end(), InvalidChar), str.end());
    }
    void StripNonAplhaNumericCharacters(string& s) 
    {
        s.erase(remove_if(s.begin(), s.end(), &ispunct), s.end());
    }
}

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
        
        getline(file, tempStr); /* Irrelevant information */
        getline(file, tempStr); /* Irrelevant information */
        getline(file, tempStr); /* Irrelevant information */


        while (getline(file, tempStr))
        {
            size_t i = tempStr.find("Comment:") + 8;
            size_t j = tempStr.find("PublishAt:");

            string temp = tempStr.substr(i, j - i);
            if (temp[temp.length() - 1] == '\t') temp.pop_back();
            filter::StripUnicode(temp);
            filter::StripNonAplhaNumericCharacters(temp);
            if(!temp.empty())
                vid.comments.push_back(temp);
        }

        file.close();
        return vid;
    }

    void Display()
    {
        cout << this->id << '\n';
        cout << this->title << '\n';
        cout << this->categoryId << '\n';
        cout << "\n";
        cout << "Comments: \n";
        for (string& x : comments)
        {
            cout << x << '\n';
        }
        cout << '\n';
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