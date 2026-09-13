/* 
 * try.cpp
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date Started: Jul 26 2026
 * 
 * Purpose: scratch paper for specfic debugging and trying things out
 */




#include <stdlib.h>
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include "Table.h"
using namespace std;


/*
 * name:    main
 * purpose: to run 1 specific unit test
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
 */
int main(){
 ///////////////////////////////////////////////////
    string dir = "/comp/15m1/files/proj-gerp-sample-execution";
    string test = "/comp/15m1/files/"
    "proj-gerp-sample-execution/long-query.txt";

    string myString = "./gerp " + dir + " out.me < " + test +
    " > cout.me 2> cerr.me";
    string demoString = "./the_gerp " + dir + " out.demo < " + test
    + " > cout.demo 2> cerr.demo";
    int myExit = system(myString.c_str());
    int demoExit = system(demoString.c_str());
    assert(demoExit == 0);
    assert(myExit == demoExit);
    assert(system("diff cout.me cout.demo") == 0);
    assert(system("diff cerr.me cerr.demo") == 0);
    system("sort out.me > out_sorted.me && sort out.demo > out_sorted.demo");
    assert(system("diff out_sorted.me out_sorted.demo") == 0);
}




 

      
