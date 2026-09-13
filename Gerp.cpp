/* Gerp.cpp
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date started: July 31 2026
 * 
 * Purpose: Implementation file for Gerp.h
 * 
*/

#include "Gerp.h"
using namespace std;



/*
 * name:    constructor
 * purpose: set up Gerp class
 * input:   dir: name of directory to build index from
 *          filename: place to direct output
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
Gerp::Gerp(string dir, string filename){
    // setup
    dirName = dir;
    outFile = filename;
    continueGerp = true;
    checkFile(outFile);
    checkDir();
    init_File_vector(directory.getRoot(), "");
    setUpLineInfo();
    setUpTables();

    
    // start gameplay loop
    string command;
    do{
        cout << "Query? ";
        cin >> command;
        if(cin.fail()){
            continueGerp = false;
        }
        else{
            processCommand(command);
        }
    } while (continueGerp);
    
    cout << "Goodbye! Thank you and have a nice day.\n";
}


/*
 * name:    processCommand
 * purpose: process the command user entered and call the 
 *          appropiate function for that command
 * input:   command: the string that the user enter
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
void Gerp::processCommand(string command){
    // quit case. This command is case sensitive
    if (command == "@quit" or command == "@q"){
        continueGerp = false;
    } 
    // change output file
    else if (command == "@f"){
        cin >> outFile;
        checkFile(outFile);
    }
    // case insensitive search
    else if (command == "@i" or command == "@insensitive"){
        string searchWord;
        cin >> searchWord;
        search(searchWord, NOT_SENSITIVE);
    }
    // case sensitive search
    else{
        search(command, SENSITIVE);
    }
}


// SEARCH AND WRITE
/*
 * name:    search
 * purpose: search for a word in a file, with an option to pick
 *          case sensitivity
 * input:   curr: the current file to look for command in
 *          command: the word we want to look for
 *          isSensitive: tells gerp which table to look into
 * returns: N/A
 * effects: sends the results to outFile
 * other:   N/A
*/
void Gerp::search(string command, bool isSensitive){
    command = stripNonAlphaNum(command);
    string result;
    set<LineInfo*> lines;
    // search based on sensitivity
    if (isSensitive){
        lines = normalTable.find(command);
    } 
    else {
        string allCapCommand = makeAllCap(command);
        lines = allCapTable.find(allCapCommand);
    }
    // format output string
    for (LineInfo *info : lines){
        result = *info->filePath + ":" + to_string(info->lineNumber) + 
                    ": " + info->line + "\n";
        writeToOutFile(result);
    } 
    // if didnt find anything
    if (lines.empty() and isSensitive){
        writeToOutFile(command + " Not Found. Try with @insensitive or @i.\n");
    }
    else if (lines.empty() and not isSensitive){
        writeToOutFile(command + " Not Found.\n");
    }
}

/*
 * name:    writeToOutfile
 * purpose: write the content of the string to outFile
 * input:   content: the thing to write 
 * returns: N/A
 * effects: DOES NOT AUTOMATICALLY ADD '\n' TO CONTENT
 * other:   N/A
*/
void Gerp::writeToOutFile(string content){
    ofstream output (outFile, ios::app);
    if (not output.is_open()){
        cerr << "ERROR: CANNOT OPEN " << outFile << endl;
        exit(EXIT_FAILURE);
    }
    output << content;
    output.close();
}



// CONSTRUCTOR FUNCS

