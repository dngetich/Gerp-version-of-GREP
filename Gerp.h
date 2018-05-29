
/*  Gerp.h
*David Ngetich
*April 20th, 2018
*COMP15
*gerp-phase2

*  Purpose: header file for Gerp.cpp
*/

#ifndef GERP_H
#define GERP_H

#include "HashTable.h"
#include "StringProcessing.h"
#include "FSTree.h"
#include "DirNode.h"

#include <vector>
#include <set>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>


using namespace std;

class Gerp
{
 
public:
        //default constructor
        Gerp();

        //default destructor
        ~Gerp();

        //traverses and reads all files and subdirectories a directory
        void traverse_file(DirNode *node);

        //builds a hash table based on a directory
        void query(string directory);

        //menu for the gerp command
        bool check_query(string input, bool);

        //searches the hash table for a specific word
        bool search(string word, bool);

        //runs the gerp command
        void run();

        //reads a file and inserts words into the hashtable
        bool file_read(const char*);

        //Counter for the vector that holds every line from every file read
        int vec_index;

private:

        HashTable T;
};

#endif
