/*
*David Ngetich
*COMP15
*gerp-phase2
*stringProcessing.cpp
*  Purpose: Contains various string manipulation functions
*/

#include <iostream>
#include "StringProcessing.h"

using namespace std;


// function: stripnotalphanum()
// Arguments: string
// Return: string
// Purpose: strips trailing and leading non-alphanumeric characters
string stripnotalphanum(string word)
{
        string strip;
        int length = word.length();
        int first, last = 0;
        for(int i = 0; i < length; i ++) {
                if(isalnum(word[i])) {
                        first = i;
                        break;
                }
        }
        for(int i = length - 1; i >= 0 ; i--) {
                if(isalnum(word[i])) {
                        last = i;
                        break;
                }
        }
        int subLength = last - first + 1;
        return word.substr(first, subLength);
}


// Function: lowerCase(string)
// Arguments: string
// Return: string
// Purpose: converts string to lower case
string lowerCase(string word)
{
        for (size_t i = 0; i < word.length(); i++) {
                word[i] = tolower(word[i]);
        }
        return word;
}


// Function: split_the_line(string)
// Arguments: string
// Return: set<string>
// Purpose: traverses a line of words and inserts them into a set
set<string> split_the_line(string input)
{
        istringstream iss(input);
        vector<string> words{istream_iterator<string>{iss},
        istream_iterator<string>{}};
        for (size_t i = 0; i < words.size(); i++) {
                words[i] = stripnotalphanum(words[i]);
        }
        set<string> strippedwords(words.begin(), words.end());
        return strippedwords;
}