/*
 * name:    init_File_vector
 * purpose: initalizes the allFiles list, setup filepath only
 * input:   root: the current directory node
 *          parentName: the filepath the file needs to take to
 *                      get to this directory
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
void Gerp::init_File_vector(DirNode *root, string parentName){
    // clean the string up, 
    // btw, the_gerp will add a '/' to the filepath even if it already
    // ends in a '/'
    string rootName = parentName + root->getName() + "/";
    
    // set up files in this dir
    for (int i = 0; i < root->numFiles(); i++)
    {
        File curr;
        curr.filepath = rootName + root->getFile(i);
        allFiles.push_back(curr);
    }

    // init the files in the subdir of this dir
    for (int i = 0; i < root->numSubDirs(); i++)
    {
        init_File_vector(root->getSubDir(i), rootName);
    }    
}

/*
 * name:    setUpLineInfo
 * purpose: go through each file and setup its LineInfo vector
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
void Gerp::setUpLineInfo(){
    for (File &curr : allFiles){
        readLines(curr);
    }
}

/*
 * name:    readLines
 * purpose: read the contents of a file and set up LineAndInfo vector
 * input:   curr: the current file to setup
 * returns: N/A
 * effects: N/A
 * other:   curr should have its filepath initialized
*/
void Gerp::readLines(File &curr){
    // open file
    ifstream reader (curr.filepath);
    if (not reader.is_open()){
        cerr << "ERROR: CANNOT OPEN " << curr.filepath << endl;
        exit(EXIT_FAILURE);
    }

    size_t lineNum = 1; // the first line is '1'
    LineInfo buffer; 

    // read each line and store the info in curr.lines
    do{
        string line;
        getline(reader, line);
        if (line.empty()){ // ignore empty lines
            lineNum++;
            continue;
        }
        buffer.filePath = &curr.filepath;
        buffer.line = line;
        buffer.lineNumber = lineNum;
                
        // add this line to lines list
        curr.lines.push_back(buffer);
        lineNum++;
    } while (not reader.eof());
    reader.close();
}

/*
 * name:    checkdir
 * purpose: check if we can build a fstree from the given directory
 * input:   N/A
 * returns: N/A
 * effects: exits with code 1 if we can't build the tree
 * other:   N/A
*/
void Gerp::checkDir(){
    // make sure directory works
    try{
        FSTree dirTree(dirName);
        directory = dirTree;   
    }
    catch(const std::exception& e){
        cerr << "Could not build index, reason:\n";
        cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

/*
 * name:    setUpTables
 * purpose: setup allCapTable and normalTable
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
*/
void Gerp::setUpTables(){
    // repeat for every LineInfo in every file
    for (File &currFile: allFiles){
        for (LineInfo &currLineInfo : currFile.lines){
            storeTheWords(currLineInfo);
        }
    }
}

/*
 * name:    storeTheWords
 * purpose: store the words of a sentence into the Tables
 * input:   sentence: a sentence to split into words and store
 * returns: N/A
 * effects: N/A
 * other:   inspired by geek 4 geek code
*/
void Gerp::storeTheWords(LineInfo &sentence){
    size_t start = 0;
    size_t end;
    
    while ((end = sentence.line.find(' ', start)) != string::npos) {
        string_view rawWord = string_view
                              (sentence.line).substr(start, end - start);
        string_view cleanWord = stripNonAlphaNum(rawWord);
        
        if (not cleanWord.empty()) { // ignore nonempty word
            normalTable.insert(cleanWord, &sentence);    
            string capWord = makeAllCap(string(cleanWord));
            allCapTable.insert(capWord, &sentence);
        }
        start = end + 1;
    }
    // Handle the final word 
    if (start < sentence.line.length()) {
        string_view rawWord = string_view(sentence.line).substr(start);
        string_view cleanWord = stripNonAlphaNum(rawWord);

        if (not cleanWord.empty()) { // only store nonempty words
            normalTable.insert(cleanWord, &sentence);
            string capWord = makeAllCap(string(cleanWord));
            allCapTable.insert(capWord, &sentence);
        }
    }    
}

// @f function
/*
 * name:    openFile
 * purpose: create an empty file called "filename"
 * input:   filename: the name of the file
 * returns: N/A
 * effects: THIS WILL CLEAR ALL DATA IN "FILENAME" IF
 *          THAT FILE IS NOT EMPTY 
 * other:   N/A
*/
void Gerp::checkFile(string filename){
    ofstream targetFile (filename);
    if (not targetFile.is_open()){
        cerr << "ERROR: CANNOT CREATE FILE: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    targetFile.close();
}


// other funcs

/*
 * name:    makeAllCap
 * purpose: make all the chars in a string upper case
 * input:   word: a word to be converted to all upper case
 * returns: the all caps word
 * effects: N/A
 * other:   N/A
*/
string Gerp::makeAllCap(string word){
    // learend from G4G

    for (auto& x : word) {
        x = toupper(x);
    }

    return word;    
}












