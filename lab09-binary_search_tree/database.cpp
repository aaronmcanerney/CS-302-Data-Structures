/** @file BStree.cpp
 @author Aaron Mcanerney and lab book people
@version Revision 1.0
@breif data base implementation
@details Impleneted data base using the templated binary search tree.
Functionality as specified by c++ lab book.
@date 10/15/2017
**/

//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index

    if(acctFile){
        //get file size and divide by record 
        //length for number of records
        acctFile.seekg(0,acctFile.end);
        int size = acctFile.tellg();
        acctFile.seekg(0, acctFile.beg);
        size = size / bytesPerRecord + 1;
        
        //populate BST
        for(int i = 0; i < size; i++){
            entry.recNum = i;
            acctFile.seekg(i *(bytesPerRecord-1), acctFile.beg) >> entry.acctID;
            index.insert(entry);
        }

    }

    acctFile.clear();
   
  // Output the account IDs in ascending order.
    cout << endl << "Account IDs :" << endl;
    index.writeKeys();
    cout << endl<<endl;

    cout << "Enter account ID : ";
    cin >> searchID;


    // Clear the status flags for the database file.

    

    // Read an account ID from the keyboard and output the
    // corresponding record.
<<<<<<< HEAD
    while(searchID != cin.eof()){
=======
    cout << endl << "Enter account ID : ";
    cin >> searchID;
    //while(!cin.eof()){
>>>>>>> e4dcb423663e11a1121c51a2979a24b0834bdd07

        if(index.retrieve(searchID, entry)){
        
            acctFile.seekg(entry.recNum * (bytesPerRecord -1)
                ,acctFile.beg) >> acctRec.acctID >> acctRec.firstName >> acctRec.lastName
                    >> acctRec.balance;
            
            cout << acctRec.acctID << " " << acctRec.firstName << " " << acctRec.lastName <<
                " " << acctRec.balance << endl;
                cout << "Enter account ID : ";
                cin >> searchID; 
        }
        else{
            cout << "No record with that account ID"<<endl;
            cout << "Enter account ID (EOF to quit): ";
            cin >> searchID;
        }
   // }

    acctFile.close();
}
