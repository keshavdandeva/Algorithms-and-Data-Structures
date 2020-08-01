#ifndef LAB1_COUNTER
#define LAB1_COUNTER

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <typename Key>
class Counter{

	struct Node{

		Key key;
		unsigned int occurence;
		Node* next;

	} *head;

public:

	Counter();
	~Counter();
	bool Keyexists(const Key &key);
	int Keyoccurrence (const Key &key);
	string HighestWord ();
	bool DeleteKey (const Key &key);
	void insert(const Key &key);
	void print();
	unsigned int length() const;
	unsigned int occurence_sum() const;
};

template<typename Key>
Counter<Key>::Counter(){

	head = NULL;

}

template<typename Key>
Counter<Key>::~Counter(){

	Node *tempNode;
	while((tempNode = head) != NULL){
		head = head->next;
		delete tempNode;
	}

}

template<typename Key>
bool Counter<Key>::Keyexists(const Key &key){

	if(head == NULL){
		return false;
	}

	else{

		Node *currNode = head;
		while(currNode != NULL){
			if(currNode->key == key) return true;
			currNode = currNode->next;
		}

	}

	return false;
}

template<typename Key>
bool Counter<Key>::DeleteKey (const Key &key){

	if(Keyexists(key)){

		Node *currNode = head;
		Node *prevNode;
		while(currNode != NULL){

			if(currNode->key == key){

				if(currNode == head){

					head = head->next;
					delete currNode;
					currNode = head;
					return true;

				}
				else{


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

	else
		return false;

}



template<typename Key>
int Counter<Key>::Keyoccurrence (const Key &key){

	if(Keyexists(key)){

		Node *currNode = head;
		while(currNode != NULL){
			if(currNode->key == key) return currNode->occurence;
			currNode = currNode->next;
		}
	}
	else{
		cout<<"The key doesn't exist"<<endl;
	}
	return 0;
}

template<typename Key>
string Counter<Key>::HighestWord (){
	int a = 0;
	int i = 0;
	string key;
	
	Node *currNode = head;

		while(currNode != NULL){
			if(currNode->occurence > a){
				a = currNode->occurence;
				key = currNode->key;
			}

			currNode = currNode->next;

		}

		cout<<key<< " : " <<a<<endl;
		return key;

	
}

template<typename Key>
void Counter<Key>::insert(const Key &key){

	if(Keyexists(key) == 1){

		Node *currNode = head;
		while(currNode != NULL){
			if(currNode->key == key) currNode->occurence++;
			currNode = currNode->next;
		}

	}
	else{

		Node *tempNode = new Node();
		tempNode->key = key;
		tempNode->occurence = 1;
		tempNode->next = NULL;

		if(head == NULL){
			head = tempNode;
		}
		else{
			Node* currNode = head;
			while(currNode->next != NULL){
				currNode = currNode->next;
			}
			currNode->next = tempNode;
		}

	}

}

template<typename Key>
void Counter<Key>::print(){

	if(head == NULL){
		cout << "List is empty!" << endl;
	}
	else{
		Node *currNode = head;
		int limit = 0;
		cout << " Printing List: " << endl;
		while(currNode != NULL){
			cout << currNode->key << " : " << currNode->occurence << endl;
			limit++;
			currNode = currNode->next;
			if(limit == 15){
				cout << "First 15 words and their occurence are displayed above. Press 1 to get next 15 or any other key to exit. ";
                fflush(stdin); //to flush or clear the output buffer of the stream
                if(char c = getchar() == '1'){
                	limit = 0;
                }
                else{
                	break;
                }
            }
        }
        cout << " -------------------------" << endl;

    }
}

template<typename Key>
unsigned int Counter<Key>::length() const{

	int length = 0;
	Node *currNode = head;
	while(currNode != NULL){
		length++;
		currNode = currNode->next;
	}
	return length;

}

template<typename Key>
unsigned int Counter<Key>::occurence_sum() const{

	int count = 0;
	Node *currNode = head;
	while(currNode != NULL){
		count += currNode->occurence;
		currNode = currNode->next;
	}
	return count;

}

int count_words(Counter<string>& cnt, istream& source){

	string str;
	string word;
    fflush(stdin); // to flush or clear the output buffer of the stream
    while(getline(source, str)){

    	if(str.empty())continue;

    	for(int i = 0; i < str.size(); i++){

    		if(str[i]>=65 && str[i]<=92){
		        str[i]=str[i]+32;           //converting to lower case
		    }

		    if(ispunct(str[i])){
                if(str[i] != '\''){		   //cleaning the text of punctuations
                    str[i] = ' ';          //only considering apostrophe as word
                }
            }

        }

        istringstream iss(str);
        while (iss >> word){               //converting to string
            cnt.insert(word);              //inserting the word and counting
        }

        if(&source == &cin) break;

    }

    return 0;

};

#endif
