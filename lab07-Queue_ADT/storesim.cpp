//--------------------------------------------------------------------
//
//  Laboratory 7, Programming Exercise 1                   storesim.cs
//
//  Program implementation shell.
//
//--------------------------------------------------------------------
/** @file storesim.cpp
@author Aaron Mcanerney and LabBook
@version Revision 1.1
@breif Simulated store using queue
@details A simulated store that uses the queue to calculate the
average wait time of customers, as well as stores the customers themselves.
@date 09/07/2017
**/
// Simulates the flow of customers through a line in a store.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"


// Use which ever implementation is currently configured.
#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif

using namespace std;


int main ()
{
#if LAB7_TEST1
    QueueLinked<int> custQ;      // Line (queue) of customers containing the
#else
    QueueArray<int> custQ;       // Line (queue) of customers containing the
#endif 				 //   time that each customer arrived and
                                 //   joined the line
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        timeArrived,             // Time dequeued customer arrived
        waitTime,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0;         // Number of new arrivals

    const int seed = 7;
    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand(seed);

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.
    
    int k;
    while(minute <= simLength){
        minute++;
        if(!custQ.isEmpty()){
            timeArrived = custQ.dequeue();
            waitTime = minute - timeArrived;
            totalWait += waitTime;
            totalServed++;
            if(maxWait < waitTime)
                maxWait = waitTime;
        }
        k = rand() % 4;
        if(k == 1){
            custQ.enqueue(minute);
            numArrivals++;
        }
        else if(k == 2){
            custQ.enqueue(minute);
            custQ.enqueue(minute);
            numArrivals += 2;
        }
    }
    



    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}