/** @file Timer.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif Timer class - simple stopwatch style mechanics.
@details Provides basic functionality of a stop watch. Handles 
stopping the timer, starting the timer, calculating
the elapsed time and handling errors.
@date 09/23/2017
**/

#include"Timer.h"
#include<sys/time.h>

//const for conversion from seconds to micro seconds
const int MICRO = 1000000; 


/**
*Constructor that intializes timerWasStarted to false
*and begin time and duration to -1 to indicate that the clock has not read
*time yet
*
*@return constructor
*
*@pre unitialized timer object
*@post an initialized timer object with beging time and 
*end time being -1 to indicate stopped
**/
Timer::Timer(){
    timerWasStarted = false;
    beginTime.tv_sec = -1;
    duration.tv_sec = -1;
}

/**
* Start method that starts the timer by calling gettimeofday()
* and sets timerWasStarted to true
*
*@return void
*
*@pre unstarted timer and timerWasStarted is false
*
*@post timer is started and begin time has been set 
*as well as timerWasStarted (true)
*
*@throws throws runtime error if gettimeofday does not set
*the time
*
**/
void Timer::start() throw (runtime_error){
    gettimeofday(&beginTime, NULL);
    if(beginTime.tv_sec != -1){
        timerWasStarted = true;
    }
    else{
        throw runtime_error("System Error");
    }
}


/**
*Stop method that stops the timer by calling gettimeofday()
* and sets timerWasStarted to false
*
*@return void
*
*@pre started timer and timerWasStarted is true
*
*@post timer is stopped and stopped has been set 
*as well as timerWasStarted (false)
*
*@throws throws logic error an attempt to stop the timer
*is made prior to starting the timer
*
**/
void Timer::stop() throw (logic_error){
    if(timerWasStarted){
        gettimeofday(&duration,NULL);
        timerWasStarted = false;
    }
    else{
        throw logic_error("timer was not started");
    }
}


/**
* GetElapsedTime method that uses the beginTime and duration to 
*calculate the amount of time that has passed
*
*@return double that is duration - beginTime
*
*@pre two timevals indicating the start and end of an interval
*
*@post a single double that represents the amount of time passed
*
*@throws throws logic error if either of the timevals have not been set
*
**/
double Timer::getElapsedTime() const throw (logic_error){
if(beginTime.tv_sec != -1 && duration.tv_sec != -1){
        long time1 = beginTime.tv_sec * MICRO + beginTime.tv_usec;
        long time2 = duration.tv_sec * MICRO + duration.tv_usec;
        double elapsed = time2 - time1;
        return elapsed / MICRO;
    }
    else{
        throw logic_error("Begin time or duration has not been set properly");
    }
}