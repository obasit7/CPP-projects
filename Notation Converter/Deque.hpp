#include <iostream>
#include "DoublyLinkedList.hpp"

template <typename T>
class Deque { // deque as doubly linked list
    public:
        int size() const{
            return D.get_size();
        }
        bool empty() const{
            return D.is_empty();
        }
        const T& front() {
            return D.front();
        }
        const T& back() {
            return D.end();
        } 
        void printDeque(){
            D.printList();
        }
        void insertFront(const T& c){
            D.addFront(c);
            n++;
        }
        void insertBack(const T& c){
            D.addBack(c);
            n++;
        }
        void removeFront() {
            D.removeFront();
            n--;
        }
        void removeBack() {
            D.removeBack();
            n--;
        }

    private: 
        DLL<T> D; // linked list of elements
        int n; // number of elements
};

