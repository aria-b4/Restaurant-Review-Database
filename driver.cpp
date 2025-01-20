#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// valgrind mem check: valgrind --leak-check=yes ./a.out test.txt 5

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool beenBuilt = false; // bool to check if file has been parsed
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);

        switch (ch)
        {
            case 1:
			{
				// ensures file only gets parsed once
                if (!beenBuilt)
                {
                    ht.setup(fname);
                    beenBuilt = true;
                }
                else
                {
                    cout << "The data structure has already been built." << endl;
                }
				break;
            }
            case 2:
			{
                // manually create review
                string rName, cName, review, time;
                
                cout << "Restaurant name: ";
                getline(cin, rName); // getline instead of cin as input could have spaces
                
                cout << "Customer: ";
                getline(cin, cName);

                cout << "Review: ";
                getline(cin, review);

                cout << "Time: ";
                getline(cin, time);
                int timeInt = stoi(time);

                ReviewInfo newReview = {rName, review, cName, timeInt};
                ht.insertItem(newReview);

				break;
            }
            case 3:
			{
                // look at most recent review for a restaurant
                string rName;
                cout << "Restaurant name: ";
                getline(cin, rName);
                node* temp = ht.searchItem(rName);

                temp->pq.peek();

				break;
            }
            case 4:
			{
                // pop most recent review
                string rName;
                cout << "Restaurant name: ";
                getline(cin, rName);
                node* temp = ht.searchItem(rName);

                temp->pq.pop();

				break;
            }
            case 5:
			{
				// print all reviews
                string rName;
                cout << "Restaurant name: ";
                getline(cin, rName);
                node* temp = ht.searchItem(rName);

                if (temp)
                {
                    temp->pq.print();
                }
                else
                {
                    cout << "no record found" << endl;
                }
                
				break;
			}
            case 6:
            {
                // output number of collisions
                cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
            }
            case 7:
            {
                // display table
                ht.displayTable();
                break;
            }
            case 8:
            {
                // quit
                return 1;
                break;
            }	
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
