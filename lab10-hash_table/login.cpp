#include "HashTable.cpp"
#include<fstream>
using namespace std;


class TestData {
public:
  TestData();
  void setKey(const string& newKey);
  string getKey() const;
  string getValue() const;
  void setValue(const string& val);
  static unsigned int hash(const string& str);

private:
  string key;
  string value;
};


TestData::TestData(){

}

void TestData::setKey(const string& newKey) {
  key = newKey;
}

string TestData::getKey() const {
  return key;
}

string  TestData::getValue() const {
  return value;
}

void TestData::setValue(const string& val){
    value = val;
}

unsigned int TestData::hash(const string& str) {
  unsigned int val = 0;

  for (int i = 0; i < str.length(); ++i) {
      val += str[i];
  }

  return val;
}
/*
class TestData {
public:
  TestData();
  void setKey(const string& newKey);
  string getKey() const;
  int getValue() const;
  static unsigned int hash(const string& str);

private:
  string key;
  int value;
  static int count;
};

int TestData::count = 0;

TestData::TestData() : value(++count) {
}

void TestData::setKey(const string& newKey) {
  key = newKey;
}

string TestData::getKey() const {
  return key;
}

int TestData::getValue() const {
  return value;
}

unsigned int TestData::hash(const string& str) {
  unsigned int val = 0;

  for (int i = 0; i < str.length(); ++i) {
      val += str[i];
  }

  return val;
}


*/

int main(){
    HashTable<TestData, string> table(8);
    string login;
    string password;
    ifstream in("password.dat");
    if(in){
        while(in >> login >> password){
           TestData temp;
           temp.setKey(login);
           table.insert(temp); 
        } 
    }
    
    table.showStructure();
    do{
        cout << "Login: ";
        cin >> login;
        cout << "Password: ";
        cin >>password;

        TestData temp;
        if(table.retrieve(login, temp)){
            if(temp.getValue().compare(password)){
                cout << "Authentication successful"<<endl;; 
            }
        }
        else{
            cout << "Authentication failure"<<endl;
        }
    }
    while(cin.good());
    return 0;
}