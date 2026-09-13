/* Gerp.h
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date started: Jul 31 2026
 * 
 * Purpose: 
 * Gerp is a class that search for words in the files of a directory.
 * The location of those words is printed to an user-provided file.
 * Case sensitive and insensitive search options are available.
 * User change change which file to redirect ouput.
*/

#ifndef GERP_H
#define GERP_H

#include "processing.h"
#include "Table.h"
#include "FSTree.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>


using namespace std;

class Gerp{
    public:
    Gerp(string dir, string filename);

    
    
    private:
    
    struct LineInfo{
        string line;
        string *filePath;
        int lineNumber;
    };

    struct File{
        string filepath; 
        list <LineInfo> lines;
    };

    // data containers
    list <File> allFiles;
    Table <string, LineInfo*> allCapTable;
    Table <string_view, LineInfo*> normalTable;

    // @f
    void changeOutputFile();
    // search and write
    void search(string command, bool sensitivity);
    void writeToOutFile(string content);
    
    string dirName;
    string outFile;

    const bool SENSITIVE = true;
    const bool NOT_SENSITIVE = false;
    const bool LINE_INFO_READY = true;
    const bool NOT_LINE_INFO_READY = false;
    
    
    FSTree directory;
    bool continueGerp;

    // gameplay loop
    void processCommand(string command);

    // open an empty file
    void checkFile(string filename);
    
    // constructor functions
    void checkDir();
    void init_File_vector(DirNode *root, string parentName);
    void readLines(File &currFile);
    void setUpLineInfo();
    void setUpTables();
    void storeTheWords(LineInfo &sentence);


    string makeAllCap(string word);
};

#endif
