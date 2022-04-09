/*
Assignment 1 (Calculator)
Name: Osama Bin Basit, Chen-Yu Liu
U Number: U39050886    ,U39755333
*/
#include<iostream>
#include <sstream>
#include <iomanip>
#include<string>
#include "CalcListInterface.hpp"

class Node{
    private: //
        char operation;
        double operand;
        double nodeTotal;
        double total;
        Node* next;

    public:
    //getters
        char get_operation();
        double get_operand();
        double get_nodeTotal();
        double get_total();
    //setters
        void set_operation(char s);
        void set_operand(double o);
        void set_nodeTotal(double n);
        void set_total(double t);
    friend class CalcList; //so CalcList can have access of Node

};

class CalcList: public CalcListInterface{
    public:
        CalcList(); //constructor
        ~CalcList(); //destructor
        
        bool empty() const; //checks if list is empty
        void removeFront();//remove front item from list
        //static Node* getNth(Node* head, int n);
        double total() const; //find the total number from the list.
        void newOperation(const FUNCTIONS func, const double operand);
        void removeLastOperation(); //remove from the list
        std::string toString(unsigned short precision)const;//strings of the list operations.
    private:
        Node* head;
        int count;
        //std::string* arr;
};