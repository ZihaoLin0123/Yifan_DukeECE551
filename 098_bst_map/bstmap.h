#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template<typename K, typename V>
class BstMap:public Map<K, V> {
private:
    class Node{
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        Node(const K & k, const V & v):key(k), value(v), left(NULL), right(NULL){}
    };
    Node *root;

public:
    BstMap():root(NULL){}
 BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }
   
 Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }
   BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  

    virtual void add(const K & key, const V & value){
        root = add(root, key, value);
    }
    Node * add(Node * cur, const K & key, const V & value){
        if (cur == NULL){
            Node *ans = new Node(key, value);
            return ans;
        }
        if(key < cur->key){
            cur->left = add(cur->left, key, value);
        }else if (key > cur->key){
            cur->right = add(cur->right, key, value);
        }else{
            cur->value = value;
        }
        return cur;
    }
    virtual const V & lookup(const K& key) const throw (std::invalid_argument){
        Node *cur = root;
        while(cur != NULL){
            if(key == cur->key){
                return cur->value;
            }else if(key < cur->key){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        throw std::invalid_argument("error");
    }
    virtual void remove(const K & key) {
    Node ** current = &root;
    Node * temp = NULL;
    //find key
    while (*current != NULL) {
      //current Node needs to be removed
      if ((*current)->key == key) {
        //one node or zero node
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        else {
          //go left once
          Node ** toReplace = current;
          current = &((*current)->left);
          //follow right
          while ((*current)->right != NULL) {
            current = &((*current)->right);
          }
          (*toReplace)->key = (*current)->key;
          const V value = (*current)->value;
          temp = (*current)->left;
          delete *current;
          *current = temp;
          add((*toReplace)->key, value);
        }
      }
      else if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
  }

   

    void destroy(Node * node){
        if(node != NULL){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    virtual ~BstMap<K,V>() {
        destroy(root);
        root = NULL;
    }

    void in(){
        inOrderTraverse(root);
    }
    void inOrderTraverse(Node * node){
        if(node != NULL){
            inOrderTraverse(node->left);
            cout << node->key << endl;
            inOrderTraverse(node->right);
        }
    }
};