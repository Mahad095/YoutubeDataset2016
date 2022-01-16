#include "Menu.h"

Menu::Menu() : analyser(videos), numBuzzWords(10)
{
    cout << "Youtube videos analysis." << '\n';
    cout << '\n';
    if (!fs::exists("Datasets"))
    {
        cout << "Cleaning, parsing and categorizing the data..." << endl;
        Chunker chunker("2016"); /*Path to the original dataset*/
    }
}
void Menu::MainLoop()
{
    while (TakeUserInput())
    {
        if (uInput == 3)
        {
            cout << "Enter required number of buzzwords: ";
            cin >> numBuzzWords;
        }
        else
        {
            if (uInput == 30)
                path = "Datasets";
            else
                path = "Datasets/" + to_string(uInput);
            cout << "Reading..." << '\n';
            for (auto& p : fs::recursive_directory_iterator(path))
                videos.push_back(Video(p.path(), int()));

            cout << "Analyzing..." << '\n';
            analyser.Analyze();
            analyser.BuzzwordAnalysis(numBuzzWords);
            videos.clear();
        }
    }
}
bool Menu::TakeUserInput()
{
    std::cout << "Enter a category number for which you would like to find Buzzwords." << '\n';
    cout << 1 << ". Film & Animation" << '\n';
    cout << 2 << ".Autos & Vehicles" << '\n';
    cout << 10 << ".Music" << '\n';
    cout << 15 << ".Pets & Animals" << '\n';
    cout << 17 << ".Sports" << '\n';
    cout << 19 << ".Travel & Events" << '\n';
    cout << 20 << ".Gaming" << '\n';
    cout << 22 << ".People & Blogs" << '\n';
    cout << 23 << ".Comedy" << '\n';
    cout << 24 << ".Entertainment" << '\n';
    cout << 25 << ".News & Politics" << '\n';
    cout << 26 << ".Howto & Style" << '\n';
    cout << 27 << ".Education" << '\n';
    cout << 28 << ".Science & Technology" << '\n';
    cout << 29 << ".Nonprofits & Activism" << '\n';
    cout << 30 << ".All categories" << '\n';
    cout << "Press 3 to Change number of buzzwords." << '\n';
    cout << "Press 0 to exit" << '\n';
    cout << '\n';
    cin >> uInput;
    if (uInput == 0) return false;
    return true;
}