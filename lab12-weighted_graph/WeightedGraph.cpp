#include "WeightedGraph.h"

using namespace std;

WeightedGraph::WeightedGraph ( int maxNumber){
    vertexList = new Vertex[maxNumber];
    adjMatrix = new int[maxNumber * maxNumber];
    maxSize = maxNumber;
    size = 0;
}

WeightedGraph::WeightedGraph ( const WeightedGraph& other ){
    vertexList = new vertexList[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;
    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
    }
}


WeightedGraph& WeightedGraph::operator= ( const WeightedGraph& other ){
    if(this == &ohter){
        return *this;
    }

    clear();
    
    vertexList = new vertexList[other.maxSize];
    adjMatrix = new int[other.maxSize * other.maxSize];
    maxSize = other.maxSize;
    size = other.size;
    
    for(int i = 0; i < size; i++){
        vertexList[i] = other.vertexList[i];
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
    index1 = conv1D(temp1,temp2);
    index2 = conv1D(temp2, temp1);

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
    if(index1 != -1 && index2 != -1){
        if(adjMatrix[conv1D(index1,index2)] != -1){
            wt = adjMatrix[conv1D(index1, index2)];
            return true;
        }
        return false;
    }
    else{
        throw logic_error("getEdgeWeight    No Such Verticies.")
    }
}                      
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error ){

}

void WeightedGraph::removeEdge ( const string& v1, const string& v2 )  throw ( logic_error ){
    
    adjMatrix[conv1D(getIndex(v1),getIndex(v2))] = -1;
}

void WeightedGraph::clear (){
    delete [] vertexList;
    delete [] adjMatrix;
    size = 0;
    vertexList = new Vertex[maxNumber];
    adjMatrix = new adjMatrix[maxNumber * maxNumber];
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
        if(!vertexList[i].compare(v)){
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

void WeightedGraph::showStructure () const {
    {
        if ( size == 0 ) {
        cout << "Empty graph" << endl;
        } else {
        cout << endl << "Vertex list : " << endl;
        for ( int row = 0 ; row < size ; row++ )
            cout << row << '\t' << vertexList[row].label
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
                if ( wt == infiniteEdgeWt )
                    cout << "- \t";
                else
                    cout << wt << '\t';
            }
            cout << endl;
        }
        }
    }
}

 