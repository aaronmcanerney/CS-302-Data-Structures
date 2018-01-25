/** @file Heap.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif simple heap implementation 
@details Zero based heap built on a dynamically allocated array. 
@date 11/14/2017
**/
#include "Heap.h"


/**
*Heap     Heap constructor 
*
*@param     maxNumber   maxHeap size
*
*@pre   uninitialized array 
*
*@post  initialized array of size maxNumber
*
**/
template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::Heap(int maxNumber){
    dataItems = new T[maxNumber];
    maxSize = maxNumber;
    size = 0;
}

/**
*Heap   copy constructor
*
*@param     other   heap to copy fro   
*
*@pre    uninitialized heap
*
*@post  heap initialized as a deep copy of other
*
**/
template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::Heap(const Heap& other ){
    dataItems = new T[other.maxSize];
    size = other.size;
    maxSize = other.maxSize;
    for(int i = 0 ; i < other.size; i ++){
        dataItems[i] = other.dataItems[i];
    }
}

/**
*operator=  overloaded assignment operator   
*
*@param     other   other heap to be copied from    
*
*@pre  initialized heap
*
*@post  heap as a deep copy of other
*
**/
template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>& Heap<T, Key, Comparator>::operator= ( const Heap& other ){
    if(this == &other){
        return *this;
    }
    clear();
    dataItems = new T[other.maxSize];
    maxSize = other.maxSize;
    for(int i = 0 ; i < other.size; i ++){
        size++;
        dataItems[i] = other.dataItems[i];
    }
    return *this; 
}

/**
*~Heap  heap destructor
*
*@pre  initialized heap 
*
*@post  memory deallocated
*
**/
template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::~Heap (){
    delete [] dataItems;
}

/**
*insert     inserts a new dataItem into the heap  
*
*@param     newDataItem     item to be inserted
*
*@pre  heap of n - 1 items
*
*@post  heap of size n (heap property maintained)
*
*@throws logic error on full heap
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::insert ( const T &newDataItem ) throw ( logic_error ){
    if(!isFull()){
        size++;
        dataItems[size-1] = newDataItem;
        heapifyUp(size-1);
    }
    else{
        throw logic_error("Insert() Heap Full");
    }
}

/**
*remove     removes the highest priority item from the heap   
*
*@pre  heap of n items
*
*@post  heap of n - 1 items (heap property maintained)
*
*@throws logic error on empty heap
*
**/
template<class T, class Key, class Comparator>
T Heap<T, Key, Comparator>::remove () throw ( logic_error ){
    if(!isEmpty()){
        T temp = dataItems[0];
        size--;
        dataItems[0] = dataItems[size];
        heapifyDown(0);
        return temp;
    }
    else{
        throw logic_error("Remove() Heap Empty");
    }
}

/**
*clear      clears the contents of the heap
*
*@pre  heap of size n
*
*@post  array is deallocated and reallocated to maxSize with no data
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::clear (){
    size = 0;
    delete [] dataItems;
    dataItems = new T[maxSize];
}

/**
*isEmpty    returns true if the heap is empty 
*
*@pre   initialized heap  
*
*@post  initialized heap
*
**/
template<class T, class Key, class Comparator>
bool Heap<T, Key, Comparator>::isEmpty () const {
    return size == 0;
}

/**
*isFull     returns true if the heap is full  
*
*@pre       initialized heap
*
*@post      initialized heap
*
**/
template<class T, class Key, class Comparator>
bool Heap<T, Key, Comparator>::isFull () const{
    return size >= maxSize;
}

/** 
*showStructure  shows tree structure representation of heap
*
*@pre  initialized heap
*
*@post  initialized heap
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::showStructure () const {
    int j;   // Loop counter
    
        cout << endl;
        if ( size == 0 )
           cout << "Empty heap" << endl;
        else
        {
           cout << "size = " << size << endl;       // Output array form
           for ( j = 0 ; j < maxSize ; j++ )
               cout << j << "\t";
           cout << endl;
           for ( j = 0 ; j < size ; j++ )
               cout << dataItems[j].getPriority() << "\t";
           cout << endl << endl;
           showSubtree(0,0);                        // Output tree form
        } 
}

/**
*write levels   prints the levels of the heap to console 
*
*@pre   initialized array  
*
*@post  contents are printed to console
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::writeLevels () const{
    int bound = 1;
    for(int i = 0; i < size; i++){
        if(i < bound){
            cout << dataItems[i].getPriority() << " ";
        }
        else{
            bound = (2*bound)+1;
            cout << endl << dataItems[i].getPriority() << " ";
        }
    }
    cout << endl;
}

/**
*showSubTree    prints a subtree to console   
*
*@param     index   index in the array    
*
*@param     level   current level in heap
*
*@pre   initialized heap
*
*@post  subtree printed to console
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::showSubtree ( int index, int level ) const{
    int j;   // Loop counter
    
         if ( index < size )
         {
            showSubtree(2*index+2,level+1);        // Output right subtree
            for ( j = 0 ; j < level ; j++ )        // Tab over to level
                cout << "\t";
            cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
            if ( 2*index+2 < size )                // Output "connector"
               cout << "<";
            else if ( 2*index+1 < size )
               cout << "\\";
            cout << endl;
            showSubtree(2*index+1,level+1);        // Output left subtree
        }
}

/**
* heapifyUp     maintains the heap property after insert  
*
*@param  index  index of the current element in the heap   
*
*@pre  array containing values
*
*@post  a heap
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::heapifyUp(int index){
    while(index > 0 && comparator(dataItems[index].getPriority(), dataItems[parent(index)].getPriority())){
        int p = parent(index);
        swap(index, p);
        index = p;
    } 
}

/**
*heapifyDown 
*
*@param     index   index of current element in the heap    
*
*@pre   array containing values 
*
*@post  a heap 
*
**/
template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::heapifyDown(int index){
    int leftc = left(index);
    int rightc = right(index);
    if(inBound(leftc) && inBound(rightc)){
        if(comparator(dataItems[leftc].getPriority() , dataItems[rightc].getPriority())){
            if(comparator(dataItems[leftc].getPriority(), dataItems[index].getPriority())){
                swap(index, leftc);
                heapifyDown(leftc);
            } 
        }
        else if(comparator(dataItems[rightc].getPriority(), dataItems[index].getPriority())){
            swap(index, rightc);
            heapifyDown(rightc);
        }
    }
    if(inBound(leftc)){
        if(comparator(dataItems[leftc].getPriority() , dataItems[index].getPriority())){
            swap(index, leftc);
        } 
    }
}
