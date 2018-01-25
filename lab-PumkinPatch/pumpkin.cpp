/** @file PumpkinPatch.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif finds all of the pumpkins for charlie brown and his friends
@details for every patch, a boolean array is created. The boolean array is iterated
over and marked off once each of the indexes has been visited. The loop 
passes an index to the recursive function where (if it is a pumpkin),
the neighbors are found and recursed on. Once the recursive call is over,
we have a modified boolean array indicating the unvisited portions of the patch
and the number of pumkins in that portion of the patch. Upon completing the search,
the results are sorted and outputted.
@date 09/13/2017
**/


#include <iostream>

using namespace std;

//40 * 40 using a 1d array
const int MAX_SIZE = 1600;
//number of possible neighbors for any given node
const int NEIGHBORS = 4;

//read in the data into my array
void read(char arr[], int &length, int &width,int  &size);
//print the array at the end
void print(const int arr[], const int size);

//recursive pumpkin patch finder
void patch(const char arr[], const int length, const int width,bool bools[], int &count, const int index);
//get the neighbors of a given index
void getNeighbors(const int index, int neighbors[], const int length, const int width);
//bubblesort
void lazyManBubbleSort(int arr[], const int size);



/**
*Main method. Holds all variabls such as size, width that are used for array manipulation.
*Contains the loops that run the program and is responsible for output.
*@return int success/failure
*
*@pre unitialized values
*@post Algorithm is run and output has been printed to console
**/
int main(){

    char arr[MAX_SIZE]; //1d array cus im freakin sick
    
    int length;
    int width;  
    int size;   //length * width

    //array for sorting the patches
  
    int gnumber = 0;    //number of garden
    read(arr, length, width, size); //read data into one 2 array - mandatory first read in to set size condition
    int ascendingPatches[MAX_SIZE / 2];
    while(size > 0){
        gnumber++;

        int count = 0;  //counter for patch size
        int numPatches = 0; //counter for total number of patches
        int iter = 0;   //iterator for placement of counts in sorting array

        bool bools[size] = {false};   //boolean array keeps track of visited "nodes"
        //go through every value in the boolean array
        for(int i = 0; i < size; i++){
            //if we havent visited the node
            if(!bools[i]){
                //find patch
              patch(arr, length, width, bools, count, i);
                //if a patch was found (count > 0 )
                if(count > 0){
                    //add patch to list
                    ascendingPatches[iter] = count;
                    //increment and reset vars
                    iter++;
                    count = 0;
                    numPatches++;
                }
                
            }
        }
        //sort all of the patches with the lazy man bubble sort
        lazyManBubbleSort(ascendingPatches, numPatches);
        //begin print
        cout<< "Garden # "<< gnumber << ": " << numPatches << " patches, sizes:";
        print(ascendingPatches, numPatches);
        // next iteration
        read(arr, length, width, size);
    }
    cout << endl;
    return 0;
}


/**
*Patch finder. Accepts an index, checks whether or not it is a pumking. 
*If it is a pumkin, the function increments the counter, finds the neighboring
*potential pumkins, and calls itself with each of the neighbors as the new index.
*Also marks of all of the items as the patch as visited if the function was
*called with thier index as an argument.
*
*@param arr[]   character array containing the pumkin patch data
*@param length  length of the "2d array"
*@param width   width of the "2d array"
*@param bools[] boolean array containing every node and whether or not they have been visited
*@param count   a counter passed by reference - increments with every pumkin we find
*@param index   the index that we are currently at
*
*@return void no return
*
*@pre boolean array with values marked off and count varaible set at n
*@post boolean array with one more "vertex" visited  and potentially an increased count
**/
void patch(const char arr[], const int length, const int width, bool bools[], int &count, const int index){
    char c = arr[index];
    bools[index] = true;
    
    //if not a pumkin we leave
    if(c != 'p'){
        return;
    }
    //initialize neighbors array
    int neighbors[NEIGHBORS] = {-1};
    //found a pumkin incrememnt count
    count++;
    //get the neighbors
    getNeighbors(index, neighbors, length, width);
    //call patch on every neighbor
    for(int i = 0; i < NEIGHBORS; i++){
        if(neighbors[i] != -1 && !bools[neighbors[i]]){
            patch(arr, length, width, bools, count, neighbors[i]);
        }
    }
    
}



/**
*Helper function that gets the neighbors of an index. If the neighbor would be out
*of bounds, the index is set to -1. This indicates to the patch function to skip
*the recursive call
*
*@param neighbors[] int array of the neighbors of a given index
*@param length  length of the "2d array"
*@param width   width of the "2d array"
*@param index   the index that we are currently at
*
*@return void no return
*
*@pre an int array initialized to -1
*@post an array containing the neighbors of a given index
**/
void getNeighbors(const int index, int neighbors[], const int length, const int width){
    //left bound check
    if(index % length > 0){
        neighbors[0] = index - 1;
    }
    else{
        neighbors[0] = -1;
    }
    //right bound check
    if((index + 1) % length > 0){
        neighbors[1] = index + 1;
    }
    else{
        neighbors[1] = -1;
    }
    //up bound check
    if(index - length > 0){
        neighbors[2] = index - length;
    }
    else{
        neighbors[2] = -1;
    }
    //down bound check
    if(index + length < length * width){
        neighbors[3] = index + length;
    }
    else{
        neighbors[3] = -1;
    }
}


/**
*Helper function that sorts the sizes of the patches 
*in ascending order
*
*@param arr[] int array of pumkin patch sizes
*@param size    size of the int array
*
*@return void no return
*
*@pre an unsorted int array
*@post a sorted int array
**/
void lazyManBubbleSort(int arr[], int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size -1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


/**
*Helper function that reads in the pumkin patch from a file
*Decomposes a 2d array into a 1d array. Allows other functions
*to use arithmatic to move around the array.
*
*@param arr[] character array filled with data
*@param length  length of the "2d array"
*@param width   width of the "2d array"
*@param size    size of the array
*
*@return void no return
*
*@pre unfilled char array and width = length = size = 0
*@post filled char array and width length and size are read in
**/
void read(char arr[], int &length, int &width, int &size){
    cin >> width >> length;
    size = length * width;
    for(int i = 0 ; i < size; i++){
        cin >> arr[i];
    }
}

/**
*Helper function that prints the sorted array to console
*
*@param arr[]   int array with sorted data
*@param size    size of the array
*
*@return void no return
*
*@pre no output
*@post outputs sorted array to console
**/
void print(const int arr[], int size){
    if(size > 0){
        cout << " ";
    }
    for(int i = 0; i < size; i++){
        if(i != size -1)
            cout << arr[i] <<" ";
        else
            cout << arr[i] << endl;
    }
}