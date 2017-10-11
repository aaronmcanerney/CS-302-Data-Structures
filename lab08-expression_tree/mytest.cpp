#include <iostream>
#include <stdexcept>

using namespace std;

//#include "ExprTree.cpp"
#include "ExpressionTree.cpp"
#include "config.h"

//--------------------------------------------------------------------
//  Function prototype // copyTree is passed by value

//--------------------------------------------------------------------

int main()
{
    ExprTree<float> testExpression;  // Test expression
    
        cout << endl << "Enter an expression in prefix form : ";
    
        testExpression.build();
        testExpression.showStructure();

    return 0;
}