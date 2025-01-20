// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next) // creates node with passed values
{
    return new node{restaurantName, PriorityQ(50), next};
}

HashTable::HashTable(int bsize) // constructor, creates new hash table with given size, initializes all values in table to nullptr
{
    tableSize = bsize;
    table = new node*[tableSize];

    for(int i=0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() // destructor, goes through all elements in table and all chained nodes and deletes
{
    for (int i = 0; i < tableSize; i++)
    {
        node* temp = table[i];
        table[i] = nullptr;

        while (temp != nullptr)
        {
            node* temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }

    delete [] table;
    table = nullptr;
}

void HashTable::displayTable() // display, iterates through each index and outputs including if there are any chained elements
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << " | ";
        node* temp = table[i];

        while (temp != nullptr)
        {
            cout << temp->restaurantName << "-->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    int hashVal = 0;

    for (int i = 0; i < restaurantName.length(); i++) // for loop to go through each letter for hash function
    {
        hashVal = hashVal + int(restaurantName[i]); // function to convert char to ascii int value and add to total
    }

    return hashVal % tableSize;
}

node* HashTable::searchItem(string restaurantName)
{
    unsigned int key = hashFunction(restaurantName);

    if (table[key] == nullptr) // if nothing is at hashed index return nullptr
    {
        return nullptr;
    }
    else if (table[key] != nullptr)
    {
        node *temp = table[key];

        while (temp->next != nullptr && temp->restaurantName != restaurantName) // if the name is not the name at the first index go through the chain
        {
            temp = temp->next;
        }

        if (temp->restaurantName == restaurantName) // if restaurantName matches then return pointer to node
        {
            return temp;
        }
        else // if it doesn't match return nullptr
        {
            return nullptr;
        }
    }

    return nullptr; // if it gets here it probably doesn't exist
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    unsigned int key = hashFunction(restaurant.restaurantName); // get hash key
    node *newNode = searchItem(restaurant.restaurantName); // search for node to see if it exists

    if (newNode != nullptr) // if it exists, add review to priority queue
    {
        newNode->pq.insertElement(restaurant); 
    }
    else // if it does not exist
    {
        node *temp = table[key]; // get pointer to first element at key

        if (temp != nullptr) // if the element exists increment collisions
        {
            numCollision++;
        }

        table[key] = createNode(restaurant.restaurantName, temp); // add element to head of linked list with next as the old head of the linked list (if it was empty it would be nullptr)
        table[key]->pq.insertElement(restaurant); // add review to pq
    }
}

void HashTable::setup(string fname)
{
    ifstream myfile; // create ifstream object and open file
    myfile.open(fname);

    string line, rName, review, cName;
    int time;
    

    if (myfile.is_open()) // make sure file is open
    {
        while (getline (myfile,line)) // file parsing using stringstream
        {
            istringstream ss(line);
            string temp;
            int sc = 0;

            while (getline(ss, temp, ';'))
            {
                if (sc == 0)
                {
                    rName = temp;
                }
                else if (sc == 1)
                {
                    review = temp;
                }
                else if (sc == 2)
                {
                    cName = temp;
                }
                else if (sc == 3)
                {
                    time = stoi(temp);
                }
                sc++;
            }

            ReviewInfo newReview = {rName, review, cName, time};
            insertItem(newReview);
        }
    }
    else // if file is not open get new filename (valgrind fix)
    {
        cout << "file read error, new fname:";
        getline(cin, fname);
        setup(fname);
    }
}