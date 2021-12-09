#include "filter.h"


bool filter::InvalidChar(char c)
{
    return !__isascii(c);
}
void filter::StripUnicode(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), InvalidChar), str.end());
}
void filter::StripNonAplhaNumericCharacters(string& s)
{
    s.erase(remove_if(s.begin(), s.end(), &ispunct), s.end());
}