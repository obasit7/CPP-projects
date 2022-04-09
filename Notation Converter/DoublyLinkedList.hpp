#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>
template <typename T>
class DLL;

//template for class
template <typename T> 
class Node{
    private:
        T c;
        Node<T>* next;
        Node<T>* prev;
    friend class DLL<T>; //shares information with DLL
};

template <typename T>
class DLL{
    private:
    //pointers to first and last node in double linked list
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        DLL(){size=0; head=nullptr;tail=nullptr;} //constructor
        int get_size() const{return size;} //returns size of array
        bool is_empty() const{return size==0;} //checks if list is empty
        Node<T>* get_head()const{return head;} //returns front node
        Node<T>* get_tail()const{return tail;} //returns last node in list

        //adds to front of DLL
        void addFront(char ch){ 
            Node<T>* insert = new Node<T>();
            insert->c=ch;
            if(get_size()==0){
                head=insert;
                tail=insert; 
            }
            else{                
                insert->next=head;
                head->prev=insert;
                head=insert;
            }
            size++;
        }
        //adds to end of DLL
        void addBack(T ch){ //adds to end of DLL
            Node<T>* insert = new Node<T>();
            insert->c=ch;
            if(get_size()==0){
                head=insert;
                tail=insert; 
            }
            else{
                tail->next=insert;
                insert->prev=tail;
                tail=insert;
            }
            size++;
        }

        //removes front node and sets head to new front node
        void removeFront() {
            if(get_size()==0) throw std::runtime_error ("CANT REMOVE SINCE LIST IS EMPTY");
            Node<T>* curr = head->next;
            if(get_size()==1){
                curr=head;
                head=nullptr;
                tail=nullptr;
                delete curr;
                size--;
            }
            if(get_size()>1){
                curr=head;
                head=head->next;
                head->prev=nullptr;
                curr->next=nullptr;
                delete curr;
                size--;
            }           
        }
        //removes last node from list
        void removeBack() {
            Node<T>* curr = tail->prev;
                                    
            if(get_size()==1){
                curr=head;
                head=nullptr;
                tail=nullptr;
                delete curr;
                size--;
            }
            if(get_size()>1){
                curr = tail;
                tail = tail->prev;
                tail->next=nullptr;
                curr->prev=nullptr;
                delete curr;
                size--;
            }
        }
        //returns content of first node
        const T& front() {
            return head->c;
        }
        //returns content of last node
        const T& end(){
            return tail->c;
        }               
        //deconstructor
        ~DLL(){
            Node<T>* temp;
            while(head != nullptr){
                temp = head;
                head = head->get_next();
                delete temp;
            }
        }

        void printList(){
            Node<T>* curr =head;
            while(curr!=nullptr){
                std::cout<<curr->c<<" -> ";
                curr=curr->next;
            }
        }

};

#endif