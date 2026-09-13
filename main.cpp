/* main.cpp
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date started: Jul 31 2026
 * 
 * Purpose: Driver file for Gerp. 
 * Ensures usage command is correct.
 * 
 * gerp is a program that search for words in the files of a directory.
 * The location of those words is printed to an user-provided file.
 * Case sensitive and insensitive search options are available.
 * User change change which file to redirect ouput.
*/

#include "Gerp.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

/*
 * name:    main
 * purpose: check argc and call Gerp
 * input:   argc: the number of commands the user gave
 *          argv: the content of those commands
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
int main (int argc, char *argv[]){
    // check usage
    if (argc != 3){
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }

    // start gerp
    Gerp wordSearcher(argv[1], argv[2]);
}