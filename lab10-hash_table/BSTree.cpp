/** @file BStree.cpp
 @author Aaron Mcanerney
@version Revision 1.0
@breif templated binary search tree implemenation
@details templated binary search tree implementation.
Functionality as specified by c++ lab book.
@date 10/15/2017
**/

#include "BSTree.h"


/**
*BStreeNode         Binary search tree node constructor 
*
*@param nodeDataItem    generic data item to be stored in the node
*
*@param leftPtr     pointer to the left child of the node
*
*@param rightPtr    pointer to the right child of the node 
*
*@pre   uninitialized Binary search tree node 
*
*@post  new binary search tree node
*
**/
template<class T, class Key>
BSTree<T,Key>::BSTreeNode::BSTreeNode ( const T &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ){
   dataItem = nodeDataItem;
   left = leftPtr;
   right = rightPtr; 
}

/**
*BStree     Binary search tree empty constructor 
*
*@pre   empty binary search tree 
*
*@post  binary search tree with root set to NULL
*
**/
template<class T, class Key>
BSTree<T, Key>::BSTree(){
    root = NULL;
}

/**
*Bstree     Binary search tree copy constructor
*
*@param other   binary search tree to copy from 
*
*@pre   uninitialized binary search tree 
*
*@post  binary search tree that is initialized as a deep copy of other
*
**/
template<class T, class Key>
BSTree<T,Key>::BSTree(const BSTree<T,Key>& other){
    root = NULL;
    copyHelper(root, other);
}

/**
*operator=  overloaded assignment operator
*
*@return returns the address of (this) binary search tree
*
*@param other   const binary search tree to copy from 
*
*@pre a binary search tree (initialized or unitialized)
*
*@post  a binary search tree that is a deep copy of other
*
**/
template<class T, class Key>
BSTree<T, Key>& BSTree<T,Key>::operator=(const BSTree<T,Key>& other){
    if(this == &other){
        return *this;
    }
    clear();
    copyHelper(root, other);
    return *this;
}

/**
*copyHelper recursive helper function for operator equals and copy constructor. Uses preorder traversal.
*
*@return    void 
*
*@param     other   binary search tree node to copy from 
*
*@param     node    binary search tree node passed by reference
*
*@pre       a binary search tree with n - 1 nodes 
*
*@post      a binary search tree with n nodes. The new node is a copy of other.
*
**/
template<class T, class Key>
void BSTree<T, Key>::copyHelper(BSTreeNode*& node, BSTreeNode* other){
    if(other != NULL){
        node = new BSTreeNode(other->dataItem, NULL, NULL);
        copyHelper(node->left, other->left);
        copyHelper(node->right, other->right);
    }
}

/**
*~BStree    destructor 
*
*@pre   a (potentially) non - empty binary search tree
*
*@post  a binary search tree with a NULL root
*
**/
template<class T, class Key>
BSTree<T, Key>::~BSTree(){
    clear();
}

/**
*insert     inserts a new node into the BST
*
*@return void
*
*@param newData     data for the new node
*
*@pre   a binary search tree with n -1 nodes. 
*
*@post  a binary search tree with n nodes (inserts new node)
*
**/
template<class T, class Key>
void BSTree<T, Key>::insert(const T& newData){
    insertHelper(root, newData);
}

/**
*insertHelper   recursive helper function for insert.
*
*@return    void 
*
*@param node    node passed by pointer reference (will be passed or attached to)
*
*@param data    data for the new node
*
*@pre   binary search tree with n - 1 nodes 
*
*@post  binary search tree with a  new node (satisfies the binary search tree property)
*
**/
template<class T, class Key>
void BSTree<T, Key>::insertHelper(BSTreeNode*& node, const T& data){
  if(node == NULL){
      node = new BSTreeNode(data, NULL, NULL);
  }
  else if(node->dataItem.getKey() > data.getKey()){
      insertHelper(node->left, data);
  }
  else if(node->dataItem.getKey() < data.getKey()){
      insertHelper(node->right, data);
  }
}

/**
*retrieve retrieves the data item with a specified key
*
*@return bool   true if the key exists, false otherwise
*
*@param key     key of the data item in the tree 
*
*@param data    passed by reference (will hold the data if found)
*
*@pre   unfilled generic data type
*
*@post  generic data type that will contain the retrieved data if found
*
**/
template<class T, class Key>
bool BSTree<T,Key>::retrieve(const Key& key, T& data) const{
    return retrieveHelper(root, key, data);
}

