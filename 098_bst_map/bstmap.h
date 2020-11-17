#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template<typename K, typename V>
class BstMap:public Map<K, V> {
private:
    class Node{
    public:
        pair<K, V> data;
        Node *left;
        Node *right;
        Node(pair<K, V> & d):data(d), left(NULL), right(NULL){}
    };
    Node *head;

public:
    BstMap():head(NULL){}
     BstMap(const BstMap & rhs) : head(NULL) { head = copy(rhs.head); }
    Node * copy(Node * node){
        if(node == NULL){
            return NULL;
        }
        Node *root = new Node(node->data);
        root ->left = copy(node->left);
        root->right = copy(node->right);
        return root;
    }

    virtual void add(const K & key, const V & value){
        pair<K, V> temp(key, value);
        head = add(head, temp);
    }
    Node * add(Node * cur, pair<K, V> & data){
        if (cur == NULL){
            return new Node(data);
        }
        if(data.first < cur->data.first){
            cur->left = add(cur->left, data);
        }else if (data.first > cur->data.first){
            cur->right = add(cur->right, data);
        }else{
            cur->data.second = data.second;
        }
        return cur;
    }
    virtual const V & lookup(const K& key) const throw (std::invalid_argument){
        Node *cur = head;
        while(cur != NULL){
            if(key == cur->data.first){
                return cur->data.second;
            }else if(key < cur->data.first){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        throw std::invalid_argument("error");
    }
    virtual void remove(const K& key){
        if(head == NULL){
        return;
        }
        if(key == head->data.first){
            head = remove(head);
            return;
        }
        Node *cur = head;
        while(cur != NULL){
            if(key < cur->data.first){
                if(cur->left == NULL){
                    return;
                }else if(key == cur->left->data.first){
                    cur->left = remove(cur->left);
                    return;
                }else{
                    cur = cur->left;
                }
            }else if(key > cur->data.first){
                if(cur->right == NULL){
                    return;
                }else if(key == cur->right->data.first){
                    cur->right = remove(cur->right);
                    //cout << "find" >> endl;
                    return;
                }else{
                    cur = cur->right;
                }
            }
        }
    }

    Node * remove(Node * target){
        //cout << "remove node" << target->data.first << endl;
        if(target->left == NULL){
            Node * temp = target->right;
            delete target;
            return temp;
        }else if(target->right == NULL){
            Node * temp = target->left;
            delete target;
            return temp;
        }else{
            Node *temp = target->right;
            if(temp->left == NULL){
                target->data = temp->data;
                delete temp;
                target->right = NULL;
                return target;
            }else{
                while(temp->left->left != NULL){
                    temp = temp->left;
                    
                }
                target->data = temp->left->data;
              
                delete temp->left;
                temp->left = NULL;
                return target;
            }
        }
    }

   

    void destory(Node * node){
        if(node != NULL){
            destory(node->left);
            destory(node->right);
            delete node;
        }
    }
    virtual ~BstMap<K,V>() {
        destory(head);
    }

    void pre(){
        preOrderTraverse(head);
    }
    void preOrderTraverse(Node * node){
        if(node != NULL){
            cout << node->data.first << endl;
            preOrderTraverse(node->left);
            preOrderTraverse(node->right);
        }
    }
};