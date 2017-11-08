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

/**
*~Destructor   hashtable destructor
*
*@pre   hahsmap of size n
*
*@post  all memory appropriately deallocated
*
**/
template<class T, class Key>
HashTable<T, Key>::~HashTable(){
    clear();
}


/**
*insert    Insert function
*
*@param     newDataItem     data item to be inserted into the hashmap
*
*@pre  hashmap of size n - 1
*
*@post  hashmap with a new data item placed inside
*
**/
template<class T, class Key>
void HashTable<T, Key>::insert(const T& newDataItem){
    dataTable[newDataItem.hash(newDataItem.getKey()) % tableSize].insert(newDataItem);
}


/**
*remove     removes the indicated data item from the 
*
*@param     deleteKey   key to be deleted from the hash table
*
*@pre  hash table with n items
*
*@post  if the item was found, a hash map with n - 1 items
*
**/
template<class T, class Key>
bool HashTable<T, Key>::remove(const Key& deleteKey){
    T temp;
    return dataTable[temp.hash(deleteKey) % tableSize].remove(deleteKey);
}


/**
*Retrieve   Retrieve method for the hashtable 
*
*@param     searchKey   key to be hashed and found in the hashtable
*
*@param     returnItem  item to hold data in if found
*
*@pre   hashtable of size n and an empty data item
*
*@post  a data item with the value indicated by the key
*
**/
template<class T, class Key>
bool HashTable<T, Key>::retrieve(const Key& searchKey, T& returnItem) const{
   T temp; 
   return dataTable[temp.hash(searchKey) % tableSize].retrieve(searchKey, returnItem); 
}


/**
*clear      deallocates the memory in use by the hashtable 
*
*@pre   initialized hashtable
*
*@post  hashtable with all memory deallocated
*
**/
template<class T, class Key>
void HashTable<T, Key>::clear(){
   delete [] dataTable; 
}

/**
*isEmpty    deteremines whether the table is empty
*
*@pre   hash table
*
*@post  returns true if hashtable is empty
*
**/
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


/**
*showStructure    shows the contents of the hashtable
*
*@pre   hashtable containing binary search trees
*
*@post  contents of each  binary search tree printed to console
*
**/
template<class T, class Key>
void HashTable<T, Key>::showStructure() const{
    for (int i = 0; i < tableSize; ++i) {
        cout << i << ": ";
        dataTable[i].writeKeys();
    }
}


/**
*standarDeviation    determines the standard deviations of keys in the table
*
*@pre   hashmap with keys and values 
*
*@post standard deviation of the keys distribution
*
**/
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