/**
*retrieveHelper recursive helper for retreive. Uses pre order traversal
*
*@return    bool    returns true if the data item was found 
*
*@param node    node pointer to the current node in the tree 
*
*@param data    conatainer for potenital value
*
*@param key     key for comparison of values within the tree
*
*@pre   unfilled dataItem 
*
*@post  generic data type containing the value associated with the key
*
**/
template<class T, class Key>
bool BSTree<T, Key>::retrieveHelper(BSTreeNode* node, const Key& key, T& data) const{
    if(node != NULL){
        if(node->dataItem.getKey() == key){
            data = node->dataItem;
            return true;
        }
        if(node->dataItem.getKey() > key){
            return retrieveHelper(node->left, key, data);
        }
        return retrieveHelper(node->right, key, data);
    }
    return false;
}

/**
*remove
*
*@return    bool    returns true if a node with the specified key was removed
*
*@param key key of the item to be removed  
*
*@pre   a tree with n + 1 items 
*
*@post  a tree with the key specified removed
*
**/
template<class T, class Key>
bool BSTree<T, Key>::remove(const Key& key){
    removeHelper(root, key);
}

/**
*removeHelper   uses pre order traversal and logic to remove a node from the tree
*
*@return    bool    returns true if the key was found and the node was removed 
*
*@param node    node pointer to the current node in the tree 
*
*@param key key of the data item to be removed 
*
*@pre   tree with n + 1 nodes 
*
*@post  tree with n nodes. Node with the key has been removed
*
**/
template<class T, class Key>
bool BSTree<T, Key>::removeHelper(BSTreeNode*& node, const Key& key){
    if(node != NULL){
        if(node->dataItem.getKey() == key){
            //no children
            if(node->left == NULL && node->right == NULL){
                delete node;
                node = NULL;
                return true;
            }
            //node has only right child
            else if(node->left == NULL && node->right != NULL){
                BSTreeNode* temp = node;
                node = node->right;
                delete temp;                
                return true;
            }
            //node has only left child
            else if(node->left != NULL && node->right == NULL){
                BSTreeNode* temp = node;
                node = node->left;
                delete temp; 
                return true;
            }
            //two children family - potentially considering a third...
            else{
                BSTreeNode* temp = node->left;
                while(temp->right != NULL){
                    temp = temp->right;
                }
                node->dataItem.setKey(temp->dataItem.getKey());
                return removeHelper(node->left, temp->dataItem.getKey());
            }
        }
        if(node->dataItem.getKey() > key){
            return removeHelper(node->left,key);
        }
        if(node->dataItem.getKey() < key){
            return removeHelper(node->right, key);
        }
    }
    return false;
}


/**
*writeKeys  writes the keys to console in ascending order
*
*@return    void 
*
*@pre binary search tree
*
*@post  contents of binary search tree are written to console
*
**/
template<class T, class Key>
void BSTree<T,Key>::writeKeys() const {
    writeKeyHelper(root);
    cout << endl;
}

/**
*writeKeyHelper     recursive helper function. uses in order traversal to print the keys.
*
*@return    void 
*
*@param node    current node in the tree whos data will be printed. 
*
*@pre   binary search tree 
*
*@post  one element of the binary search tree node will be printed to console
*
**/
template<class T, class Key>
void BSTree<T,Key>::writeKeyHelper(BSTreeNode* node) const {
    if(node != NULL){
        writeKeyHelper(node->left);
        cout << node->dataItem.getKey()<< " ";
        writeKeyHelper(node->right);
    }
}

/**
*clear  clears the contents of the BST
*
*@return    void 
*
*@pre   binary search with data in it 
*
*@post  empty binary search tree
*
**/
template<class T, class Key>
void BSTree<T, Key>::clear(){
    clearHelper(root);
    root = NULL;    //might be redundant
}

/**
*clearHelper    recursive helper funtion that uses a post order traversal to delete nodes.
*
*@return void 
*
*@param node    node passed by pointer reference to the current node in the tree 
*
*@pre   a binary seawrch tree with n + 1 nodes 
*
*@post  a binary search tree with n nodes (current will have been deleted)
*
**/
template<class T, class Key>
void BSTree<T, Key>::clearHelper(BSTreeNode*& node){
    if(node != NULL){
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = NULL;
    }
}

