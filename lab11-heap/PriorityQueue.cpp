/** @file PriorityQueue.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif simple Priority queue implementation 
@details Priority queue that inherits from a heap
@date 11/14/2017
**/

#include "PriorityQueue.h"

/**
*PriorityQueue   Priority Queue constructor
*
*@param     maxNumber   maxPriority size
*
*@pre   uninitialized array 
*
*@post  initialized array of size maxNumber
*
**/
template < typename DataType, typename KeyType, typename Comparator >
PriorityQueue<DataType,KeyType,Comparator>::PriorityQueue(int maxNumber) : Heap<DataType>(maxNumber){
    
}

/**
*Enqueue    insert a new dataItem into the Priority Queue   
*
*@param     newDataItem   item to be inserted
*
*@pre   priority queue of size n 
*
*@post  priority queue of size n + 1
*
**/
template < typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType,KeyType,Comparator>::enqueue(const DataType& newDataItem){
    Heap<DataType>::insert(newDataItem);
}

/**
*dequeue   removes the max priority item off the heap
*
*@pre   priority queue of size n
*
*@post  priority queue of size n -1
*
**/
template < typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType,KeyType,Comparator>::dequeue(){
    return Heap<DataType>::remove();
}