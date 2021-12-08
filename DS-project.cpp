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
    bool invalid; 
    size_t NumberOfComments()
    {
        return comments.size();
    }
    Video(){}
    Video(fs::path p)
    {
        cout << p << '\n';
        fstream file(p);
        string tempStr;
        this->invalid = false;
        try
        {
            getline(file, tempStr);
            this->id = tempStr.substr(tempStr.find(':') + 1);

            getline(file, tempStr);
            this->title = tempStr.substr(tempStr.find(':') + 1);

            getline(file, tempStr);
            this->categoryId = stoi(tempStr.substr(tempStr.find(':') + 1));
        }
        catch (...)
        {
            this->invalid = true;
        }
        if (!invalid)
        {
            getline(file, tempStr); /* Irrelevant information */
            getline(file, tempStr); /* Irrelevant information */
            getline(file, tempStr); /* Irrelevant information */


            while (getline(file, tempStr))
            {
                string temp;
                size_t i = tempStr.find("Comment:");
                if (i == string::npos) continue;  /*Not found*/
                i += 8; /* 8 chars for the "Comment:"*/
                size_t j = tempStr.find("PublishAt:");
                if (j == string::npos) continue; /*Not found*/
                try
                {
                    temp = tempStr.substr(i, j - i);
                }
                catch (...) { continue; }
                if (!temp.empty())
                {
                    if (temp[temp.length() - 1] == '\t') temp.pop_back();
                    filter::StripUnicode(temp);
                    filter::StripNonAplhaNumericCharacters(temp);
                    if(!temp.empty()) /*Some cases might become empty after filtering*/
                        this->comments.push_back(temp);
                }
            }
        }
        file.close();
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
    string path = "2016";
    vector<Video> videos;
    videos.reserve(30);

    for (auto& p : fs::recursive_directory_iterator(path))
        videos.push_back(Video(p.path()));


    cout << "The number of videos before removing: "<< videos.size() << '\n';
    videos.erase(std::remove_if(
        videos.begin(), videos.end(),
        [](const Video& x) {
            return x.invalid; // put your condition here
        }), videos.end());
    cout << "The number of videos after removing: " << videos.size() << '\n';

    ofstream write("DataSetFull.txt");



    for (Video& v : videos)
    {
        write << v.id << '\n';
        write << v.title << '\n';
        write << v.categoryId << '\n';
        for (auto& s : v.comments)
        {
            write << s << '\n';
        }
        write << '\n';
    }
    write.close();
}
