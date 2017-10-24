#include "BSTree.h"
template<class T, class Key>
BSTree<T,Key>::BSTreeNode::BSTreeNode ( const T &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ){
   dataItem = nodeDataItem;
   left = leftPtr;
   right = rightPtr; 
}

template<class T, class Key>
BSTree<T, Key>::BSTree(){
    root = NULL;
}

template<class T, class Key>
BSTree<T,Key>::BSTree(const BSTree<T,Key>& other){
    root = NULL;
    copyHelper(root, other);
}

template<class T, class Key>
BSTree<T, Key>& BSTree<T,Key>::operator=(const BSTree<T,Key>& other){
    if(this == &other){
        return *this;
    }
    clear();
    copyHelper(root, other);
    return *this;
}

template<class T, class Key>
void BSTree<T, Key>::copyHelper(BSTreeNode*& node, BSTreeNode* other){
    if(other != NULL){
        node = new BSTreeNode(other->dataItem, NULL, NULL);
        copyHelper(node->left, other->left);
        copyHelper(node->right, other->right);
    }
}

template<class T, class Key>
BSTree<T, Key>::~BSTree(){
    clear();
}


template<class T, class Key>
void BSTree<T, Key>::insert(const T& newData){
    insertHelper(root, newData);
}

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

template<class T, class Key>
bool BSTree<T,Key>::retrieve(const Key& key, T& data) const{
    return retrieveHelper(root, key, data);
}

template<class T, class Key>
bool BSTree<T, Key>::retrieveHelper(BSTreeNode* node, const Key& key, T& data) const{
    if(node != NULL){
        if(node->dataItem.getKey() == key){
            data = node->dataItem;
            return true;
        }
        return retrieveHelper(node->left, key, data) || retrieveHelper(node->right, key, data);
    }
    return false;
}

template<class T, class Key>
bool BSTree<T, Key>::remove(const Key& key){
    removeHelper(root, key);
}




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
                node->dataItem.setKey(node->right->dataItem.getKey());
                BSTreeNode* temp = node->right;
                node->right = NULL;
                delete temp;
                return true;
            }
            //node has only left child
            else if(node->left != NULL && node->right == NULL){
                node->dataItem.setKey(node->left->dataItem.getKey());
                BSTreeNode* temp = node->left;
                node->left = NULL;
                delete temp;
                return true;
            }
            //two children family - potentially considering a third...
            else{
                BSTreeNode* temp = node->left;
                BSTreeNode* tracer = node->left;
                //one step case
                if(temp->right == NULL){
                    node->dataItem.setKey(temp->dataItem.getKey());
                    node->left = NULL;
                    delete temp;
                    return true;
                }
                //tracer will be one step ahead of temp
                tracer = tracer->right;
                while(tracer->right != NULL){
                    temp = temp->right;
                    tracer = tracer->right;
                }
                node->dataItem.setKey(tracer->dataItem.getKey());
                temp->right = NULL;
                delete tracer;
                return true;
            }
        }
        else{
            return removeHelper(node->left, key) || removeHelper(node->right, key);
        }
    }
    return false;
}


template<class T, class Key>
void BSTree<T,Key>::writeKeys() const {
    writeKeyHelper(root);
    //cout << endl;
}

template<class T, class Key>
void BSTree<T,Key>::writeKeyHelper(BSTreeNode* node) const {
    if(node != NULL){
        writeKeyHelper(node->left);
        cout << node->dataItem.getKey()<< " ";
        writeKeyHelper(node->right);
    }
}

template<class T, class Key>
void BSTree<T, Key>::clear(){
    clearHelper(root);
    root = NULL;    //might be redundant
}

template<class T, class Key>
void BSTree<T, Key>::clearHelper(BSTreeNode*& node){
    if(node != NULL){
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = NULL;
    }
}

template<class T, class Key>
bool BSTree<T,Key>::isEmpty() const {
    return root == NULL;
}

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

template<class T, class Key>
int BSTree<T, Key>::getHeight() const {
   return getHeightHelper(root) - 1 ;
}


template<class T, class Key>
int BSTree<T, Key>::getHeightHelper(BSTreeNode* node)const {
    if(node != NULL){
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
    }
    else{
        return 1;
    }
}

template<class T, class Key>
int BSTree<T, Key>::max(int i, int j) const {
    if(i > j) {
        return i;
    }
    return j;
}


template<class T, class Key>
int BSTree<T, Key>::getCount() const {
    return getCountHelper(root) - 1;
}

template<class T, class Key>
int BSTree<T, Key>::getCountHelper(BSTreeNode* node) const{
    if(node != NULL){
        return getCountHelper(node->left) + getCountHelper(node->right);
    }
    else{
        return 1;
    }
}
template<class T, class Key>
void BSTree<T, Key>::writeLessThan(const Key& key) const {
    writeLessThanHelper(root, key);
}

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

