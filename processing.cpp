/* 
 * processing.cpp
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date Started: Jul 26 2026
 * 
 * Purpose: implementation file for processing.h
 */

#include "processing.h"


using namespace std;


/*
 * name:    stripNonAlphaNum (string ver)
 * purpose: remove non alphanumeric characters from the front
 *          and rear of a string
 * input:   an unprocessed string
 * returns: a string that starts and ends with alphanumeric chars
 * effects: N/A
 * other:   N/A
 */
string stripNonAlphaNum(string input){
    // non empty and front is not alphanumeric
    while (not input.empty() and not isalnum(input.front())){
        input.erase(0, 1);
    }
    // non empty and rear is not alphanumeric
    while (not input.empty() and not isalnum(input.back())){
        input.pop_back();
    }
    return input;
}

/*
 * name:    stripNonAlphaNum (stringview ver)
 * purpose: remove non alphanumeric characters from the front
 *          and rear of a stringview 
 * input:   an unprocessed stringview 
 * returns: a stringview that starts and ends with alphanumeric chars
 * effects: N/A
 * other:   N/A
 */
string_view stripNonAlphaNum(string_view input){
    // non empty and front is not alphanumeric
    while (not input.empty() and not isalnum(input.front())){
        input.remove_prefix(1);
    }
    // non empty and rear is not alphanumeric
    while (not input.empty() and not isalnum(input.back())){
        input.remove_suffix(1);
    }
    return input;
}


/*
 * name:    traverseDirectory
 * purpose: print out all files in a directory 
 *          including files in subdirectory
 * input:   file name of directory that we are searching
 * returns: N/A
 * effects: WILL CRASH IF DIRECTORY DOES NOT EXIST
 * other:   Correctly handles both dir names ending and not ending with '/'
 *          Unlike the_gerp.
 */
void traverseDirectory(string directory){  
    // clean the string up
    if ((not directory.empty()) and directory.back() != '/'){
        directory = directory + "/";
    }

    FSTree homeDir (directory);
    DirNode *root = homeDir.getRoot();

    // print current files
    for (int i = 0; i < root->numFiles(); i++)
    {
        cout << root->getName() << root->getFile(i) << endl; 
    }

    // print files in subdir -> recursive
    for (int i = 0; i < root->numSubDirs(); i++)
    {
        traverseDirectory(directory + root->getSubDir(i)->getName());
    }    
}





