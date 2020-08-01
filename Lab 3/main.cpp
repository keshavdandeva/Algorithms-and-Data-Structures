#include "avltree.h"

int main(){

    int choice;
    string input;
    while(true){

        choice = 0;
        cout << " ------- TESTING -----------" << endl;
        cout << "Type : 1 for General Testing, 2 for Word Counter, 3 to exit: ";
        while(choice != 1 && choice !=2 && choice !=3){

            getline(cin, input);
            stringstream ss(input);
            if(ss >> choice){
                if(choice != 1 && choice !=2 && choice !=3){
                    cout << "Enter a valid number! ";
                }
                else{
                    break;
                }
            }
            else{
                cout << "Please enter a valid number : ";
            }
            
        }
        
        if(choice == 1){

            cout << endl << "-------- 1. General Testing ----------" << endl << endl;

            // create the tree and try methods on an empty tree
            cout << "Testing operations on a empty tree :" << endl;
            AvlTree<string, string> tree1;
            tree1.printTree();
            tree1.removeNode("Inception");
            tree1.keyExists("Key");
            cout << "Size of Tree : " << tree1.size() << endl;
            tree1.showRoot();
            cout << endl;

            // populate the tree
            cout << "Inserting nodes :" << endl;
            tree1.addNode("Dark Knight", "C. Nolan");
            tree1.addNode("Zodiac", "D. Fincher");
            tree1.printTree();
            cout << "Size of Tree = " << tree1.size() << endl;
            cout << endl;

            // let's create an imbalance
            cout << "Balancing Operation (right rotation)" << endl;
            tree1.addNode("Memento", "C. Nolan");
            tree1.printTree();
            cout << "Size of Tree = " << tree1.size() << endl;
            cout << endl;

            // let's remove a side node, and then the root
            cout << "Deleting nodes :" << endl;
            tree1.removeNode("Memento");
            tree1.printTree();
            cout << "Size of Tree = " << tree1.size() << endl;
            tree1.removeNode("Zodiac");
            tree1.printTree();
            cout << "Size of Tree = " << tree1.size() << endl;
            cout << endl;

            // other balancing operation
            cout << "Other Balancing Operations :" << endl;
            tree1.deleteAll();
            cout << endl;

            cout << "Left Rotation :" << endl;
            tree1.addNode("Armageddon", "B. Wills");
            tree1.addNode("Legend", "W. Smith");
            tree1.printTree();
            tree1.addNode("Nightcrawler", "J. Gyllenhal");
            tree1.printTree();
            tree1.deleteAll();
            cout << endl;

            cout << "Left-Right Rotation :" << endl;
            tree1.addNode("Nightcrawler", "J. Gyllenhal");       
            tree1.addNode("Legend", "W. Smith");
            tree1.printTree();
            tree1.addNode("Armageddon", "B. Wills");
            tree1.printTree();
            tree1.deleteAll();
            cout << endl;

            cout << "Right-Left Rotation :" << endl;
            tree1.addNode("Armageddon", "B. Wills");
            tree1.addNode("Nightcrawler", "J. Gyllenhal");
            tree1.printTree();
            tree1.addNode("Legend", "W. Smith");
            tree1.printTree();
            cout << endl;

            // bigger tree test
            AvlTree<string, string> tree2;
            cout << "let's try a bigger tree test" << endl;
            tree2.addNode("Inception", "L. Caprio");
            tree2.addNode("Mad Max", "T. Hardy");
            tree2.addNode("Joker", "J. Phoenix");
            tree2.addNode("Bad Boys", "W. Smith");
            tree2.addNode("Shutter Island", "M. Ruffalo");
            tree2.addNode("Iron Man", "RDJ");
            tree2.addNode("Ant Man", "P. Rudd");
            tree2.addNode("Se7en", "B. Pitt");
            tree2.addNode("Memento", "C. Nolan");
            tree2.addNode("Pulp Fiction", "S. Jackson");
            tree2.addNode("Dark Knight", "C. Bale");
            tree2.addNode("Spider Man", "T. Maguire");
            tree2.printTree();
            cout << "Size of Tree = " << tree2.size() << endl;
            tree2.showRoot();
            cout << endl;

            cout << "Adding more data" << endl;
            tree2.addNode("Incredibles", "Disney");
            tree2.addNode("Wall-E", "Pixar");
            tree2.addNode("Ice Age", "Disney");
            tree2.addNode("Kill Bill", "Q. Tarantino");
            tree2.addNode("Superman", "H. Cavill");
            tree2.addNode("Deadpool", "R. Reynolds");
            tree2.printTree();
            cout << "Size of Tree = " << tree2.size() << endl;
            tree2.showRoot();
            cout << endl;

            cout << "Deleting some data :" << endl;
            tree2.removeNode("Joker");
            tree2.removeNode("Ant Man");
            tree2.removeNode("Ice Age");
            tree2.removeNode("Bad Boys");
            tree2.removeNode("Mad Max");
            tree2.printTree();
            cout << "Size of Tree = " << tree2.size() << endl;
            tree2.showRoot();
            cout << endl;

        }
        else if(choice == 2){

            cout << "-------- 2. Word Count Testing ----------" << endl;

            int choice2 = 0;
            cout << "Type : 1 for user input, 2 for reading file, 3 to go back: ";
            while(choice2 != 1 && choice2 !=2 && choice2 !=3){

                getline(cin, input);
                stringstream ss(input);
                if(ss >> choice2){
                    if(choice2 != 1 && choice2 !=2 && choice2 !=3){
                        cout << "Enter a valid number : ";
                    }
                    else{
                        break;
                    }
                }
                else{
                    cout << "Enter a valid number : ";
                } 

            }

            AvlTree<string, int> tree;
            int a;
            if(choice2 == 1){

                cout << "Please enter the string :" << endl;
                a = count_words(tree, cin);
                tree.printTree();
                cout << "Size of tree = " << tree.size() << " | Total word count of tree = " << tree.occurenceSum() << endl;

            }
            else if(choice2 == 2){

                ifstream file_data;
                string filename;
                
                do{

                    cout << "Enter file name: ";
                    fflush(stdin);
                    getline(cin, filename);
                    file_data.open(filename);
                    if(!file_data) cout << "File doesn;t exist!" << endl;

                }while(!file_data);
                
                a = count_words(tree, file_data);
                tree.printTree();
                cout << "Size of Tree = " << tree.size() << " | Total word count of tree = " << tree.occurenceSum() << endl;
                file_data.close();

            }
            else{
                continue;
            }

            int occ;
            string word1;
            cout << "To find occurences of specific word, type it or type ! to go back: "<< endl;
            while(true){
                
                fflush(stdin);
                getline(cin, input);
                if(input == "!") break;
                else tree.printKey(input);
                
            }

        }
        else{
            break;
        }

    }

    return 0;

}