#include "Analyzer.h"

int main()
{
    string path = "Subset100";
    vector<Video> videos;
    videos.reserve(30);
    for (auto& p : fs::recursive_directory_iterator(path))
        videos.push_back(Video(p.path()));


    Analyzer analyzer(videos);      // Load Video Data
    analyzer.Analyze();             // Parse Data
    analyzer.BuzzwordAnalysis(1000);  // Perform Analysis on Data

    //Invalid records can be remove with this
    /*
    videos.erase(std::remove_if(
        videos.begin(), videos.end(),
        [](const Video& x) {
            return x.invalid; // put your condition here
        }), videos.end());
    */
}