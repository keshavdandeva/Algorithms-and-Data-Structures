#ifndef LAB1_SEQUENCE
#define LAB1_SEQUENCE

#include <iostream>
using namespace std;

template <typename Val_type>
class Sequence{

    struct Node {
        Val_type value;
        Node *next;

    } *head;

public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence<Val_type> &newSequence);
    void pushFront(const Val_type &val);
    void pushBack(const Val_type &val);
    void removeFront();
    void removeBack();
    void deleteAll();
    bool valExists(const Val_type &val);
    Val_type getVal(int index);
    bool removeVal(const Val_type &val);
    void print();
    int length() const;
    void insertAtIndex(const Val_type &val, int index);
    Sequence<Val_type> &operator=(const Sequence<Val_type> &sequence);
    Sequence<Val_type> &operator+(const Sequence<Val_type> &sequence);

};

template<typename Val_type>
Sequence<Val_type>::Sequence(){

    head = NULL;

}

template<typename Val_type>
Sequence<Val_type>::~Sequence(){

    deleteAll();

}

template<typename Val_type>
void Sequence<Val_type>::pushFront(const Val_type &val){

    Node *tempNode = new Node();
    tempNode->value = val;
    tempNode->next = head;
    head = tempNode;

}

template<typename Val_type>
void Sequence<Val_type>::pushBack(const Val_type &val){

    Node *tempNode = new Node();
    tempNode->value = val;
    tempNode->next = NULL;

    if(head == NULL){
        head = tempNode;
    }
    else{
        Node* currentNode = head;
        while(currentNode->next != NULL){
            currentNode = currentNode->next;
        }
        currentNode->next = tempNode;
    }

}

template<typename Val_type>
Sequence<Val_type>::Sequence(const Sequence<Val_type> &newSequence){

    head = NULL;
    if(&newSequence != NULL){
        Node *tempNode = newSequence.head;
        while(tempNode != NULL){
            pushBack(tempNode->value);
            tempNode = tempNode->next;
        }
    }

}

template<typename Val_type>
void Sequence<Val_type>::deleteAll() {
    Node *tempNode;
    while ((tempNode = head) != NULL) {
        head = head->next;
        delete tempNode;
    }
}

template<typename Val_type>
void Sequence<Val_type>::removeFront(){

    if(head != NULL){
        Node *tempNode = head;
        head = head->next;
        delete tempNode;
    }

}

template<typename Val_type>
void Sequence<Val_type>::removeBack(){

      Node *tempNode = head;
    Node *prevNode = NULL;
    if (tempNode != NULL) {
        if (tempNode->next == NULL) {
            delete tempNode;
            head = NULL;
        } else {
            while (tempNode->next != NULL) {
                prevNode = tempNode;
                tempNode = tempNode->next;
            }
            prevNode->next = NULL;
            delete tempNode;
        }
    }
}

template<typename Val_type>
Val_type Sequence<Val_type>::getVal(int index){

    if(index < 0){
        cout << "Index is invalid!" << endl;
        return false;
    }
    else if(head == NULL){
        cout << "List is empty!" << endl;
        return false;
    }

    else if (index > length()){
        cout << "Index is greater than the number of elements!" << endl;
        return false;
    }


    else{
        Node *tempNode = head;
        int counter = 0;
        while(tempNode != NULL || counter > index){
            if(counter == index)return tempNode->value;
            tempNode = tempNode->next;
            counter++;
        }
    }
 }   

template<typename Val_type>
bool Sequence<Val_type>::valExists(const Val_type &val){

    if(head == NULL){

        return false;

    }
    else{

        Node *currentNode = head;
        while(currentNode != NULL){
            if(currentNode->value == val) return true;
            currentNode = currentNode->next;
        }

    }

    return false;
    
}

template<typename Val_type>
bool Sequence<Val_type>::removeVal(const Val_type &val){

    
    if(head == NULL){

        cout << "List is empty! Value doesn't exist" << endl;
        return false;

    }
    else{

        Node *currNode = head;
        Node *prevNode;
        while(currNode != NULL){

            if(currNode->value == val){

                if(currNode == head){

                    cout << "Value found at head and removed" << endl;
                    head = head->next;
                    delete currNode;
                    currNode = head;
                    return true;

                }
                else{

                    cout << "Value found after head and removed" << endl;
                    prevNode->next = currNode->next;
                    delete currNode;
                    currNode = prevNode->next;
                    return true;   
                }
                
            }
            else{

                prevNode = currNode;
                currNode = currNode->next;

            }

        }

    }

    return false;

}

template<typename Val_type>
void Sequence<Val_type>::print(){

    if(head == NULL){
        cout << "List is empty" << endl;
    }
    else{
        Node *currNode = head;
        cout << " Printing List : " << endl;
        while(currNode != NULL){
            cout << currNode->value << endl;
            currNode = currNode->next;
        }
        cout << " -------------------------" << endl;
    }

}

template<typename Val_type>
int Sequence<Val_type>::length() const{

    int length = 0;
    Node *currNode = head;
    while(currNode != NULL){
        length++;
        currNode = currNode->next;
    }
    return length;

}

template<typename Val_type>
void Sequence<Val_type>::insertAtIndex(const Val_type &val, int index){

    if(index > length() || index < 0){
        cout << "Index is invalid!" << endl;
        return;
    }
    else if(index == 0){
        Node *newNode = new Node();
        newNode->value = val;
        newNode->next = head;
        head = newNode;
        return;
    }
    else{

        Node *currNode = head;
        int counter = 0;
        while(counter < index - 1){
            currNode = currNode->next;
            counter++;
        }
        Node *newNode = new Node();
        newNode->value = val;
        newNode->next = currNode->next;
        currNode->next = newNode;

    }

}

template<typename Val_type>
Sequence<Val_type> &Sequence<Val_type>::operator=(const Sequence<Val_type> &sequence){

    if(&sequence == this){
        return *this;
    }

    Node *tempNode;
    while((tempNode = head) != NULL){
        head = head->next;
        delete tempNode;
    }

    *tempNode = sequence.head;

    while (tempNode != NULL) {
        pushBack(tempNode->value);
        tempNode = tempNode->next;
    }

    return *this;

}

template<typename Val_type>
Sequence<Val_type> &Sequence<Val_type>::operator+(const Sequence<Val_type> &sequence){

    Node *copyNode = sequence.head;
    while(copyNode != NULL){
        pushBack(copyNode->value);
        copyNode = copyNode->next;
    }

    return *this;

}

#endif 