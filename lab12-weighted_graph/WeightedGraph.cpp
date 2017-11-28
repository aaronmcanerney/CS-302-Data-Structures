/** @file WeightedGraph.cpp
@author Aaron Mcanerney
@version Revision 1.0
@breif weighted graph implementation
@details weighted graph implemtntaion using adjaceny matrix.
Functionality as specified by c++ lab book.
@date 111/27/2017
**/


#include "WeightedGraph.h"

using namespace std;


/**
*WeightedGraph      constructor
*
*@param maxNumber   maxnumber of vertices
*
*@pre   unititalized graph 
*
*@post  initialized graph
*
**/
WeightedGraph::WeightedGraph ( int maxNumber){
    vertexList = new Vertex[maxNumber];
    adjMatrix = new int[maxNumber * maxNumber];
    maxSize = maxNumber;
    size = 0;
    fillMatrix();
}

/**
*WeightedGraph      copy constructor
*
*@param other   graph to be copied from
*
*@pre   unititalized graph 
*
*@post  initialized graph
*
**/
WeightedGraph::WeightedGraph ( const WeightedGraph& other ){
    vertexList = new Vertex[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;

    //copy vertex
    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
    }
    //copy adjmatrix
    for(int i = 0; i < maxSize * maxSize; i++){
        adjMatrix[i] = other.adjMatrix[i];
    }
}

/**
*operator=      overloaded assignment operator
*
*@param other   other graph to be copied from
*
*@pre   unititalized graph 
*
*@post  initialized graph
*
**/
WeightedGraph& WeightedGraph::operator= ( const WeightedGraph& other ){
    if(this == &other){
        return *this;
    }

    //clear function not needed
    delete [] vertexList;
    delete [] adjMatrix;
    
    vertexList = new Vertex[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;

    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
    }

    for(int i = 0; i < maxSize * maxSize; i++){
       adjMatrix[i] = other.adjMatrix[i];
    }

    return *this;
}

/**
*~WeightedGraph      destructor
*
*@pre   allocated memory
*
*@post  all memory deallocated
*
**/
WeightedGraph::~WeightedGraph (){
    delete [] vertexList;
    delete [] adjMatrix;
}

/**
*insertVertex   inserts a vertex into the graph
*
*@param newVertex   new vertex in the graph
*
*@pre   graph with n - 1 vertices
*
*@post  graph with n vertices
*
*@throws    throws exception if the graph is full
*
**/
void WeightedGraph::insertVertex ( const Vertex& newVertex ) throw ( logic_error ){
    if(!isFull()){
        size++;
        vertexList[size-1] = newVertex;
    }
    else{
        throw logic_error("insertVertex Graph Full");
    }
}

/**
*inertEdge     inserts an edge into the graph
*
*@param v1  vertex one
*
*@param v2  vertex two
*
*@param wt  weight of the edge
*
*@pre   graph with some edge weight between v1 and v2
*
*@post  v1 and v2 are connected with weight wt
*
*@throws throws exception if the vertices don't exist in the graph
**/
void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error ){
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);
    if(inBound(index1) && inBound(index2)){
        adjMatrix[conv1D(index1,index2)] = wt;
        adjMatrix[conv1D(index2, index1)] = wt;
    }
    else{
        throw logic_error("insertEdge index out of bounds");
    }
}

/**
*retrieveVertex     gets the data of the given vertex
*
*@param v   vertex to check
*
*@param vData   container for data
*
*@pre   graph
*
*@post  returns true if the vertex v exists in the graph
*
**/
bool WeightedGraph::retrieveVertex ( const string& v, Vertex& vData ) const{
    if(inBound(getIndex(v))){
        vData = vertexList[getIndex(v)];
        return true;
    }
    return false;
}

/**
*getEdgeWeight      gets the weight of the edge between v1 and v2
*
*@param v1  vertex one
*
*@param v2  vertex two
*
*@param wt  container for the weight between v1 and v2
*
*@pre   graph 
*
*@post  returns true if v1 amd v2 are connected
*
*@throws    throws execption if the vertices dont exist
*
**/
bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error ){
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);
    if(inBound(index1) && inBound(index2)){
        if(adjMatrix[conv1D(index1,index2)] != INFINITE_EDGE_WT){
            wt = adjMatrix[conv1D(index1,index2)];
            return true;
        }
        else{
            return false;
        }
    }
    else{
        throw logic_error("getEdgeWeight    No Such Verticies.");
    }
}      

/**
*removeVertex   removes a vertex from the graph
*
*@param v   vertex to be removed
*
*@pre   graph of v vertexs
*
*@post  graph of v - 1 vertexs
*
@throws throws exception if the vertex does not exist
*
**/
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error ){
    if(inBound(getIndex(v))){
        int removal = getIndex(v);

        for(int i = removal; i < size - 1; i++){
            vertexList[i] = vertexList[i+1];
        }
        int cap = size * size;
        cout << "cap " << cap<<endl;
        cout << "removal " << removal << endl;
        for(int i = removal; i < cap; i += size){
            cout << "iterator " << i<<endl;
            adjMatrix[i] = adjMatrix[i+1];
            cout << "matrix at i " << adjMatrix[i] << endl;
        }
        /*
        int temp[(size- 1)* (size-1)];
        for(int i = 0; i < size*size; i++){
            if()
        }*/
        showStructure();/*
        for(int i = removal * size; i < size * size;)
        */
        size--;
        
    }

}

