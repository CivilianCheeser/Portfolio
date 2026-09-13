/* 
 * processing.h
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date Started: Jul 26 2026
 * 
 * Purpose: a few functions that will help with processing
 * strings and traversing directories.
 */


#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include "FSTree.h"
#include "DirNode.h"
using namespace std;

string_view stripNonAlphaNum(string_view input);
string stripNonAlphaNum(string input);
void traverseDirectory(string directory);

#endif 