/** @file ExpressionTree.cpp
 @author Aaron Mcanerney
@version Revision 1.0
@breif solves prefix notation equations
@details uses a tree structure as a container and helper functions to
evaluate algebraic expressions
@date 10/10/2017
**/

#include "ExpressionTree.h"

//char array of operators
const char OPERATOR[4] = {'+', '/', '*', '-'};


/**
*ExprTreeNode creates a new node for the tree. Checks for operator or number
*
*@return constructor
*
*@param elem    a new element (dataItem)
*
*@param leftPtr pointer to the left child
*
*@param rightPtr pointer to the right child 
*
*@pre uninitialized node
*
*@post  initialized node with data and pointers 
*
**/
template<class T>
ExprTree<T>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr){
    bool flag;
    //cout << "Elem: " << elem << endl;
    for(int i = 0; i < 4; i++){
        if(OPERATOR[i] == elem){
            flag = true;
        }
    }
    if(flag){
      //  cout << "Operator"<<endl;
        dataItem = elem;
    }
    else{
        dataItem = elem - '\0';
    }
    left = leftPtr;
    right = rightPtr;
}

/**
*ExprTree empty constructor
*
*@return    constructor
*
*@pre unititialized tree
*
*@post new expression tree
*
**/
template<class T>
ExprTree<T>::ExprTree(){
    root = NULL;
}



/**
*ExprTree copy constructor
*
*@return    constructor
*
*@param source  an expression tree to be copied from
*
*@pre unititialized tree
*
*@post new expression tree
*
**/
template<class T>
ExprTree<T>::ExprTree(const ExprTree<T>& source){
    root = NULL;
    ExprTreeNode* temp = source.root;
    insertHelper(root, temp);
}

/**
*operator=  overloaded assignment operator
*
*@return    reference to a new expression tree
*
*@param source  an expression tree to be copied from
*
*@pre unititialized tree
*
*@post new expression tree
*
**/
template<class T>
ExprTree<T>& ExprTree<T>::operator=(const ExprTree<T>& source){
    if(*this == &source){
        return *this;
    }
    clear();
    root = NULL;
    ExprTreeNode* temp = source.root;
    insertHelper(root, temp);
    return *this;
}

/**
*insertHelper   inserts a new node into the tree
*
*@return    void
*
*@param node    node from this tree
*
*@param otherNode    node from otherTree tree
*
*@pre a tree with n-1 nodes
*
*@post  a tree with n nodes (if the node passed in was not null)
*
**/
template<typename T>
void ExprTree<T>::insertHelper(ExprTreeNode*& node, ExprTreeNode*& otherNode){
    if(otherNode != NULL){
        node = new ExprTreeNode(otherNode->dataItem, NULL,NULL);
        insertHelper(node->left, otherNode->left);
        insertHelper(node->right, otherNode->right);
   }
}

/**
*~ExprTree destructor for memory deallocation
*
*@return    destructor
*
*@pre   a tree
*
*@post a completely deleted tree
*
**/
template<class T>
ExprTree<T>::~ExprTree(){
    clear();
}


/**
*build builds a new expression tree
*
*@return    void
*
*@param source  an expression tree to be copied from
*
*@pre empty tree
*
*@post new expression tree with data
*
**/
template<class T>
void ExprTree<T>::build(){
    buildHelper(root);
}


/**
*buildHelper build helper function
*
*@return    void
*
*@param node    a node to be assigned and recursed on
*
*@pre   a tree with n-1 nodes
*
*@post a tree with n nodes
*
**/
template<typename T>
void ExprTree<T>::buildHelper(ExprTreeNode* &node){
    char c;
    cin >> c;
    node = new ExprTreeNode(c, NULL, NULL);
    if(isOperator(c)){
        buildHelper(node->left);
        buildHelper(node->right);
    }
}


/**
*expression prints the expression to terminal
*
*@return    void
*
*@pre expression tree
*
*@post contents of the expression tree printed to terminal
*
**/
template<class T>
void ExprTree<T>::expression() const{
    ExprTreeNode* node = root;
    expressHelper(node);
}


/**
*evaluate   evaluates the expression in the expression tree
*
*@return    data of type T
*
*@pre an expression tree
*
*@throws throws logic error if called on empty tree
*
*@post the evaluated Type T of the expression tree
*
**/
template<class T>
T ExprTree<T>::evaluate() const throw (logic_error){
    if(!isEmpty()){
        return evaluateHelper(root);
    }
    else{
        throw logic_error("evaluate() Tree Empty");
    }
}

/**
*evaluateHelper evaluates the expression in the tree
*
*@return    data of type T
*
*@param an expression tree node
*
*@pre a tree, subtree, or node in the expression tree
*
*@post an evaluation of the expression tree, subtree, or the return of a node
*
**/
template<class T>
T ExprTree<T>::evaluateHelper(ExprTreeNode* node) const{
    if(node != NULL){
        if(isOperator(node->dataItem)){
            if(node->dataItem == '*'){
                return evaluateHelper(node->left) * evaluateHelper(node->right);
            }
            else if(node->dataItem == '/'){
                return evaluateHelper(node->left) / evaluateHelper(node->right);
            }
            else if(node->dataItem == '+'){
                return evaluateHelper(node->left) + evaluateHelper(node->right);

            }
            else{
                return evaluateHelper(node->left) - evaluateHelper(node->right);
            }
        }
        else{
            //cout << node->dataItem;
            return node->dataItem - '0';
        }
    }
}


