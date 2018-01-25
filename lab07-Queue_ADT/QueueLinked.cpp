/** @file QueueLinked.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif templated version of a node based queue.
@details provides all of the functionality associated with a queue.
contains enqueue and dequeue methods, clear, is empty, and is full functionality.
Also, has a couple of "extra" functionality methods such as put front and get rear.
@date 09/07/2017
**/


/**
@mainpage
Templated implementation of a list based queueue;
**/


//
// Header Files ///////////////////////////////////////////////////
//
#include "QueueLinked.h"

//
// Supporting Function Implementations //////////////////////////////
//

/**
*Constructor for the Queuenode.
*
*@param nodeData     the intitial data for the node
*@param nextPtr      the initial pointer (typically set to NULL)
*
*@return constructor - no return
*
*@pre The node will be uninitialized
*@post The node will be initialized with the parameters
**/
template<typename T>
QueueLinked<T>::QueueNode::QueueNode(const T& nodeData, QueueNode* nextPtr){
    dataItem = nodeData;
    next = nextPtr;
}


/**
*Constructor for the Queue class. Unused in this case - purely meant 
*to maintain equity betweent Node and Array based Queues.
*
*@param maxNumber    ambiguous number that is used for nothing in this particular case
*
*@return constructor - no return
*
*@pre queue is uninitialized
*@post queue is initialized, but empty, with both front and back set to NULL;
**/
template<class T>
QueueLinked<T>::QueueLinked(int maxNumber){
    front = back = NULL;
}


/**
*Copy constructor for the Queue. Will copy the contents from other,
*and create a new queue that is exactly the same. Uses the varaible temp as an
*iterator over the other queue.
*
*@param other    queue to be copied over
*
*@return constructor - no return
*
*@pre an uninitialized queue
*@post an initialized queue that is an exact copy of other
**/
template<class T>
QueueLinked<T>::QueueLinked(const QueueLinked<T>& other){
    front = back = NULL;
    QueueNode* temp = other.front;
    while(temp != NULL){
        enqueue(temp->dataItem);     
        temp = temp->next;    
    }
}


/**
*Overloaded equals operator. checks for self assignment and returns this if true.
*Otherwise clears the queue and procceeds to copy the other queue, using the exact same
methodolgy as the copy construtor;
*
*@param other   other queue to be copied from
*
*@return A QueueLinked of containing type T
*
*@pre   a queue, either empty or with data
*@post  a queue that is an exact copy of other
**/
template<class T>
QueueLinked<T>& QueueLinked<T>::operator=(const QueueLinked& other){
    if(this == &other){
        return *this;
    }
    clear();
    QueueNode* temp = other.front;
    while(temp != NULL){
        enqueue(temp->dataItem);
        temp = temp->next;
    }
    return *this;
}


/**
*Destructor. Deallocates the memory used by the QueueLinked object.
*Invokes the clear method (as the clear method performs deallocation).
*
*@param none
*
*@return none - destructor
*
*@pre (potentially) a queue of dynamically allocated nodes
*@post An empty queue with head = front = NULL and no allocated memory
**/
template<class T>
QueueLinked<T>::~QueueLinked(){
    clear();
}


/**
*Creates a new node and places it at the back of the queue.
*If the queue is empty prior to creating the new node, both front 
*and back point to the new node. Otherwise, back points to the new node.
*Throws a logic error if the user tries to enqueue a full queue
*
*@param newDataItem     new data to be used as an unitial value for the node
*
*@return void   no return
*
*@pre an empty/nonempty queue with n-1 nodes
*@post a queue with n items
**/
template<class T>
void QueueLinked<T>::enqueue(const T& newDataItem) throw (logic_error){
    if(!isFull()){
        if(isEmpty()){
            //empty
            QueueNode* node = new QueueNode(newDataItem, NULL);
            front = back = node;                                                    
        }
        else{
            //non empty
            QueueNode* node = new QueueNode(newDataItem, NULL);
            back->next = node;
            back = node;
        }
    }
    else{
        throw logic_error("enqueue() queue full");
    }
}


