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
}

template<class T, class Key>
BSTree<T, Key>& BSTree<T,Key>::operator=(const BSTree<T,Key>& other){

}

template<class T, class Key>
BSTree<T, Key>::~BSTree(){

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
  else if(node->dataItem > data){
      insertHelper(node->left, data);
  }
  else if(node->dataItem < data){
      insertHelper(node->right, data);
  }
}

template<class T, class Key>
bool BSTree<T,Key>::retrieve(const Key& key, T& data) const{

}

template<class T, class Key>
bool BSTree<T, Key>::remove(const Key& key){

}

template<class T, class Key>
void BSTree<T,Key>::writeKeys() const {

}

template<class T, class Key>
void BSTree<T, Key>::clear(){

}

template<class T, class Key>
bool BSTree<T,Key>::isEmpty() const {

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

}

template<class T, class Key>
int BSTree<T, Key>::getCount() const {

}

template<class T, class Key>
void BSTree<T, Key>::writeLessThan(const Key& key) const {

}

