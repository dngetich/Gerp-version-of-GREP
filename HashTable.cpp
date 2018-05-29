/*
*David Ngetich
*April 20th, 2018
*COMP15
*gerp-phase2
*HashTable.cpp
* Purpose:contains the implementation of the HashTable with the
*  insert, search, expand, and the print functions for the hashtable.
*/
#include <iostream>
#include "HashTable.h"
#include "StringProcessing.h"

using namespace std;


//default constructor for HashTable
HashTable::HashTable()
{
    current_table_size = INITIAL_TABLE_SIZE;

    num_files  = 0;

    table = new FileNode *[current_table_size];

    for (int i = 0; i < current_table_size; i++) {
        table[i] = NULL;
    }
}

//Destructor
HashTable::~HashTable() {
    deleteTable();
}


//function: hashIndex()
// Arguments: string
// Return: size_t
//Purpose: hashes a value into the hash table and returns its
// corresponding index.
size_t HashTable::hash_index(string value)
{
    return hash<string>{}(value) % current_table_size;
}


//Function: insert(string, int, string, int)
// Arguments: string, int, string, int
// Return: Nothing
//Purpose: inserts a new file node into the hash table based on chaining
// method
void HashTable::insert(string value, int file_index, 
    string file_location, int vec_line_index)
{
    expand();
    size_t index = hash_index(lowerCase(value));

    FileNode * new_node = new FileNode();
    new_node->value = value;
    new_node->file_index = file_index;
    new_node->file_location = file_location;
    new_node->vec_line_index = vec_line_index;
    new_node->next = NULL;

    if (table[index] == NULL) {
        table[index] = new_node;
    } else {
        FileNode * temp_node = table[index];
        table[index] = new_node;
        new_node->next = temp_node;
    }
    num_files++;
}


//Function: print_file_node(FileNode *)
// Arguments: FileNode *
// Return: Nothing
// Purpose: prints an individual FileNode
void HashTable::print_file_node(FileNode *p, ostream &out)
{
    out << "value:  {" << p->value << " " << p->file_index
    << ":" << p->file_location << "}" ;
}


// FUnction:print()
// Arguments: Nothing
// Return: Nothing
// Purpose: prints the HashTable
void HashTable::print(ostream &out)
{
    for (int i = 0; i < current_table_size; ++i) {
        FileNode *curr = table[i];
        out << i << ":  [ ";
        while (curr != NULL) {
            print_file_node(curr, out);
            curr = curr->next;
            if (curr != NULL)
                out << ", ";
            }
            out << "]" << endl;
        }
    out << endl;
}


//Function: expand()
//Arguments: Nothing
//Return: Nothing
//Purpose: expands the current hash table if the load factor reaches a
// limit
void HashTable::expand()
{
	double loadFact = double (num_files) / double(current_table_size);

	if (loadFact > 0.70) {
		int tempnum = num_files;
		FileNode * temp_ray = new FileNode[tempnum];

		int tempIterator = 0;
        for (int i = 0; i < current_table_size; i++)
            {
            FileNode * temp = table[i];
            while (table[i] != NULL)
            {
            temp_ray[tempIterator].value = table[i]->value;
            temp_ray[tempIterator].file_index = table[i]->file_index;
            temp_ray[tempIterator].file_location = table[i]->file_location;
            temp_ray[tempIterator].vec_line_index = table[i]->vec_line_index;

            temp = temp->next;
            delete table[i];
            table[i] = temp;
            tempIterator++;
            }
            }

    int capacityBig = (current_table_size + 1) * 2;

    FileNode ** tableBig = new FileNode *[capacityBig];

    for(int i = 0; i < capacityBig; i++) {
        tableBig[i] = NULL;
        }
        deleteTable();
        table = tableBig;
        current_table_size = capacityBig;

    for (int i = 0; i < tempnum; i++) {
        insert(temp_ray[i].value,
        temp_ray[i].file_index,
        temp_ray[i].file_location,
        temp_ray[i].vec_line_index);
        }
        delete [] temp_ray;
                }
}


// dFunction: deleteTable()
// Return: Nothing
// Arguments: Nothin
// Purpose: deletes the entire table
void HashTable::deleteTable()
{
    for (int i = 0; i < current_table_size; i++) {
        if (table[i] != NULL) {
            FileNode *curr = table[i];
            FileNode * next = curr->next;

            while (curr != NULL) {
                delete curr;
                curr = next;
                if(next != NULL)
                next = next->next;
                }
            }
        }
    num_files = 0;
    current_table_size = 0;
    delete [] table;
}

//Function: remove_dup(vector <FileNode *> &v)
// Arguments: vector <FileNode *> &v
// Return: Nothin
// Purpose: removes duplicates in a vector - based on same value and on
// the same line
void HashTable::remove_dup(vector <FileNode *> &v)
{
    for(size_t i = 0; i < v.size(); i++) {
        for(size_t j = 0 ; j < v.size(); j++) {
            if (i != j) {
                if (lowerCase(v[i]->value) == lowerCase(v[j]->value)
                 && v[i]->file_index == v[j]->file_index) 
                {
                    v.erase(v.begin() + j);
                }
            }
        }
    }
}


// search(string query, bool insensitive)
// Arguments: string, bool
// Return: Nothing
//Purpose: searches the hash table for a query i.e insensitive or case
//sensitive mode
bool HashTable::search(string query, bool insensitive)
{
    size_t index = hash_index(lowerCase(query));
    FileNode *temp = table[index];
    bool flag = false;
    if (insensitive) {
        vector<FileNode*> repeats;
        while (temp != NULL)
        {
            repeats.push_back(temp);
            temp = temp->next;
        }
        remove_dup(repeats);
       for (size_t i = 0; i < repeats.size(); i++) {

        if(lowerCase(repeats[i]->value) == lowerCase(query)) {
            cout << repeats[i]->file_location << ":" 
            << repeats[i]->file_index << ": " 
            << vec_line[repeats[i]->vec_line_index] << endl;
            flag = true;
            }
        }

        } else {

        while (temp != NULL) {
            if (temp->value == query) {
                cout << temp->file_location << ":" <<
                temp->file_index << ": " <<
                vec_line[temp->vec_line_index] << endl;
                flag = true;
                }
                temp = temp->next;
            }
        }
        return flag;
}


//Function: addToVector(string line)
// Arguments: string line
// Return: Nothing
// Purpose: adds a line to the line vector from the file
void HashTable::add_to_vector(string line)
{
        vec_line.push_back(line);
}














