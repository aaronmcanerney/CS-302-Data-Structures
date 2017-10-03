#include<iostream>
#include <unistd.h>

using namespace std;

struct Vehicle{
    int length;
    char orientation;
    int row;
    int column;
};

const int CAR = 2;
const int TRUCK = 3;
const char HORIZONTAL = 'H';
const int MAX_ARR = 6;
const int MAX_VEHICLE = 10;
unsigned int microseconds = 2000000;

void read(int board[][MAX_ARR], int& numCars, Vehicle cars[]);
void setBoard(int board[][MAX_ARR], const Vehicle& v, const int car);
bool isCar(const Vehicle& v);
void print(const int board[][MAX_ARR]);
void fillArray(int board[][MAX_ARR]);
bool moveForward(Vehicle& v, int board[][MAX_ARR]);
bool moveBackward(Vehicle& v, int board[][MAX_ARR]);
bool isComplete(const Vehicle& v, const int board[][MAX_ARR]);
bool isHorizontal(const Vehicle& v);
bool solve(int& numMoves, Vehicle cars[], int board[][MAX_ARR], int& best,const int& numCars, bool& result);
bool isCollisionForward(const Vehicle& v, const int board[][MAX_ARR]);
bool isCollisionBackward(const Vehicle& v, const int board[][MAX_ARR]);


int main(){
    int board[MAX_ARR][MAX_ARR];
    Vehicle cars[MAX_VEHICLE];
    int numCars;
    fillArray(board);

    read(board, numCars, cars);
    print(board);
    int moves = 0;
    int best = 10;
    bool result = false;
    if(solve(moves, cars,board,best, numCars, result)){
        cout << "Solved in "<< best<< " moves"<<endl;
    }
    else{
        cout <<"Impossibruuuuuu"<<endl;
    }
    //print(board);
    return 1;
}



void read(int board[][MAX_ARR], int& numCars, Vehicle cars[]){
    cin >> numCars;
    for(int i = 0; i < numCars; i++){
        Vehicle v;
        cin >> v.length >> v.orientation >> v.row >> v.column;
        //cout << v.length << " " << v.orientation << " " << v.row << " " << v.column << " " << endl;
        cars[i] = v;
        setBoard(board, v, i+1);
    }
}

void setBoard(int board[][MAX_ARR], const Vehicle& v, const int car){
    for(int i = 0 ; i < v.length; i++){
        if(isHorizontal(v)){
            board[v.row][v.column + i] = car; 
        }
        else{
            board[v.row + i][v.column] = car;
        }
    }
}

bool isCar(const Vehicle& v){
    return v.length == CAR;
}

bool isHorizontal(const Vehicle& v){
    return v.orientation == HORIZONTAL;
}

