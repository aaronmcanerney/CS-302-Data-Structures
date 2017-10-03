#include<iostream>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <stdio.h>  
#include <stdlib.h>



using namespace std;

int main(int argc, char *arg[]){
    srand((unsigned) time(0));
    int random_integer;
    
    //cout << arg[0] << " " << arg[1]<< " "  << arg[2] << " "<< endl;
    ofstream myfile;
        myfile.open (arg[1]);
        for( int i = 0 ; i < atoi(arg[2]) ; i ++){
            random_integer = (rand()% 1000000)+1;
            myfile << random_integer << endl;
        }
        myfile.close();
        return 0;
}