#include "Video.h"

using namespace std;
namespace fs = filesystem;


int main()
{
    string path = "Subset10";
    vector<Video> videos;
    videos.reserve(30);
    for (auto& p : fs::recursive_directory_iterator(path))
        videos.push_back(Video(p.path()));


    //Invalid records can be remove with this
    /*
    videos.erase(std::remove_if(
        videos.begin(), videos.end(),
        [](const Video& x) {
            return x.invalid; // put your condition here
        }), videos.end());
    */
}