#include <iostream>
#include "ListLinked.cpp"



using namespace std;

int main(){

    List<int> list;
    for(int i = 0; i < 10; i ++){
        list.insert(i);
    }

    cout << "Show original structure" << endl;
    list.showStructure();
    cout << endl;
   
    List<int> verify;

    verify = list;
    cout << "List created using overloaded assignment"<<endl;
    verify.showStructure();
    cout<<endl;


    cout << "Move cursor to the beggining and then two positions forward"<<endl;
    list.gotoBeginning();
    if(list.gotoNext());
    if(list.gotoNext());

    cout << "Show original structure with cursor moved ahead" << endl;
    list.showStructure();
    cout << endl;

    List<int> verify2;
    verify2 = list;

    cout << "Second List created using overloaded assignment, cursor moved ahead"<<endl;
    verify2.showStructure();
    cout<<endl;
    

    
}