void print(const int board[][MAX_ARR]){
    for(int i = 0; i <  6; i ++){
        for(int j = 0; j < 6; j ++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void fillArray(int board[][MAX_ARR]){
    for(int i = 0; i <  MAX_ARR; i ++){
        for(int j = 0; j < MAX_ARR; j ++){
            board[i][j] = 0;
        }
    }
}

bool isCollisionForward(const Vehicle& v, const int board[][MAX_ARR]){
    if(isHorizontal(v)){
        if(isCar(v)){
            if(board[v.row][v.column + CAR] != 0){
                return true;
            }
        }
        else{
            if(board[v.row][v.column + TRUCK] != 0){
                return true;
            }
        }
    }
    else{
        if(isCar(v)){
            if(board[v.row + CAR][v.column] != 0){
                return true;
            }
        }
        else{
            if(board[v.row + TRUCK][v.column] != 0){
                return true;
            }
        }
    }
    return false;
}

bool isCollisionBackward(const Vehicle& v, const int board[][MAX_ARR]){
    if(isHorizontal(v)){
        if(isCar(v)){
            if(board[v.row][v.column - 1] != 0){
                return true;
            }
        }
        else{
            if(board[v.row][v.column - 1] != 0){
                return true;
            }
        }
    }
    else{
        if(isCar(v)){
            if(board[v.row - 1][v.column] != 0){
                return true;
            }
        }
        else{
            if(board[v.row - 1][v.column] != 0){
                return true;
            }
        }
    }
    return false;
}

bool moveForward(Vehicle& v, int board[][MAX_ARR]){
    
    int set = board[v.row][v.column];
   // cout << "attempt to move " << set << " forward: " <<endl;
    if(isHorizontal(v)){
        if(isCar(v)){
            if(v.column + CAR < MAX_ARR){
                if(!isCollisionForward(v, board)){
                    board[v.row][v.column] = 0;
                    v.column++;
                    for(int i = 0; i < CAR; i++){
                        board[v.row][v.column + i] = set;
                    }
                    return true;
                }
            }
        }
        else{
            if(v.column + TRUCK < MAX_ARR){
                if(!isCollisionForward(v, board)){
                    board[v.row][v.column] = 0;
                    v.column++;
                    for(int i = 0; i < TRUCK; i++){
                        board[v.row][v.column + i] = set;
                    }
                    return true;
                }
            }
        }
    }
    else{
        if(isCar(v)){
            if(v.row + CAR < MAX_ARR){
                if(!isCollisionForward(v, board)){
                    board[v.row][v.column] = 0;
                    v.row++;
                    for(int i = 0; i < CAR; i++){
                        board[v.row + i][v.column] = set;
                    }
                    return true;
                }
            }
        }
        else{
            if(v.row + TRUCK < MAX_ARR){
                if(!isCollisionForward(v, board)){
                    board[v.row][v.column] = 0;
                    v.row++;
                    for(int i = 0; i < TRUCK; i++){
                        board[v.row + i][v.column] = set;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool moveBackward(Vehicle& v, int board[][MAX_ARR]){
    int set = board[v.row][v.column];
        //cout << "attempt to move " << set << " backward: "<<endl;
        if(isHorizontal(v)){
            if(isCar(v)){
                if(v.column - 1 >= 0){
                    if(!isCollisionBackward(v, board)){
                        board[v.row][v.column + 1] = 0;
                        v.column--;
                        for(int i = 0; i < CAR; i++){
                            board[v.row][v.column + i] = set;
                        }
                        return true;
                    }
                }
            }
            else{
                if(v.column - 1 >= 0){
                    if(!isCollisionBackward(v, board)){
                        board[v.row][v.column + 2] = 0;
                        v.column--;
                        for(int i = 0; i < TRUCK; i++){
                            board[v.row][v.column + i] = set;
                        }
                        return true;
                    }
                }
            }
        }
        else{
            if(isCar(v)){
                if(v.row - 1 >= 0){
                    if(!isCollisionBackward(v, board)){
                        board[v.row + 1][v.column] = 0;
                        v.row--;
                        for(int i = 0; i < CAR; i++){
                            board[v.row + i][v.column] = set;
                        }
                        return true;
                    }
                }
            }
            else{
                if(v.row - 1 >= 0){
                    if(!isCollisionBackward(v, board)){
                        board[v.row + 2][v.column] = 0;
                        v.row--;
                        for(int i = 0; i < TRUCK; i++){
                            board[v.row + i][v.column] = set;
                        }
                        return true;
                    }
                }
            }
        }
        return false;
}

bool isComplete(const Vehicle& v, const int board[][MAX_ARR]){
    if(isHorizontal(v)){
        if(isCar(v)){
            if(v.column + CAR == MAX_ARR)
                return true;
        }
        else{
            if(v.column + TRUCK == MAX_ARR){
                return true;
            }
        }
        return false;
    }
    else{
        if(isCar(v)){
            if(v.row + CAR == MAX_ARR)
                return true;
        }
        else{
            if(v.row + TRUCK == MAX_ARR){
                return true;
            }
        }
        return false;
    }
}

bool solve(int& numMoves, Vehicle cars[], int board[][MAX_ARR], int& best, const int& numCars, bool& result){
   // print(board);
    //usleep(microseconds);
    if(isComplete(cars[0], board)){
        
        if(numMoves <= best){
            result = true;
            best = numMoves;
            numMoves = 0;
            return true;
        }

        if(numMoves > best){
            numMoves = 0;
            return false;
        }

    }
    for(int i = 0; i < numCars; i++){
        if(moveForward(cars[i], board)){
            cout << "Car " << i + 1 << " has been moved forward"<<endl;
            numMoves += 1;
            result = solve(numMoves, cars, board, best, numCars, result);
            moveBackward(cars[i], board);
        }
    }
    for(int i =0; i< numCars; i++){
        if(moveBackward(cars[i], board)){
            cout << "Car " << i + 1 << " has been moved backwards" << endl;
            numMoves += 1;
            result = solve(numMoves, cars, board, best, numCars, result);
            moveForward(cars[i], board);
        }
    }
    return result;
   
}

