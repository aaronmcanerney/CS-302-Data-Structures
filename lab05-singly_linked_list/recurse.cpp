#include<iostream>
using namespace std;

void RecEm(int i );
int main(){
    RecEm(4);
}

void RecEm( int i ){
    if (i < 8){
        i++;
        RecEm(i);
        cout << i << " ";
    }
}