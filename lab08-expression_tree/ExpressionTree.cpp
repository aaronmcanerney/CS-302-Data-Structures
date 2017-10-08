#include "ExpressionTree.h"

ExprTree::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr){
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}


ExprTree::ExprTree(){
    root = NULL;
}

ExprTree::ExprTree(const ExprTree& source){
    
}

ExprTree& ExprTree::operator=(const ExprTree& source){
    return *this;
}

ExprTree::~ExprTree(){

}

void ExprTree::build(){


}

void ExprTree::expression() const{

}

double ExprTree::evaluate() const throw (logic_error){
    return 1.0;
}

void ExprTree::clear(){

}

void ExprTree::commute() {

}

bool ExprTree::isEquivalent(const ExprTree& source) const {
    return false;
}

void ExprTree::showStructure() const {


}

void ExprTree::insert(const int data){
    ExprTreeNode* node = new ExprTreeNode(data, NULL, NULL);
    if(root == NULL){
        root = node;
    }
    else{
    }
}