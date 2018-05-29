/*
*David Ngetich
*gerp-phase2
*COMP15
* Gerp.cpp
* Purpose: 
*  Traversesthrough all the files and subdirectories to create a fStree.
*  It then inserts the word from the tree into a HashTable and lets the
*  user to query the words.
*/

#include <iostream>
#include "Gerp.h"

using namespace std;


Gerp::Gerp()
{
    vec_index = 0;
}

Gerp::~Gerp()
{

}


// Function: file_read()
// Arguments: char 
// Return: bool
// Does: reads in the contents of a text file inserting each
// word in the file into the hash table
bool Gerp::file_read(const char* file_name)
{
    ifstream infile;
    infile.open(file_name);

    if (!infile.is_open()) {
        cerr << "Could not build index, exiting." << file_name << endl;
        return false;
    };
	string line;
    int file_index = 1;
    while (getline(infile, line)) 
    {
	    set<string> words = split_the_line(line);

        for (set<string>::const_iterator i = words.begin(); i !=
        words.end(); i++) 
        {
            T.insert(*i, file_index, file_name, vec_index);
        }
        T.add_to_vector(line);
        vec_index++;
        file_index++;
    }
    infile.close();
    return true;
}


//Function: checkquery(string, bool)
// Arguments: string, bool
// Return: bool
// Purpose: checks the query for the gerp command, 
// It has 3 options: quit, insensitive query or regular query
bool Gerp::check_query(string input, bool insensitive)
{

	if (input == "@q" || input == "@quit") {
        cout << "\nGoodbye! Thank you and have a nice day." << endl;
        return false;
        } else if (insensitive) {
            string strip = stripnotalphanum(input);
            if (!search(strip, true)) 
            {
                cout << strip << " Not Found." << endl;
            }
        } else {
            string strip = stripnotalphanum(input);
            if (!search(strip, false)) 
            {
                cout << " query not found" << endl;
            }
        }
    cout << "Query? ";
    return true;
}


// Function: search(string, bool)
// Arguments: string, bool
// Return: bool
// Purpose: searches the hash table for a word - either insensitive or case
// sensitive mode
bool Gerp::search(string word, bool insensitive)
{
    if (T.search(word, insensitive)) 
    {
        return true;
    }
    return false;
}


// Function:run()
// Arguments: none
// Return: none
// Purpose: runs the gerp command - accepts user input for querying words
// in the hash table
void Gerp::run()
{
    cout << "Query? ";
    string input;
    while (cin >> input) {
        if (input == "@i" || input == "@insensitive") {
            cin >> input;
            if (!check_query(input, true)) 
                break;
        } else {

            if (!check_query(input, false)) 
                break;
            }

        }
        if (cin.eof()) {
            cout << "\nGoodbye! Thank you and have a nice day." << endl;
        }
}

//Function: query(string)
// Arguments: string
// Return: None
// Purpose: builds a FSTree based on the directory
void Gerp::query(string directory)
{
        FSTree tree_directory(directory);
        DirNode *root = tree_directory.get_root();
        traverse_file(root);
        
}

//Function: traverse_file(DirNode)
// Arguments: DirNode 
// Return: None
// Purpose: traverses through files and the subdirectories in a directory
void Gerp::traverse_file(DirNode *node)
{
    if (node->is_empty()) 
    {
    return;
    }

    if (node->num_files() != 0) 
    {
        for (int i = 0; i < node->num_files(); i++) 
        {
            string full_name = node->get_name() + "/" +
            node->get_file(i);
            file_read(full_name.c_str());
        }
    }
    if (node->has_subdir()) 
    {
        for (int i = 0; i < node->num_subdirs(); i++) 
        {
            DirNode *sub_dir = node->get_subdir(i);
            string full_name = sub_dir->get_parent()->get_name() + "/"
            + sub_dir->get_name();
            sub_dir->set_name(full_name);
            traverse_file(sub_dir);
        }
    }
}