/**
*isEmpty    checks whether or not the tree is empty
*
*@return    bool    returns true if the tree is empty 
*
*@pre   a binary search tree 
*
*@post  returns true if empty
*
**/
template<class T, class Key>
bool BSTree<T,Key>::isEmpty() const {
    return root == NULL;
}

/**
*showStructure  factory print method (provided)
*
*@return    void 
*
*@pre   binary search tree 
*
*@post  binary search tree has been printed to console
*
**/
template<class T, class Key>
void BSTree<T, Key>::showStructure() const {
    if ( root == 0 )
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}

/**
*showHelper recursive helper that prints the tree to console
*
*@return    void 
*
*@param p   binary search tree node (current)  node in the tree
*
*@param level   level of the tree used to tab children node 
*
*@pre   binary search tree node 
*
*@post  one node of the tree printed to console
*
**/
template<class T, class Key>
void BSTree<T, Key>::showHelper(BSTreeNode *p, int level) const {
    int j;   // Loop counter
    
         if ( p != 0 )
         {
            showHelper(p->right,level+1);         // Output right subtree
            for ( j = 0 ; j < level ; j++ )    // Tab over to level
                cout << "\t";
            cout << " " << p->dataItem.getKey();   // Output key
            if ( ( p->left != 0 ) &&           // Output "connector"
                 ( p->right != 0 ) )
               cout << "<";
            else if ( p->right != 0 )
               cout << "/";
            else if ( p->left != 0 )
               cout << "\\";
            cout << endl;
            showHelper(p->left,level+1);          // Output left subtree
        }
}

/**
*getHeight  returns the height of the tree
*
*@return    int     the (max) height of the tree 
*
*@pre   a binary search tree 
*
*@post  the height of binary search tree is returned
*
**/
template<class T, class Key>
int BSTree<T, Key>::getHeight() const {
   return getHeightHelper(root) - 1 ;
}

/**
*getHeightHelper    recursive helper function that returns the hieght of the tree
*
*@return    int     height of the tree 
*
*@param node    current node in the tree 
*
*@pre   binary search tree node 
*
*@post  count incremented by one if the node was not NULL
*
**/
template<class T, class Key>
int BSTree<T, Key>::getHeightHelper(BSTreeNode* node)const {
    if(node != NULL){
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
    }
    else{
        return 1;
    }
}

/**
*max    returns the max between the two parameteres
*
*@return    int     max between i and j 
*
*@param i int to be compared 
*
*@param j int to be compared 
*
*@pre   two numbers with unkown max 
*
*@post  max of i and j
*
**/
template<class T, class Key>
int BSTree<T, Key>::max(int i, int j) const {
    if(i > j) {
        return i;
    }
    return j;
}

/**
*getCount   returns the number of nodes in the tree.
*
*@return    int     number of nodes in the tree 
*
*@pre   binary search tree with n nodes 
*
*@post  the number of nodes in the tree
*
**/
template<class T, class Key>
int BSTree<T, Key>::getCount() const {
    return getCountHelper(root) - 1;
}

/**
*getCountHelper recursive helper function that returns the count of nodes in the tree.
*
*@return    int number of nodes in the tree 
*
*@param     node    node pointer to the current node 
*
*@pre   a node in the binary search tree 
*
*@post  an incremented count if the node found is not null
*
**/
template<class T, class Key>
int BSTree<T, Key>::getCountHelper(BSTreeNode* node) const{
    if(node != NULL){
        return getCountHelper(node->left) + getCountHelper(node->right);
    }
    else{
        return 1;
    }
}

/**
*writeLessThan  writes the keys less than (key) to console
*
*@return    void 
*
*@param     key  key to be compared to  
*
*@pre   a binary search tree 
*
*@post  all data less than key k printed to console
*
**/
template<class T, class Key>
void BSTree<T, Key>::writeLessThan(const Key& key) const {
    writeLessThanHelper(root, key);
}

/**
*writeLessThanHeper recursive helper function that prints nodes with key < k to console
*
*@return void 
*
*@param node    pointer to current node in the tree 
*
*@param key     key used for comparison 
*
*@pre   binary search tree 
*
*@post  data less than key printed to console
*
**/
template<class T, class Key>
void BSTree<T, Key>::writeLessThanHelper(BSTreeNode* node, const Key& key) const{
    if(node != NULL){
        if(node->dataItem.getKey() < key){
            writeLessThanHelper(node->left, key);
            cout << node->dataItem.getKey() <<" ";
            writeLessThanHelper(node->right, key);
        }
        else{
            writeLessThanHelper(node->left, key);
        }
    }
}

