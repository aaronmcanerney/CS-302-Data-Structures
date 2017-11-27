#include "WeightedGraph.h"
#include <limits>  

using namespace std;

WeightedGraph::WeightedGraph ( int maxNumber){
    vertexList = new Vertex[maxNumber];
    adjMatrix = new int[maxNumber * maxNumber];
    maxSize = maxNumber;
    size = 0;
    fillMatrix();
}

WeightedGraph::WeightedGraph ( const WeightedGraph& other ){
    vertexList = new Vertex[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;
    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
    }
}


WeightedGraph& WeightedGraph::operator= ( const WeightedGraph& other ){
    if(this == &other){
        return *this;
    }

    clear();
    
    vertexList = new Vertex[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;
    
    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
    }

    for(int i = 0; i < maxSize; i++){
        for(int j = 0; j < maxSize; j++){
            adjMatrix[conv1D(i,j)] = other.adjMatrix[conv1D(i,j)];
        }
    }

    return *this;
}


WeightedGraph::~WeightedGraph (){
    delete [] vertexList;
    delete [] adjMatrix;
}


void WeightedGraph::insertVertex ( const Vertex& newVertex ) throw ( logic_error ){
    if(!isFull()){
        size++;
        vertexList[size-1] = newVertex;
    }
    else{
        throw logic_error("insertVertex Graph Full");
    }
}
    
void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error ){
    int temp1 = getIndex(v1);
    int temp2 = getIndex(v2);
    int index1 = conv1D(temp1,temp2);
    int index2 = conv1D(temp2, temp1);

    if(inBound(index1)){
        adjMatrix[index1] = wt;
    }

    if(inBound(index2)){
        adjMatrix[index2] = wt;
    }
}

bool WeightedGraph::retrieveVertex ( const string& v, Vertex& vData ) const{
    if(inBoundV(getIndex(v))){
        vData = vertexList[getIndex(v)];
        return true;
    }
    return false;
}

bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error ){
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);
    if(index1 != INFINITE_EDGE_WT && index2 != INFINITE_EDGE_WT){
        if(adjMatrix[conv1D(index1,index2)] != INFINITE_EDGE_WT){
            wt = adjMatrix[conv1D(index1, index2)];
            return true;
        }
        return false;
    }
    else{
        throw logic_error("getEdgeWeight    No Such Verticies.");
    }
}                      
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error ){
    if(getIndex(v) != -1){

    }
}

void WeightedGraph::removeEdge ( const string& v1, const string& v2 )  throw ( logic_error ){
    if(!isEmpty()){
        adjMatrix[conv1D(getIndex(v1),getIndex(v2))] = INFINITE_EDGE_WT;
    }
    else{
        throw logic_error("removeEdge() removeEdge on Empty List");
    }
}

void WeightedGraph::clear (){
    delete [] vertexList;
    delete [] adjMatrix;
    size = 0;
    vertexList = new Vertex[maxSize];
    adjMatrix = new int[maxSize * maxSize];
}                         

bool WeightedGraph::isEmpty () const {
    return size == 0;
}               
             
bool WeightedGraph::isFull () const{
    return size >= maxSize;
}      

void WeightedGraph::showShortestPaths () const{

}

bool WeightedGraph::hasProperColoring() const{

}

bool WeightedGraph::areAllEven () const{

}


int WeightedGraph::getIndex ( const string& v ) const{
    for(int i = 0; i < size; i++){
        if(vertexList[i].getLabel().compare(v) == 0){
            return i;
        }
    }
    return -1;
}        
                                               
int WeightedGraph::getEdge ( int row, int col ) const{
    return adjMatrix[conv1D(row,col)];
}        
                                               
void WeightedGraph::setEdge ( int row, int col, int wt){
    adjMatrix[conv1D(row,col)] = wt;
}

void WeightedGraph::fillMatrix(){
    for(int i = 0; i < maxSize; i++){
        for(int j = 0; j < maxSize; j++){
            adjMatrix[conv1D(i,j)] = INFINITE_EDGE_WT;
        }
    }
}

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

 