/**
*clear  deallocates memory from the tree
*
*@return    void
*
*@pre an expression tree
*
*@post deallocated treed
*
**/
template<class T>
void ExprTree<T>::clear(){
    clearHelper(root);
    root = NULL;
}


/**
*clearHelper  deallocates memory from the tree
*
*@return    void
*
*@param     node 
*
*@pre an expression tree
*
*@post deallocated tree
*
**/
template<class T>
void ExprTree<T>::clearHelper(ExprTreeNode* node){
    if(node != NULL){
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = NULL;
    }
}


/**
*commute  swaps subtrees and the data in the subtrees
*
*@return    void
*
*@pre an expression tree
*
*@post a commuted expression tree
*
**/
template<class T>
void ExprTree<T>::commute() {
    commuteHelper(root);
}


/**
*commuteHelper   swaps subtrees and the data in the subtrees
*
*@return    void
*
*@param node    a node to comute and recurse on
*
*@pre an expression tree
*
*@post an expression tree with subtrees swapped as well as children
*
**/
template<class T>
void ExprTree<T>::commuteHelper(ExprTreeNode* node){
    if(node != NULL){
        commuteHelper(node->left);
        commuteHelper(node->right);
        ExprTreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}


/**
*isEquivalent   determines if two subtrees are equivalent
*
*@return    bool
*
*@param source another tree to be tested for equivalence
*
*@pre two possibly exquivalent expression trees
*
*@post if tree one equals tree two
*
**/
template<class T>
bool ExprTree<T>::isEquivalent(const ExprTree& source) const {
    if(evaluateHelper(root) != evaluateHelper(source.root)){
        return false;
    }
    return equalHelper(root, source.root);
}



/**
*equalHelper    checks if both the tree and the commuted tree are equivalent
*
*@return    bool
*
*@param node    the node to be tested for equivalence
*
*@param other   the other node to be tested for equivalence
*
*@pre two potentially equivalent nodes
*
*@post if node one equals node two
*
**/
template<class T>
bool ExprTree<T>::equalHelper(ExprTreeNode* node, ExprTreeNode* other) const{
    if(node != NULL && other != NULL){
        if(node->dataItem == other->dataItem){
            return (equalHelper(node->left, other->left) && equalHelper(node->right, other->right)) || 
            (equalHelper(node->left, other->right) && equalHelper(node->right, other->left));
        }
        else{
            return false;
        }
    }
    return node == NULL && other == NULL;
}


/**
*showStructure   prints the tree to terminal
*
*@return    void
*
*@pre an expression tree
*
*@post an expression tree printed to terminal
*
**/
template<class T>
void ExprTree<T>::showStructure() const {
        if ( isEmpty() )
           cout << "Empty tree" << endl;
        else
        {
           cout << endl;
           showHelper(root,1);
           cout << endl;
        }
}



/**
*showHelper  prints the expression tree to terminal
*
*@return    void
*
*@param p a pointer to a node
*
*@param level the level of the tree (indicates tab)
*
*@pre an expression tree
*
*@post an expression tree printed to terminal
*
**/
template<class T>
void ExprTree<T>::showHelper(ExprTreeNode* p, int level) const {
    
    int j;   // Loop counter
    
         if ( p != NULL )
         {
            showHelper(p->right,level+1);        // Output right subtree
            for ( j = 0 ; j < level ; j++ )   // Tab over to level
                cout << "\t";
            cout << " " << p->dataItem;        // Output dataItem
            if ( ( p->left != 0 ) &&          // Output "connector"
                 ( p->right != 0 ) )
               cout << "<";
            else if ( p->right != 0 )
               cout << "/";
            else if ( p->left != 0 )
               cout << "\\";
            cout << endl;
            showHelper(p->left,level+1);         // Output left subtree
         }
}



/**
*isEmpty   returns whether or not the tree is empty
*
*@return    bool
*
*@pre an expression tree
*
*@post an empty or non empty expression tree
*
**/
template<class T>
bool ExprTree<T>::isEmpty() const{
    return root == NULL;
}



/**
*isOperator   determines whether the dataitem is an operator
*
*@return    bool
*
*@param c   a character to be checked
*
*@pre a character c
*
*@post  whether or not the dataitem is an operator
*
**/
template<class T>
bool ExprTree<T>::isOperator(char& c) const{
    for(int i = 0 ; i < 4; i++){
        if(OPERATOR[i] == c){
            return true;
        }
    }
    return false;
}


/**
*expressHelper   prints the expression to terminal
*
*@return    void
*
*@pre an expression tree
*
*@post an expression tree printed to terminal
*
**/
template<class T>
void ExprTree<T>::expressHelper(ExprTreeNode* node) const{
    if(node != NULL){
        bool flag = isOperator(node->dataItem);
        if(flag){
            cout << "(";
        }
        expressHelper(node->left);
        cout << node->dataItem;
        expressHelper(node->right);
        if(flag){
            cout << ")";
        }
    }
    
}


