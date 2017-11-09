#include "Heap.h"

template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::Heap(int maxNumber){
    dataItems = new T[maxNumber];
    maxSize = maxNumber;
    size = 0;
}

template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::Heap(const Heap& other ){
    dataItems = new T[other.maxSize];
    size = other.size;
    maxSize = other.maxSize;
    for(int i = 0 ; i < other.size; i ++){
        dataItems[i] = other.dataItems[i];
    }
}

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

template<class T, class Key, class Comparator>
Heap<T, Key, Comparator>::~Heap (){
    clear();
}

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

template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::clear (){
    size = 0;
    delete [] dataItems;
}

template<class T, class Key, class Comparator>
bool Heap<T, Key, Comparator>::isEmpty () const {
    return size == 0;
}

template<class T, class Key, class Comparator>
bool Heap<T, Key, Comparator>::isFull () const{
    return size >= maxSize;
}

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

template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::writeLevels () const{

}

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

template<class T, class Key, class Comparator>
void Heap<T, Key, Comparator>::heapifyUp(int index){
    while(index > 0 && comparator(dataItems[index].getPriority(), dataItems[parent(index)].getPriority())){
        int p = parent(index);
        swap(index, p);
        index = p;
    } 
}


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
