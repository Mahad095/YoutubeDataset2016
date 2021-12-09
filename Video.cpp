#include "Video.h"


size_t Video::NumberOfComments()
{
    return comments.size();
}

Video::Video(fs::path p)
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
                if (!temp.empty()) /*Some cases might become empty after filtering*/
                    this->comments.push_back(temp);
            }
        }
    }
    file.close();
}

void Video::Display()
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
