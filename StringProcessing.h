/*
*David Ngetich
*April 20th, 2018
*COMP15
*gerp-phase2
*  stringProcessing.h
*  Purpose: Header file for stringProcessing.h
*/

#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H

#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//removes all non-alphanumeric characters in a string
string stripnotalphanum(string);

//returns a lower case version of a string
string lowerCase(string);

//parses a line of words
set<string> split_the_line(string input);

#endif