/**
*removeEdge   removes the edge between two vertices
*
*@param v1  vertice one
*
*@param v2  vertice two
*
*@pre   graph with potential edge between v1 and v2
*
*@post  edge between v1 and v2 has been removed
*
*@throws    throws exception if the graph does not contain the vertices
*
**/
void WeightedGraph::removeEdge ( const string& v1, const string& v2 )  throw ( logic_error ){
    if(inBound(getIndex(v1)) && inBound(getIndex(v2))){
        adjMatrix[conv1D(getIndex(v1),getIndex(v2))] = INFINITE_EDGE_WT;
        adjMatrix[conv1D(getIndex(v2),getIndex(v1))] = INFINITE_EDGE_WT;
    }
    else{
        throw logic_error("removeEdge() No Such Vertices");
    }
}

/**
*clear     sets size = 0
*
*@pre   graph of size n
*
*@post  graph of size 0
*
**/
void WeightedGraph::clear (){
    size = 0;
}                         

/**
*isEmpty    returns true if size == 0
*
*@pre   graph of size n
*
*@post  returns true if size == -0
*
**/
bool WeightedGraph::isEmpty () const {
    return size == 0;
}               
            
/**
*isFull     returns true if the graph is full
*
*@pre   graph of size n
*
*@post  returns true if size >= maxSize
*
**/
bool WeightedGraph::isFull () const{
    return size >= maxSize;
}      


/**
*showShortestPaths      shows the shortest path in the adjMatrix
*
*@pre   graph with no shortest paths
*
*@post  matrix that shows the shortest paths
*
**/
void WeightedGraph::showShortestPaths (){
    /*
    int path[size * size];
    for(int i = 0; i < size * size; i++){
        if(i % (size + 1) == 0){
            path[i] = 0;
        }
        else{
            path[i] = adjMatrix[i];
        }
    }
    int sum = 0;
    for(int m = 0; m < size; ++m){
        for(int j = 0; j < size; ++j){
            for(int k = 0; k < size; ++k){
                if(getEdge(j,m) != INFINITE_EDGE_WT && getEdge(m,k) != INFINITE_EDGE_WT){
                    sum = (getEdge(j,m) + getEdge(m,k));
                    if(sum < getEdge(j,k)){
                        setEdge(j,k, sum);
                    }
                }
            }
        }
    }
    */
   // showStructure();
}

/**
*hasProperColering determines if adjacent vertices have different colors
*
*@pre   graph 
*
*@post  returns true if the adjacent vertices have different colors
*
**/
bool WeightedGraph::hasProperColoring() const{
    for(int i = 0 ; i <  (size * size) - 1; i++){
        
    }
}

/**
*WeightedGraph      constructor
*
*@param maxNumber   maxnumber of vertices
*
*@pre   unititalized graph 
*
*@post  initialized graph
*
**/
bool WeightedGraph::areAllEven () const{
    for(int i = 0; i < size; i ++){

    }
}

/**
*getIndex   returns the index associated with a given vertex
*
*@param v   vertex to check
*
*@pre   graph
*
*@post  returns the index of the given vertex
*
**/
int WeightedGraph::getIndex ( const string& v ) const{
    for(int i = 0; i < size; i++){
        if(vertexList[i].getLabel().compare(v) == 0){
            return i;
        }
    }
    return -1;
}        
              
/**
*getEdge    gets the edge between to vertices (indexed)
*
*@param     row     row of the vertex
*
*@param     col     columb of the vertex
*
*@pre   graph 
*
*@post  returns the edge weight
*
**/
int WeightedGraph::getEdge ( int row, int col ) const{
    return adjMatrix[conv1D(row,col)];
}        

/**
*setEdge        sets the edge weight
*
*@param row     row of vertex
*
*@param col     col of the vertex
*
*@param wt      weight of the edge
*
*@pre   graph with n - 1 edges
*
*@post  graph with n edges
*
**/ 
void WeightedGraph::setEdge ( int row, int col, int wt){
    adjMatrix[conv1D(row,col)] = wt;
}


/**
*fillMatrix    fills the matrix with max edge wieght
*
*@pre   unititalized graph 
*
*@post  graph with infinite edge wieght
*
**/
void WeightedGraph::fillMatrix(){
    for(int i = 0; i < maxSize*maxSize; i++){
        adjMatrix[i] = INFINITE_EDGE_WT;
    }
}


/**
*showStructure      prints graph to terminal
*
*@pre   graph
*
*@post  prints graph to terminal
*
**/
void WeightedGraph::showStructure () const {
    {
        if ( size == 0 ) {
        cout << "Empty graph" << endl;
        } else {
        cout << endl << "Vertex list : " << endl;
        for ( int row = 0 ; row < size ; row++ )
            cout << row << '\t' << vertexList[row].getLabel()
        #if LAB12_TEST2
            << vertexList[row].color
        #endif
            << endl;

        cout << endl << "Edge matrix : " << endl << '\t';
        for ( int col = 0 ; col < size ; col++ )
            cout << col << '\t';
        cout << endl;
        for ( int row = 0 ; row < size ; row++ )
        {
            cout << row << '\t';
            for ( int col = 0 ; col < size ; col++ )
            {
                int wt = getEdge(row,col);
                if ( wt == INFINITE_EDGE_WT )
                    cout << "- \t";
                else
                    cout << wt << '\t';
            }
            cout << endl;
        }
        }
    }
}

 