#include <iostream>
#include <sstream>

using namespace std;

template<typename Key, typename Info>
class BiRing {

    struct Node {
        Key key;
        Info info;
        Node *next;
        Node *prev;

        Node() {};

        Node(Key key1, Info info1, Node *node, Node *prevNode) {
            key = key1;
            info = info1;
            next = node;
            prev = prevNode;
        };
    } *element;

public:
    class Iterator {
    private:
        Node *targetNode;

    public:
        friend class BiRing;

        Iterator() {
            targetNode = NULL;
        }

        Iterator(const Iterator &copy) {
            targetNode = copy.targetNode;
        }

        Iterator(Node *copy) {
            targetNode = copy;
        }

        const Key &getKey() {
            return targetNode->key;
        }

        const Info &getInfo() {
            return targetNode->info;
        }

        bool operator!=(const Iterator &compare) const {
            return targetNode != compare.targetNode;
        }

        bool operator==(const Iterator &compare) const {
            return targetNode == compare.targetNode;
        }

        Iterator &operator+(const int add) {
            if (targetNode == NULL) {
                return *this;
            }

            Iterator *tempIterator = new Iterator(*this);
            for (int i = 0; i < add; i++) {
                tempIterator->targetNode = tempIterator->targetNode->next;
            }
            return *tempIterator;
        }

        Iterator &operator-(const int substract) {
            if (targetNode == NULL) {
                return *this;
            }

            Iterator *tempIterator = new Iterator(*this);
            for (int i = 0; i < substract; i++) {
                tempIterator->targetNode = tempIterator->targetNode->prev;
            }
            return *tempIterator;
        }

        Iterator &operator++() {                  //pre-increment like ++a
            if (targetNode != NULL) {
                targetNode = targetNode->next;
            }
            return *this;
        }

        Iterator operator++(int) {              //post-increment like a++
            Iterator tempIterator(*this);
            if (targetNode != NULL) {
                targetNode = targetNode->next;
            }
            return tempIterator;
        }

        Iterator &operator--() {
            if (targetNode != NULL) {
                targetNode = targetNode->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator tempIterator(*this);
            if (targetNode != NULL) {
                targetNode = targetNode->prev;
            }
            return tempIterator;
        }

        Iterator &operator=(const Iterator &equal) {
            targetNode = equal.targetNode;
            return *this;
        }

        Iterator &operator+=(const int add) {
            for (int i = 0; i < add; i++) {
                targetNode = targetNode->next;
            }
            return *this;
        }

        Iterator operator-=(const int substract) {
            for (int i = 0; i < substract; i++) {
                targetNode = targetNode->prev;
            }
            return *this;
        }

        Iterator &add(const Key &key, const Info &info) {
            if (targetNode == NULL) {
                return *this;
            }

            Node *newNode = new Node(key, info, targetNode->next, targetNode);
            targetNode->next->prev = newNode;
            targetNode->next = newNode;
            return *(new Iterator(newNode));
        }

        Iterator &removeCurrent() {
            if (targetNode == NULL) {
                return *this;
            } else if (targetNode->next == targetNode && targetNode->prev == targetNode) {
                return *this;
            }

            Node *deleteNode = targetNode;
            Node *tempNode = deleteNode->prev;
            tempNode->next = deleteNode->next;
            tempNode = deleteNode->next;
            tempNode->prev = deleteNode->prev;


            targetNode = targetNode->next;
            delete deleteNode;
            return *this;
        }
    };

    typedef Iterator iterator;

    BiRing(){
        element = new Node();
        element->next = element;
        element->prev = element;
    };

    BiRing(const BiRing<Key, Info> &copyBiRing){
        element = new Node();
        element->next = element;
        element->prev = element;

        BiRing<Key, Info>::iterator copyIterator = copyBiRing.beginning();
        BiRing<Key, Info>::iterator iterator = element;

        while (copyIterator != copyBiRing.end()) {
            iterator.add(copyIterator.getKey(), copyIterator.getInfo());
            copyIterator++;
        }
    };

    ~BiRing(){
        deleteAll();
    };

    BiRing<Key, Info> &operator=(const BiRing<Key, Info> &BiRing) {
        deleteAll();
        ::BiRing<Key, Info>::iterator copyIterator = BiRing.beginning();

        while (copyIterator != BiRing.end()) {
            push(copyIterator.getKey(), copyIterator.getInfo());
            copyIterator++;
        }
        return *this;
    };

    BiRing<Key, Info> &operator+(const BiRing <Key, Info> &ring) {
        ::BiRing<Key, Info> *newBiRing = new ::BiRing<Key, Info>(*this);
        ::BiRing<Key, Info>::iterator copyIterator = ring.beginning();

        while (copyIterator != ring.end()) {
            (*newBiRing).push(copyIterator.getKey(), copyIterator.getInfo());
            copyIterator++;
        }

        return *newBiRing;
    };

    int length() const {
        int counter = 0;
        ::BiRing<Key, Info>::Iterator countIterator = beginning();
        while (countIterator != end()) {
            counter++;
            countIterator++;
        }
        return counter;
    }

    Iterator beginning() const {
        return ++(iterator(element));
    };

    Iterator end() const {
        return iterator(element);
    };

    Iterator push(const Key &key, const Info &info) {
        Iterator tempIterator = beginning();
        tempIterator--;
        return tempIterator.add(key, info);
    };

    Iterator deleteFirst() {
        Iterator tempIterator = beginning();
        if (tempIterator == end()) {
            return tempIterator;
        }
        return tempIterator.removeCurrent();
    };

    Iterator deleteLast() {
        Iterator tempIterator = end();
        tempIterator--;
        if (tempIterator == end()) {
            return tempIterator;
        }
        return tempIterator.removeCurrent();
    };

    void deleteAll() {
        Iterator tempIterator = beginning();

        while (tempIterator != end()) {
            tempIterator.removeCurrent();
        }
    };

    friend ostream &operator<<(ostream &os, const BiRing <Key, Info> &BiRing) {
        stringstream strStream;
        iterator tempIterator = BiRing.beginning();
        if (tempIterator == BiRing.end()) {
            strStream << "The ring is empty";
        }

        while (tempIterator != BiRing.end()) {
            strStream << tempIterator.getInfo() << " ";
            tempIterator++;
        }

        return os << strStream.str();
    };
};


template<typename Key, typename Info>
BiRing<Key, Info> shuffle(const BiRing<Key, Info>& first, BiRing<Key, Info>& second, int nbfirst, int nbsecond, int reps)
{
    BiRing<Key, Info> returnBiRing;
    BiRing<int, string>::iterator iterator1 = first.beginning();
    BiRing<int, string>::iterator iterator2 = second.beginning();

    try {

        for (int i = 0; i < reps; i++)
        {
            for (int j = 0; j < nbfirst; j++)
            {

                if (iterator1.getKey() == 0) {
                    iterator1++;
                }
                returnBiRing.push(iterator1.getKey(), iterator1.getInfo());
                iterator1++;

            }

            for (int k = 0; k < nbsecond; k++)
            {
                if (iterator2.getKey() == 0) {
                    iterator2++;
                }
                returnBiRing.push(iterator2.getKey(), iterator2.getInfo());
                iterator2++;
            }
        }
        
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    return returnBiRing;
}
