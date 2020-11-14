#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>

//YOUR CODE GOES HERE
using namespace std;

class MyException : public exception
{
  const char * what () const throw ()
  {
    return "Invalid Index!";
  }
};

template <typename T>
class LinkedList{
private:
    class Node{
    public:
        T data;
        Node *prev;
        Node *next;
        Node(const T & d):data(d), prev(NULL), next(NULL){}
        Node(const T & d, Node * preNode, Node * nextNode):data(d), prev(preNode), next(nextNode){}
    };

    Node *head;
    Node *tail;
    int sz;

public:
    LinkedList():head(NULL), tail(NULL), sz(0){}

    ~LinkedList(){
        while(head != NULL){
            Node *temp = head->next;
            delete head;
            head = temp;
        }
    }

    
    void addFront(const T &item){
        if(head == NULL){
            head = new Node(item, NULL, NULL);
            tail = head;
        }else{
            head = new Node(item, NULL, head);
            head -> next -> prev = head;
        }
        ++sz;
    }

    void addBack(const T &item){
        if(head == NULL){
            head = new Node(item, NULL, NULL);
            tail = head;
        }else{
            tail = new Node(item, tail, NULL);
            tail->prev->next = tail;
        }
        ++sz;
    }

    bool remove(const T &item){
        Node * cur = head;
        while(cur != NULL){
            if(cur->data == item){
                if(cur == head && cur == tail){
                    head = NULL;
                    tail = NULL;
                }else if (cur == head){
                    head = cur->next;
                    head->prev = NULL;
                }else if(cur == tail){
                    tail = cur->prev;
                    tail->next = NULL;
                }else{
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                }
                delete cur;
                --sz;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    const T& operator[](int index) const{
        if(index + 1 > sz){
            throw MyException();
        }else{
            Node *cur = head;
            for (int i = 0; i < index; i++){
                cur = cur->next;
            }
            return cur->data;
        }
    }

    T& operator[](int index){
        if(index + 1 > sz){
            throw MyException();
        }else{
            Node *cur = head;
            for (int i = 0; i < index; i++){
                cur = cur->next;
            }
            return cur->data;
        }
    }

    int find(const T &item){
        Node *cur = head;
        int index = 0;
        while(cur != NULL){
            if(cur->data == item){
                return index;
            }
            ++index;
            cur = cur->next;
        }
        return -1;
    }

    LinkedList(const LinkedList & rhs):head(NULL), tail(NULL), sz(rhs.sz){
        Node *cur = rhs.head;
        while(cur != NULL){
            addBack(cur->data);
            cur = cur->next;
        }
    }

    LinkedList & operator = (const LinkedList & rhs){
        if(this != &rhs){
            Node *cur = rhs.head;
            Node * temp = new Node(cur->data);
            Node *dummyHead = temp;
            cur = cur->next;
            while(cur != NULL){
                temp->next = new Node(cur->data);
                temp->next->prev = temp;
                temp=temp->next;
                cur = cur->next;
            }
            while(head != NULL){
                Node *temp = head->next;
                delete head;
                head = temp;
            }
            head = dummyHead;
            tail = temp;
            sz = rhs.sz;
            }else{
                return *this;
            }
    }

    int getSize(){
        return sz;
    }
};



#endif
