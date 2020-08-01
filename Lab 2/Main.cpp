#include <iostream>
#include <sstream>
#include "BiRing.h"

using namespace std;

int main() {

    BiRing<int, string> ring1;

    cout << "Ring 1 : " << ring1 << endl;
    cout << "Ring 1 length is: " << ring1.length() << endl;

    ring1.push(1, "Horse");
    ring1.push(2, "Tiger");

    cout << "Ring 1 : " << ring1 << endl;

    ring1.push(3, "Camel");
    ring1.push(4, "Bird");

    cout << "Ring 1 : " << ring1 << endl;
    cout << "Ring 1 length is: " << ring1.length() << endl;

    BiRing<int, string> ring2 = ring1;
    cout << "Ring 2 : " << ring2 << endl;

    ring1.deleteLast();
    ring1.deleteFirst();

    cout << "Ring 1 : " << ring1 << endl;
    cout << "Ring 1 length is: " << ring1.length() << endl;

    ring1.deleteAll();

    cout << "Ring 1 : " << ring1 << endl;
    cout << "Ring 1 length is: " << ring1.length() << endl;


    BiRing<int, string>::iterator iterator = ring2.beginning();

    iterator = iterator.add(5, "Lion");

    cout << "Ring 2 : " << ring2 << endl;

    iterator++;
    iterator.add(6, "Cat");
    cout << "Ring 2 : " << ring2 << endl;
    iterator -= 4;
    iterator.add(7, "Monkey");
    cout << "Ring 2 : " << ring2 << endl;

    BiRing<int, string> ring3(ring2);
    cout << "Ring 3 : " << ring3 << endl;
    
    BiRing<int, string> *ring5 = new BiRing<int, string>(ring2);

    cout << "Ring 5: " << *ring5 << endl;

    delete ring5;
    cout << "Ring 5: " << *ring5 << endl;

    iterator++;
    iterator.removeCurrent();
    cout << "Ring 2 : " << ring2 << endl;

    iterator += 19;
    iterator.removeCurrent();
    cout << "Ring 2 : " << ring2 << endl << endl;

    cout << " ------------- Shuffle Function Testing : -----------------" << endl << endl ;

    BiRing<int, string> ring6;
    ring6.push(1, "Five");
    ring6.push(2, "Four");
    ring6.push(3, "Three");
    ring6.push(4, "Two");
    ring6.push(5, "One");

    BiRing<int, string> ring7;
    ring7.push(1, "E");
    ring7.push(2, "D");
    ring7.push(3, "C");
    ring7.push(4, "B");
    ring7.push(5, "A");

    cout << "Ring 6: " << ring6 << endl << endl;
    cout << "Ring 7: " << ring7 << endl << endl;

    BiRing<int, string> ring4;
    ring4 = shuffle(ring6, ring7, 6, 6, 2);

    cout << "Ring 4: " << ring4 << endl;

    return 0;
}





