#include "CalcList.hpp"

static double finalTotal = 0;

CalcList::CalcList(): head(nullptr), count(0) {} //constructor
CalcList::~CalcList() {while(!empty()) removeFront(); } //deconstructor

bool CalcList::empty() const { return head==nullptr; } //checks if list is empty

//setter and getter funcions
void Node::set_nodeTotal(double n){this->nodeTotal = n;}
void Node::set_total(double t){this->total = t;}
void Node::set_operand(double o){this->operand = o;}
void Node::set_operation(char s){this->operation=s;}
double Node::get_nodeTotal(){return nodeTotal;}
double Node::get_total(){return total;}
double Node::get_operand(){return operand;}
char Node::get_operation(){return operation;};

//remove front item list
void CalcList::removeFront(){ 
    Node* rem = head;
    head = head->next;
    delete rem;
}

//find the total number from the list.
double CalcList::total() const {
    return finalTotal;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){
    Node* temp = new Node; //create new node temp
    switch(func){ //using a switch to decide FUNCTIONS
        case ADDITION:
            temp->set_operation('+'); 
            temp->set_operand(operand);
            //if head is empty
            if(head==nullptr){ 
                temp->set_total(0);
                temp->set_nodeTotal(temp->get_total() + operand);
                head = temp;
                head->next=nullptr;
            } else { //if head is not empty
                Node* temp2 = head; //set temp variable to head
                while(temp2->next!=nullptr){ //reach last node in list
                    temp2= temp2->next;
                }
                temp->set_total(temp2->get_nodeTotal()); //set previous total as new total of node
                temp->set_nodeTotal(temp->get_total() + operand) ; //
                temp2->next = temp;
                temp->next = NULL;
            }

            finalTotal = temp->nodeTotal; //set the finalTotal number
            break;

        case SUBTRACTION:
            temp->set_operation('-');
            temp->set_operand(operand);
            if(head==nullptr){
                temp->set_total(0);
                temp->set_nodeTotal(temp->get_total() - operand);
                head = temp;
                head->next = nullptr;
            } else {
                Node* temp2 = head;
                while(temp2->next!=nullptr){
                    temp2= temp2->next;
                }
                temp->set_total(temp2->get_nodeTotal());
                temp->set_nodeTotal(temp->get_total() - operand) ;
                temp2->next = temp;
                temp->next = nullptr;
            }
            finalTotal = temp->nodeTotal;
            
            break;

        case MULTIPLICATION:
            temp->set_operation('*');
            temp->set_operand(operand);
            if(head==nullptr){
                temp->set_total(0);
                temp->set_nodeTotal(temp->get_total() * operand);
                head = temp;
                head->next = nullptr;
            } else {
                Node* temp2 = head;
                while(temp2->next!=nullptr){
                    temp2= temp2->next;
                }
                temp->set_total(temp2->get_nodeTotal());
                temp->set_nodeTotal(temp->get_total() * operand) ;
                temp2->next = temp;
                temp->next = nullptr;
            }
            finalTotal = temp->nodeTotal;
            
            break;

        case DIVISION:
        
        try{ //trying the statements below to see if operand is 0
            if(operand==0) {throw "CANT DIVIDE BY 0";}//throw std::runtime_error("division by 0")
            temp->set_operation('/'); 
            temp->set_operand(operand);
        
            if(head==nullptr){
                temp->set_total(0);
                temp->set_nodeTotal(temp->get_total() / operand);
                head = temp;
                head->next = nullptr;
            } else {
                Node* temp2 = head;
                while(temp2->next!=nullptr){
                    temp2= temp2->next;
                }
                temp->set_total(temp2->get_nodeTotal());
                temp->set_nodeTotal(temp->get_total() / operand) ;
                temp2->next = temp;
                temp->next = nullptr;
            }
        } catch (double ex){
                std::cout<<"Can't divide by zero -"<<ex<<std::endl;
            }
        
            finalTotal = temp->nodeTotal;
            
            break;
        
    }
    count++;
    
}

//remove last node from the list 
void CalcList::removeLastOperation(){
    
    //if list is empty
    if (head==nullptr){
        throw "CAN'T REMOVE SINCE LIST IS EMPTY";
        return;
    }

    //if node to remove is the only node in list
    if(head->next==nullptr){
        finalTotal =0;
        delete head;
        head = nullptr;
        count--;
        return;
    }

    //to remove any other node
    Node* secondLast = head;
    //go to the second last node
    while(secondLast->next->next!=nullptr){
        secondLast = secondLast->next;
    }
    //delete last node
    delete secondLast->next;
    //set new last node to null
    secondLast->next = nullptr;
    //set new final total
    finalTotal = secondLast->get_nodeTotal();
    count--;
    return; 
}

std::string CalcList::toString(unsigned short precision)const{
    if(head==nullptr){ return "";} //if list is empty
    
    //set up temporary variables to switch nodes
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* current = head;
        
    while(current != nullptr){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
        
    Node* temp = prev;

    std::string out = "";
    int j = count;
    int i = 0;

    //using sstream and iomanip to output string and double values
    std::ostringstream stream;
    stream<<std::setprecision(precision)<<std::fixed;
    while (temp!= nullptr && i < count){
        double tot = temp->get_total();
        double operand = temp->get_operand();
        char operation = temp->get_operation();
        double nodeTotal = temp->get_nodeTotal();
        stream<<j<<": "<<tot<<operation<<operand<<"="<<nodeTotal<<"\n";
        temp = temp->next;
        j--;
        i++;
    }

    out = stream.str();

    //revert linked lsit back to original form
    prev = nullptr;
    next = nullptr;
    current = prev;
    
    while(current != nullptr){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return out;

}








 


