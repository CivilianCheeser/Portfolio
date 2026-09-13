/*
 * Table.h
 * Gerp Project
 * Written by: Jerry Qiao (jqiao04)
 * Date started: Jul 28 2026
 * 
 * Purpose: Table is my version of <unordered_map>. 
 * User insert by giving the table a key and a value.
 * To search, provide a key, the table will find it and return
 * a list of values mapped by this key.
 * 
 * Does not support deleting elements
 */

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

// Table's performance tuning variables
const size_t INITIAL_TABLE_SIZE = 10;
static constexpr float MAX_LOAD_FACTOR = 0.5;
static constexpr float MIN_LOAD_FACTOR = 0.1;

template <typename KeyType, typename ValueType>
class Table {
    public:
    Table();

    size_t size() const;
    void insert(KeyType key, ValueType value);
    set<ValueType> find(const KeyType key) const;
    // does not support deleteing values
    
    private:
    struct TableEntry {
        bool      isEmpty;
        KeyType   key;
        set<ValueType> valueSet;
        // ^ should ideally be unordered set
    };


    // only counts the number of TableEntrys
    size_t numItemsInTable; 
    size_t currentTableSize;

    // contains the actual data
    vector<TableEntry> data;

    void initEmpty(vector<TableEntry> &buffer);
    void expand();
    int collisionCheck(size_t index, KeyType key) const;
    void insertAtIndex(KeyType key, ValueType val, size_t index);
};


/*
 * name:    constructor
 * purpose: set up an empty Table
 * input:   N/A
 * returns: N/A
 * effects: N/A
 * other:   N/A
 */
template <typename KeyType, typename ValueType>
Table<KeyType, ValueType>::Table(){
    // intialize variables
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    data.reserve(currentTableSize);
    initEmpty(data);
}

/*
 * name:    insert
 * purpose: insert a value into the table
 * input:   the key and the value that will be inserted
 * returns: N/A
 * effects: Calls insertAtIndex, which increments numItemInTable
 * other:   N/A
 */
template <typename KeyType, typename ValueType>
void Table<KeyType, ValueType>::insert(KeyType key, ValueType val){
    // check if need to expand
    expand();
    
    // find the right index
    hash<KeyType> hasher;
    size_t index = hasher(key) % currentTableSize;
    index = collisionCheck(index, key);

    insertAtIndex(key, val, index);
}

/*
 * name:    find
 * purpose: return the ValueType set that KEY maps to if it exists
 * input:   key: the key used to find the map
 * returns: returns the set of ValueType for that key,
 *          returns an empty set if key cannot be found
 * effects: N/A
 * other:   N/A
 */
template <typename KeyType, typename ValueType>
set<ValueType> Table<KeyType, ValueType>::find(const KeyType key) const{
    hash<KeyType> hasher;
    size_t index = hasher(key) % currentTableSize;
    
    // linear probing to find the map
    size_t attempt = 0;
    while (attempt <= currentTableSize and 
          (data[index].isEmpty or 
           data[index].key != key)){
        index = (index + 1) % currentTableSize;
        attempt++;
    }
    // if finding timed out -> return empty set
    if (attempt >= currentTableSize){
        set <ValueType> emptyList;
        return emptyList;
    }

    return data[index].valueSet;
}

/*
 * name:    size
 * purpose: returns the num of entries stored in Table
 * input:   N/A
 * returns: number of entries in Table
 * effects: N/A
 * other:   N/A
 */
template <typename KeyType, typename ValueType>
size_t Table<KeyType, ValueType>::size() const{
    return numItemsInTable;
}


// PRIVATE FUNCS

/*
 * name:    initEmpty
 * purpose: put currentTableSize amount of empty entry in a vector
 * input:   the vector to put these empty entires in
 * returns: N/A
 * effects: N/A
 * other:   I coulda wrote this func to not take a parameter. -.-
 */
template <typename KeyType, typename ValueType>
void Table<KeyType, ValueType>::initEmpty(vector<TableEntry> &buffer){
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
template <typename KeyType, typename ValueType>
void Table<KeyType, ValueType>::expand(){
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
    hash<KeyType> hasher;

    // for each elem in buffer, insert back in data
    for (size_t i = 0; i < buffer.size(); i++){
        // skip if empty
        if (buffer[i].isEmpty){
            continue;
        }
        size_t index = hasher(buffer[i].key) % currentTableSize;
        index = collisionCheck(index, buffer[i].key);
        for (ValueType val : buffer[i].valueSet){ // insert the mapped values
            insertAtIndex(buffer[i].key, val, index);
        }
    }
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
template <typename KeyType, typename ValueType>
int Table<KeyType, ValueType>::collisionCheck(size_t index, KeyType key) const{
    size_t attempt = 0;

    // loop until index does not collide
    while ((not data[index].isEmpty) and // target is not empty
    data[index].key != key and  // keys dont match 
    attempt <= currentTableSize){ // finite loop check
        // linear probing
        index = (index + 1) % currentTableSize;    
        attempt++;
    }

    // crash if collision is unavoidable
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
template <typename KeyType, typename ValueType>
void Table<KeyType, ValueType>::insertAtIndex(KeyType key, ValueType val, 
                                              size_t index){
    TableEntry &curr = data[index];
    // insert into empty slot
    if (curr.isEmpty){
        curr.isEmpty = false;
        curr.key = key;
        curr.valueSet.insert(val);
        numItemsInTable++;
    }

    // this key already exists
    else{
        // since valueSet is a set, inserting a duplicate does nothing
        // yay! less code for me to worry about!
        curr.valueSet.insert(val);
    }   
}






#endif