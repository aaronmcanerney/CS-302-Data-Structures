#include<iostream>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include "QueueLinked.cpp"
using namespace std;


int main(){
    srand(time(NULL));
    QueueLinked<int> q;
    QueueLinked<int> dur;
    int rand;
    for(int i = 0; i < 10; i ++){
        q.enqueue(i);
        dur.enqueue(i*10);
    }
    q.showStructure();

    QueueLinked<int> copyofQueue(dur);

    copyofQueue.showStructure();
    
    copyofQueue = copyofQueue;

    copyofQueue.showStructure();
}