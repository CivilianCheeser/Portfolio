/*
 * TableSet.h
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date started: Jul 28 2026
 * 
 * This file will borrow elements from the classes found in the
 * hash table lab.
 * 
 * Purpose: Table is a data container designed for Table.h 
 * User can insert elements. The elements stored is unique
 * User can ask for find elements at a certain index
 * It is an unorderset copycat
 * 
 */

#ifndef TABLE_SET_H
#define TABLE_SET_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;


using ValueType = size_t;

class TableSet {
    public:
    TableSet();

    size_t size() const;
    void insert(ValueType value);
    ValueType at(size_t index) const;

    // does not support deleteing values


    private:
    struct TableEntry {
        bool      isEmpty;
        ValueType value;
    };

    // change the balance of space vs time using these two vars
    // initial table size should be bigger than 3 (passes my testing)
    const size_t INITIAL_TABLE_SIZE = 5;
    static constexpr float MAX_LOAD_FACTOR = 0.5;
    static constexpr float MIN_LOAD_FACTOR = 0.1;

    // only counts the number of TableEntry
    size_t numItemsInTable; 
    size_t currentTableSize;

    // contains the actual data
    vector<TableEntry> data;
    list <ValueType> accessList;

    list<ValueType> get() const;
    void initEmpty(vector<TableEntry> &buffer);
    void expand();
    int collisionCheck(size_t index, ValueType key) const;
    void insertAtIndex(ValueType val, size_t index);
    bool hasDuplicate(ValueType val);
};


/*
 * name:    constructor
 * purpose: set up an empty Table
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
 */
TableSet::TableSet(){
    // intialize variables
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    data.reserve(currentTableSize);
    initEmpty(data);
}

/*
 * name:    insert
 * purpose: insert a value into the table
 * input:   the value that will be inserted
 * returns: N/A
 * effects: Calls insertAtIndex, which increments numItemInTable
 * other:   N/A
 */
void TableSet::insert(ValueType val){
    if(hasDuplicate(val)){
        return;
    }

    // check if need to expand
    expand();
    
    // find
    hash<ValueType> hasher;
    size_t index = hasher(val) % currentTableSize;

    index = collisionCheck(index, val);
    insertAtIndex(val, index);
    accessList.push_back(val);
    size(); // assert insertion done right
}

/*
 * name:    get
 * purpose: get all elems in this TableSet
 * input:   N/A
 * returns: return accessList
 * effects: N/A
 * other:   N/A
*/
list<ValueType> TableSet::get()const{
    return accessList;
}


/*
 * name:    size
 * purpose: returns the num of entries stored in Table
 * input:   N/A
 * returns: number of entries in Table
 * effects: N/A
 * other:   N/A
 */
size_t TableSet::size() const{
    if (accessList.size() != numItemsInTable){
        cerr << "ERROR: SIZE INVARIANT VIOLATED\n";
    }
    return numItemsInTable;
}


// // PRIVATE FUNCS


/*
 * name:    hasDuplicates
 * purpose: return true if val already exists in the data
 * input:   val: the value to see if we already have a copy of
 * returns: retrns if val has a duplicate in data
 * effects: N/A
 * other:   N/A
*/
bool TableSet::hasDuplicate(ValueType val){
    hash<ValueType> hasher;
    size_t index = hasher(val) % currentTableSize;

    if (data[index].isEmpty){
        return false;
    }
    if (data[index].value == val){
        return true;
    }

    size_t attempt = 0;
    while (attempt <= currentTableSize){
        index = (index + 1) % currentTableSize;
        attempt++;

        if (data[index].isEmpty){
            return false;
        }
        if (data[index].value == val){
            return true;
        }
    }
    return false;
}

/*
 * name:    initEmpty
 * purpose: set all is empty 
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
 */
void TableSet::initEmpty(vector<TableEntry> &buffer){
    TableEntry emptyEntry;
    emptyEntry.isEmpty = true;
    for (size_t i = 0; i < currentTableSize; i++){    
        buffer.push_back(emptyEntry);
    }   
}

/*
 * name:    expand
 * purpose: expand the list so that the load factor is set to
 *          the miminum acceptable load factor
 * input:   N/A
 * returns: N/A
 * effects: Changes currentTableSize
 * other:   SHOULD NOT CHANGE numItemsInTable
 */
void TableSet::expand(){
    // check if need to expand
    float currLoadFactor =  (numItemsInTable + 1.0) / currentTableSize;
    if (currLoadFactor < MAX_LOAD_FACTOR){
        return;
    }

    // set aside current data
    vector<TableEntry> buffer = data;
    // adjust data to be bigger
    currentTableSize = numItemsInTable / MIN_LOAD_FACTOR;
    data.clear();
    data.reserve(currentTableSize);
    numItemsInTable = 0; // cuz the insert func will increment this
    initEmpty(data);
    hash<ValueType> hasher;

    // for each elem in buffer, insert back in data
    for (size_t i = 0; i < buffer.size(); i++){
        // skip if empty
        if (buffer[i].isEmpty){
            continue;
        }
        size_t index = hasher(buffer[i].value) % currentTableSize;
        index = collisionCheck(index, buffer[i].value);

        insertAtIndex(buffer[i].value, index);
    }
    size(); // assert expansion done right
}

/*
 * name:    collisionCheck
 * purpose: ensures that inserting KEY at INDEX will not cause collisions
 * input:   index: the index that we want to insert KEY at
 *          key: the KEY we want to check to avoid collision
 * returns: an index that is guaranteed to not collide
 * effects: N/A
 * other:   USES LINEAR PROBING, BE CONSISTENT!
 */
int TableSet::collisionCheck(size_t index, ValueType val) const{
    size_t attempt = 0;
    while ((not data[index].isEmpty) and // target is not empty
    data[index].value != val and  // vals dont match
    attempt <= currentTableSize){ // finite loop check
        // linear probing
        index = (index + 1) % currentTableSize;    
        attempt++;
    }
    if (attempt >= currentTableSize){
        cerr << "ERROR: COLLISON UNAVOIDABLE\n";
        exit(EXIT_FAILURE);
    }

    return index;
}

/*
 * name:    insertAtIndex 
 * purpose: Insert a key and a value at index'th position
 *          in the data vector.
 * input:   key: the key to be inserted
 *          line: an int to be inserted into lineNums data container
 *          index: the index to insert at
 * returns: N/A
 * effects: If inserted on empty index, the index is no longer empty
 * other:   THIS FUCTION ADJUSTS numItemsIntable
 *          Assumes index is valid and does not have collision
 */
void TableSet::insertAtIndex(ValueType val, size_t index){
    TableEntry &curr = data[index];
    // insert into empty slot
    if (curr.isEmpty){
        curr.isEmpty = false;
        curr.value = val;
        numItemsInTable++;
    }
    
    else{
        cerr << "ERROR: INVARIANT VIOLATED.\n"
             << "There is either a duplicate or a collision\n";
        exit(EXIT_FAILURE);
    }   
}






#endif