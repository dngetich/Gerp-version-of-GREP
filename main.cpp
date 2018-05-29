/*
*David Ngetich
*April 20th, 2018
*COMP15
*gerp-phase2
* main.cpp
*  Purpose: Instantiates a gerp object and runs the main simulation.
*/

#include <iostream>
#include <string.h>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>

     
#include "Gerp.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << ">> ./the_gerp" << endl;            
        cerr << "usage: ./the_gerp directory" << endl;
        exit(EXIT_FAILURE);
    } else {
        Gerp gerp;
        gerp.query(argv[1]);
        gerp.run();

        }
        return 0;
}
