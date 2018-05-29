/*
*David Ngetich
*April 20th, 2018
*COMP15
*gerp-phase2
* HashTable.h
* Purpose: header file for HashTable.cpp
*/


#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <functional>
#include "StringProcessing.h"

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

using namespace std;


class HashTable
{

public:
        //default constructor
        HashTable();

        //default destructor
        ~HashTable();

        //inserts a file node into a hash table through chaining method
        void insert(string value, int, string, int);

        //searches the hash table for a specific query
        bool search(string query, bool);

        //adds a string to the line vector
        void add_to_vector(string line);

        //prints the entire hash table
        void print(ostream &out);




private:

        //file node struct
        //contains the keys - word, file_location, file number that the word
        //occured on, line vector index that the word occured in, pointer to 
        // the next node by chaining method
        struct FileNode {
                string value;
                string file_location;
                int vec_line_index;
                int file_index;
                FileNode *next;
        };

        //removes duplicates in the vector
        void remove_dup(vector <FileNode *> &);

        //line vector containing every line iteraterated while
        //file read
        vector<string> vec_line;

        //hash table
        FileNode ** table;

        //number of items in the table
        int num_files;

        //current table size
        int current_table_size;

	//initial table size
        static const int INITIAL_TABLE_SIZE = 100;  

        //hash index
        size_t hash_index(string key);

        //file node print
        void print_file_node(FileNode *p, ostream &);

        //expands hash table
        void expand();

        //deletes entire table
        void deleteTable();

};
#endif