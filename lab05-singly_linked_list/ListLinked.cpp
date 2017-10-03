#include "ListLinked.h"



using namespace std;

/*
List node constructor
*/
template<typename T>
List<T>::ListNode::ListNode(const T& nodeData, ListNode* nextPtr) {
    dataItem = nodeData;
    nextPtr = NULL;
}

/*
List constructor
Unused - meant to keep compatibilty with array based version
*/
template<class T>
List<T>::List(int ignored) {
    head = NULL;
    cursor = NULL;
}

/*
copy constructor
*/
template<class T>
List<T>::List(const List<T>& other) {
    head = cursor = NULL;
    ListNode* temp = other.head;
    //ListNode* t_cursor = other.head;
    while(temp != NULL){
          insert(temp->dataItem);
          temp = temp->next;
    }
    cursor = head;
    temp = other.head;


    while(temp != other.cursor){
        temp = temp->next;
        cursor = cursor->next;
    }
}


/*
overloaded assignment operator
calls clear to delete list then copies
*/
template<class T>
List<T>& List<T>::operator=(const List<T>& other){
   // head = cursor = NULL;
    if(this == &other){
       return *this;
    }
    clear();    //clear data
    ListNode* temp = other.head;
    while(temp != NULL){
        insert(temp->dataItem);
        temp = temp->next;
    }
    temp = other.head;
    cursor = head;
    while(temp != other.cursor){
        temp = temp->next;
        cursor = cursor->next;
    }
    return *this;
}


/*
List destructor
*/
template<class T>
List<T>::~List(){
    clear();
}

/*
inserts a new node into the list at the end of the cursor
throws a log error if the list is full
*/
template<class T>
void List<T>::insert(const T& newDataItem) throw(logic_error) {
    if(!isFull()) {
        ListNode* node = new ListNode(newDataItem, NULL);
        if(isEmpty()){
            //insert only node
            head = node;
            cursor = head;
        }
       else{
            //kills two birds with one stone
            //insert middle and end cases in one
            node->next = cursor->next;
            cursor->next = node;
            cursor = node;
        }
    }
    else {
        clear();
        throw logic_error("insert() full list");       
    }
}

/*
Removes the item the cursor is pointing at.
Throws logic error if the list is empty,
otherwise removes and sets cursor to next or the begginging
of the list.
*/
template<class T>
void List<T>::remove() throw (logic_error){
    if(!isEmpty()){
        //1 node in list
        if(head->next == NULL){
            delete head;
            cursor = head = NULL;
        }
        //cursor is last node
        else if(cursor->next == NULL){
            ListNode* temp = cursor;
            gotoPrior();
            delete temp;
            cursor->next = NULL;
            cursor = head;
        }
        //more than one entry
        else{
            ListNode* temp = cursor;
            //cursor has prior
            if(gotoPrior()){
                cursor->next = temp->next;
                cursor = temp->next;
                delete temp;
            }
            //cursor is first element
            else{
                head = cursor->next;
                delete cursor;
                cursor = head;
            }
        }
    }
    else{
        throw logic_error("remove() empty list");
    }
}

/*
Replaces the data item at the cursor with the new data item. 
Throws error on empty list
*/
template<class T>
void List<T>::replace(const T& newDataItem)  throw (logic_error) {
    if(!isEmpty()){
        cursor->dataItem = newDataItem;
    }
    else{
        throw logic_error("replace() empty list");
    }
}

/*
Removes all of the nodes from the list.
Since this is a node based implementation, the 
function deallocates all of the nodes in the list and sets head 
and cursor to null. 
*/
template<class T>
void List<T>::clear(){
    ListNode* node = head;
    while(node != NULL){
        ListNode* temp = node->next;
        delete node;
        node = temp;
    }
    head = NULL;
    cursor = NULL;
}

/*
Returns whether or not the function is empty.
*/
template<class T>
bool List<T>::isEmpty() const {
    return head == NULL;
}

/*
Returns whether or not the list is full.
Always returns false as we assume we have
"infinite" memory. Retains compatibility with
array based implementation.
*/
template<class T>
bool List<T>::isFull() const {
    return false;
}

/*
Moves the cursor to the begining of the list.
Sets cursor-> next to the next value in the list.
Errors on empty list.
*/
template<class T>
void List<T>::gotoBeginning() throw (logic_error) {
    if(!isEmpty()){
        cursor = head;
        //cursor->next = head->next;
    }
    else{
        throw logic_error("gotoBeginning() empty list");
    }
}

/*
Iterates through the list until the cursor is the last element in the list.
Errors on empty list.
*/
template<class T>
void List<T>::gotoEnd() throw (logic_error) {
    if(!isEmpty()){
        while(gotoNext());
    }
    else{
        throw logic_error("gotoEnd() empty list");
    }
 }

/*
Iterates to the next node in the list if the 
cursor is not already at the end of the list.
Throws error on empty list.
*/
template<class T>
bool List<T>::gotoNext() throw (logic_error){
    if(!isEmpty()){
        if(cursor->next != NULL){
            cursor = cursor->next;
            return true;
        }
        return false;
    }
    else{
        throw logic_error("gotoNext() empty list");
    }
}

/*
Gets the node behind the cursor.

*/
template<class T>
bool List<T>::gotoPrior() throw (logic_error){
    if(!isEmpty()){
        //if we are not at beginning of list
        if(cursor != head){
            //iterate until next node is cursor and return
            ListNode* node = head;
            while(node->next != cursor){
                node = node->next;
            }
            cursor = node;
            return true;
        }
        return false;
    }
    else{
        throw logic_error("gotoPrior() empty list");
    }
    
}
/*
returns the dataitem that is at the cursor
*/
template<class T>
T List<T>::getCursor() const throw (logic_error){
    if(!isEmpty()){
        return cursor->dataItem;
    }
}
/*
moves the element indicated by the cursor to the
beggining of the list
*/
template<class T>
void List<T>::moveToBeginning() throw (logic_error){
    if(!isEmpty()){
        //create new node with data
        ListNode* temp = new ListNode(getCursor(), NULL);
        //remove
        remove();
        //insert front
        temp->next = head;
        head = cursor = temp;
    }
    else{
        throw logic_error("moveToBeginning() empty list");
    }
}

/*
inserts the newDataItem infront of the cursor.
If there is no data in the list, inserts front
*/
template<class T>
void List<T>::insertBefore(const T& newDataItem) throw (logic_error){
    if(!isFull()){
        if(isEmpty()){
            //empty case
            insert(newDataItem);
        }
        else{
            ListNode* temp = cursor;
            //middle of list
            if(gotoPrior()){
                insert(newDataItem);
            }
            //insert front case
            else{
                ListNode* node = new ListNode(newDataItem, NULL);
                node->next = head;
                head = node;
                cursor = node;
            }
        }
    }
    else{
        throw logic_error("insertBefore() full list");
    }
}
/*
Factory method from the lab book - unchanged and without proper NULL check
*/
template<class T>
void List<T>::showStructure() const{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}

