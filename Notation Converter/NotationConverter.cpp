/*
Names: Osama Bin Basit(driver)    Chen-Yu Liu(navigator)
UID:         U39050886                  U39755333
Weightage:     50-50
*/

#include "NotationConverter.hpp"

//returns an error if [, ],\ or ^ are in string
void NotationConverter::checkBad(std::string str) {
    for(unsigned int i=0; i<str.size();i++){
        if(str[i]=='['||str[i]==']'||str[i]=='^'||str[i]=='\\') 
            throw std::runtime_error ("STRING CONTAINS INVALID CHARACTERS");
    }
}

//sets priority of / and * as 2, and + and - as 1
int NotationConverter::evaluatePrecedence(char c){
    if(c=='/'||c=='*')
        return 2;
    if(c=='+'||c=='-')
        return 1;
    else 
        return -1;
}

//removes spaces from input string
std::string NotationConverter::removeSpaces(std::string s){
    std::string out;
    for(unsigned int i=0; i<s.length();i++){
        char ch = s[i];
        if(ch==' '){
            continue;
        }
        else{
            out +=s[i];
        }
    }
    return out;
}

//formats the final string to be output in the required way
std::string NotationConverter::stringFormat(std::string str){
    std::string out;
    for(unsigned int i; i<str.length();i++){
        if(str[i]=='('){ //no spaces after (
            out = out + str[i];
        }
        else if(str[i+1]==')'){ //no space before )
            out = out+ str[i];
        }
        else{out = out+ str[i] +" ";} //add a space after character for all other cases
    }
    return out;
}

//converts infix format to postfix
std::string NotationConverter::infixToPostfix(std::string inStr){
    Deque<char>* dq = new Deque<char>();
    std::string out;
        
    std::string s = removeSpaces(inStr);  
    checkBad(s);

    for(unsigned int i =0; i<s.length();i++){
        char c = s[i];
        //outputs if operand
        if( (c>='a'&&c<='z')||(c>='A'&&c<='Z') ){
            out += c;
        }
        //pushes to deque if ()
        else if(c== '('){
            dq->insertBack('(');     //insertBack('(');
        }
        //pops until ) appears
        else if(c==')'){
            while(dq->back()!='('){
                out += dq->back();
                dq->removeBack();
            }
            dq->removeBack();
        }

        else{//if operator has lower precedence, add to string from back of deque
            while(!dq->empty() && evaluatePrecedence(s[i])<= evaluatePrecedence(dq->back())){
                out += dq->front();
                dq->removeBack();
            }
            dq->insertBack(s[i]); //push lower precedence operator to deque
        }
    } //else pop off from deque until deque is empty
    while(!dq->empty()){
        out += dq->back();
        dq->removeBack();
    } 

    return stringFormat(out);
}

std::string NotationConverter::infixToPrefix(std::string inStr){

    std::string s = removeSpaces(inStr);
    checkBad(s); 

    std::reverse(s.begin(),s.end()); //reverses input string 
    for (unsigned int i=0; i<s.size();i++){
        //changes ( to ) and ) to ( in reversed string
        if(s[i]=='('){
            s[i]=')';
        }
        else if(s[i]==')'){
            s[i]='(';
        }
    }
    //call infix to postfix function
    std::string out = infixToPostfix(s);
    //reverse postfix notation to make prefix notation
    std::reverse(out.begin(),out.end());

    return out;
}

std::string NotationConverter::postfixToInfix(std::string inStr){
    Deque<std::string>* dq = new Deque<std::string>();
    std::string out;

    inStr = removeSpaces(inStr);
    checkBad(inStr);

    for(unsigned int i=0;i<inStr.length();i++){
        char c = inStr[i];
        //push to deque if operand
        if( (c>='a'&&c<='z')||(c>='A'&&c<='Z') )
            dq->insertBack(std::string(1, c));
        //pop twice if operation, adds parenthesis and pushes back to deque
        else if(c=='+'||c=='-'||c=='*'||c=='/'){            
            std::string o1 = dq->back();
            dq->removeBack();
            std::string o2 = dq->back();
            dq->removeBack();
            out = '('+o2 +c + o1+')';
            dq->insertBack(out);          
        }
    }
    
    return stringFormat(out);
} 

std::string NotationConverter::prefixToInfix(std::string inStr){
    Deque<std::string>* dq = new Deque<std::string>();
    std::string out;

    std:: string s = removeSpaces(inStr);
    checkBad(s);

    std::reverse(s.begin(),s.end());

    for(unsigned int i=0;i<s.length();i++){
        char c = s[i];
        //push if operand
        if( (c>='a'&&c<='z')||(c>='A'&&c<='Z') ){
            dq->insertBack(std::string(1, c));
        }
        //pop and add parenthesis if operation and push back to deque
        else if(c=='+'||c=='-'||c=='*'||c=='/'){            
            std::string o1 = dq->back();
            dq->removeBack();
            std::string o2 = dq->back();
            dq->removeBack();
            out = '('+o1 +c + o2+')';
            dq->insertBack(out);          
        }
    }
    
    return stringFormat(out);  
}
//converts postfix to infixe, then infix to prefix
std::string NotationConverter::postfixToPrefix(std::string inStr){
    return infixToPrefix(postfixToInfix(inStr));
}
//converts prefix to infix, then infix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr){
    return infixToPostfix(prefixToInfix(inStr));
}



