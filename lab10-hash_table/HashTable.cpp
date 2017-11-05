/** @file HashTable.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif simple hash table implementation 
@details Implemetns a hash table with chaining.
Uses Binary Search Tree as "chain" 
@date 11/01/2017
**/


#include "HashTable.h"
#include<math.h>

/**
*HashTable     HashTable constructor 
*
*@param     initTableSize   initial size for the table
*
*@pre   uninitialized array of binary search trees 
*
*@post  array of binary search trees initialized
*
**/
template<class T, class Key>
HashTable<T, Key>::HashTable(int initTableSize){
    tableSize = initTableSize;
    dataTable = new BSTree<T,Key>[tableSize];
}

/**
*copyTable   function to copy the values from one hash table to another 
*
*@param     source  table to be copied from
*
*@pre   hash map with data or empty hash map 
*
*@post  dataTable contains an exact copy of the param source
*
**/
template<class T, class Key>
void HashTable<T, Key>::copyTable(const HashTable& source){
    tableSize = source.tableSize;
    dataTable = new BSTree<T, Key>[tableSize]; 
    for(int i = 0; i < tableSize; i++){
         dataTable[i] = source[i];
    } 
}


/**
*HashTable    HashTable copy constructor 
*
*@param     ohter   hash table to be copied from
*
*@pre  uninitalized hash map
*
*@post  hashap copied from other
*
**/
template<class T, class Key>
HashTable<T, Key>::HashTable(const HashTable<T, Key>& other){
    copyTable(other);
}

/**
*operator=     Overloaded assignment operator 
*
*@param     initTableSize   initial size for the table
*
*@pre   uninitialized array of binary search trees 
*
*@post  array of binary search trees initialized
*
**/
template<class T, class Key>
HashTable<T, Key>& HashTable<T, Key>::operator=(const HashTable<T, Key>& other){
    if(this == &other){
        return *this;
    }
    clear(); 
    copyTable(other);
    return *this;
}

template<class T, class Key>
HashTable<T, Key>::~HashTable(){
    clear();
}

template<class T, class Key>
void HashTable<T, Key>::insert(const T& newDataItem){
    dataTable[newDataItem.hash(newDataItem.getKey()) % tableSize].insert(newDataItem);
}

template<class T, class Key>
bool HashTable<T, Key>::remove(const Key& deleteKey){
    T temp;
    return dataTable[temp.hash(deleteKey) % tableSize].remove(deleteKey);
}

template<class T, class Key>
bool HashTable<T, Key>::retrieve(const Key& searchKey, T& returnItem) const{
   T temp; 
   return dataTable[temp.hash(searchKey) % tableSize].retrieve(searchKey, returnItem); 
}

template<class T, class Key>
void HashTable<T, Key>::clear(){
   delete [] dataTable; 
}

template<class T, class Key>
bool HashTable<T, Key>::isEmpty() const{
    if(tableSize == 0){
        return true;
    }
    for(int i = 0; i < tableSize; i++){
        if(!dataTable[i].isEmpty()){
            return false;
        }
    }
    return true;
}

template<class T, class Key>
void HashTable<T, Key>::showStructure() const{
    for (int i = 0; i < tableSize; ++i) {
        cout << i << ": ";
        dataTable[i].writeKeys();
    }
}

template<class T, class Key>
double HashTable<T, Key>::standardDeviation() const{
    double  mean = 0;
    double sum = 0;
    for(int i = 0; i < tableSize; i++){
        mean += dataTable[i].getCount();
    }
    mean /= tableSize;
    for(int i = 0; i < tableSize; i++){
        sum += pow((dataTable[i].getCount() - mean), 2.0); 
    }
    return sqrt(sum / (tableSize - 1)); 
}
