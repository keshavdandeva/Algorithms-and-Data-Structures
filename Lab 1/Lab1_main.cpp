#include <iostream>
#include <string>
#include "Lab1_Sequence.h"
#include "Lab1_Counter.h"
using namespace std;

int main(){

	int input = 0;
	while(true){

		cout << "------------Testing-------------"<<endl;
		cout << "Type 1 for Sequence Class Testing, 2 for Counter Class Testing, 3 to exit :"<<endl;
		while(input != 1 && input !=2 && input !=3){
			cin >> input;
			if(input != 1 && input !=2 && input !=3){
				cout << "Please type the correct number : ";
			}
		}

		if(input == 1){

			cout << "Sequence class testing!" << endl;

			Sequence<int> s1;
			Sequence<int> s2;

			s1.pushBack(1);
			s1.pushBack(2);
			s1.pushBack(3);
			s1.pushBack(4);
			s2.pushBack(7);
			s2.pushFront(6);
			s2.pushFront(5);

			s1.print();
			s2.print();

			Sequence<int> s3 = s1 + s2;
			s3.print();

			Sequence<int> s4(s3);
			s4.print();


            /*s4.removeFront();
            s4.removeBack();

            s4.print();
            int value = 123;
            value = s4.getVal(10);
            cout << "Value at 10 = " << value << endl;
            value = s4.getVal(-10);
            cout << "Value at -10 = " << value << endl;
            value = s4.getVal(2);
            cout << "Value at 2 = " << value << endl;

            bool exist;
            exist = s4.valExists(111);
            cout << "Value 111 exists? : " << exist << endl;
            exist = s4.valExists(3);
            cout << "Value 3 exists? : " << exist << endl;

            s4.print();

            int len = s4.length();
            cout << "length = " << len << endl;



            s4.insertAtIndex(0, 0); //insert it above 1
            s4.insertAtIndex(-1, 0); //insert it above 0

            s4.insertAtIndex(8, 9); // insert it below 7
            s4.insertAtIndex(10, 10); //insert it below 8
            s4.insertAtIndex(9, 10); //insert it above 10
            s4.insertAtIndex(1234, 20); //out of bounds
            s4.insertAtIndex(5678, 30); //out of bounds
            s4.insertAtIndex(2244, -1); //negative index
            s4.insertAtIndex(2244,5);
            s4.print();

            s4.removeVal(2244);
            s4.print();

            s1.~Sequence();
            s2.~Sequence();
            s3.~Sequence();
            s4.~Sequence();*/

			break;

		}
		else if(input == 2){

			cout << "Counter class testing!" << endl;

			int choice = 0;
			cout << "Type 1 for entering data, 2 for reading file and 3 to exit: "<<endl;
			while(choice != 1 && choice !=2 && choice !=3){
				cin >> choice;
				if(choice != 1 && choice !=2 && choice !=3){
					cout << "Please enter a valid number: ";
				}
			}

			Counter<string> c1;
			int a;
			if(choice == 1){

				cout << "Please enter the string" << endl;
				a = count_words(c1, cin);
				c1.print();
				cout << "Length : " << c1.length() << " | Word occurrences : " << c1.occurence_sum() << endl;
				//c1.~Counter();

			}
			else if(choice == 2){

				ifstream file_data;
				string filename;
				cout << "Enter filename :";
				do{

					fflush(stdin);
					getline(cin, filename);
					file_data.open(filename);
					//if(!file_data) cout << "File doesn't exist" << endl;

				}while(!file_data);

				a = count_words(c1, file_data);
				int select = 0;
				cout << "Type 3 for top 10 highest frequency words, 2 for a specific word or 1 for all words :"<<endl;
				cin >> select;
				if(select == 1){
					c1.print();
					cout << "Length : " << c1.length() << " | Word occurrences : " << c1.occurence_sum() << endl;
				}
				else if(select == 2){
					string input;
					cout << "Type the word you wanna check or type -> ! to exit" << endl;
					while(true){
						fflush(stdin);
						getline (cin, input);
						if (input == "!") break;
						else cout<< input << " : " << c1.Keyoccurrence(input) << endl;
					}
				}
				else if(select == 3){
					
					string word;

					for(int i=0;i<10;i++){
						word = c1.HighestWord();
						c1.DeleteKey(word);
					}
				}

				file_data.close();
				c1.~Counter();

			}
			else{
				break;
			}

		}
		else{
			break;
		}

	}

	return 0;

}