/**
*Removes the element at the front of the queue. Returns the data associated
*with the first node and dealocates memory. If the node has one element
*it deletes the element and sets back =  front = NULL. Else sets 
*front = to the next node. Throws logic error on dequeue of empty queue.
*
*@param none
*
*@return    data of type T
*
*@pre   an empty queue or a queue of size n
*@post  a queue of size n -1 and the data from the first element of the queue
**/
template<class T>
T QueueLinked<T>::dequeue() throw (logic_error) {
    if(!isEmpty()){
        T data = front->dataItem;
        //one node case
        if(front == back){
            delete front;
            front = back = NULL;
            return data;
        }
        else{
            //more than one node
            QueueNode* temp = front;
            front = front->next;
            delete temp;
            return data;
        }
    }
    else{
        throw logic_error("dequeue() queue empty");
    }
}


/**
*Deallocates all of the memory that is used by the Queue
*Does not check whether or not the queue is empty, as the 
*condition is covered by the iterator.
*
*@ param none
*
*@return    none void function
*
*@pre   an empty or non empty queue
*@post  an empty queue with no memory allocated
**/
template<class T>
void QueueLinked<T>::clear(){
    QueueNode* temp = front;
    while(temp != NULL){
        front = front->next;
        delete temp;
        temp = front;
    }
    //back = front = NULL
    back = front;
}


/**
*Return true if the queue is empty. Determines whether or not the queue is empty
*by checking whether or not the first element is pointing to NULL.
*
*@param none
*
*@return    boolean true if empty, false if not
*
*@pre   an empty/non empty queue 
*@post  an empty/non empty queue
**/
template<class T>
bool QueueLinked<T>::isEmpty() const {
    return front == NULL;
}


/**
*Always returns false as this is a node based implementation.
*this method exists to maintain consitency with the array based implementation
*
*@param  none
*
*@return   boolean always false
*
*@pre   an empty/non empty queue
*@post  an empty/non empty queue
**/
template<class T>
bool QueueLinked<T>::isFull() const {
    return false;
}


/**
*Puts a node at the front of the queue. If the queue if full throws a logic error
*if the queue was initially empty, simply enqueues the node. If the queue has data, 
*the method perfroms an insert front operation.
*
*@param newDataItem new data for the node
*
*@return    void no return
*
*@pre   an empty/non empty queue with n-1 nodes
*@post  a queue with n nodes, and the most recently created node at the front
**/
template<class T>
void QueueLinked<T>::putFront(const T& newDataItem) throw (logic_error){
    if(!isFull()){
        if(isEmpty()){
            enqueue(newDataItem);
        }
        else{
            QueueNode* temp = new QueueNode(newDataItem, front);
            front = temp;
        }
    }
    else{
        throw logic_error("putFront() queue full");
    }
}


/**
*Removes the most recently added item in the queue and returns it.
*The remainder of the queue is left unchanged. Throws logic error on empty
*queue
*
*@param none
*
*@return    dataItem of type T
*
*@pre a queue of size n
*@post a queue of size n-1 (missing the most recently added node)
**/
template<class T>
T QueueLinked<T>::getRear() throw (logic_error) {
    if(!isEmpty()){
        T temp;
        //one node case
        if(front == back){
            temp = front->dataItem;
            delete front;
            front = back = NULL;
            return temp;
        }
        else{
            //iterate up to the node behind back
            QueueNode* node = front;
            while(node->next != back){
                node = node->next;
            }
            //remove
            temp = back->dataItem;
            delete back;
            node->next = NULL;
            back = node;
            return temp;
        }
    }
    else{
        throw logic_error("getRear() queue empty");
    }
}


/**
*Returns the number of elements in the queue
*
*@param none
*
*@return    int size of the queue
*
*@pre   a queue of length n
*@post  a queue of length n
**/
template<class T>
int QueueLinked<T>::getLength() const {
    int count = 0;
    QueueNode* temp = front;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}


/**
*Shows the contents of the queue. Also shows the first element (indicated by brackets)
*Used for debugging purposes only
*
*@param none
*
*@return none void
*
*@pre   a queue of size n
*@post  a queue of size n
**/
template <typename DataType>
void QueueLinked<DataType>:: showStructure () const
// Linked queue implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    // Iterates through the queue
	QueueNode* p;

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != NULL ; p = p->next )
	{
	    if( p == front )
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}