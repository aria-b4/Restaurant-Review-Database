#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b) // swaps two elements within heapArr[]
{
    ReviewInfo *temp = a;
    a = b;
    b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap) // constructor, creates new heapArr on the heap, initializes capacity to specified amount, and initializes currentSize to 0
{
    heapArr = new ReviewInfo[cap];
    capacity = cap;
    currentSize = 0;
}

/*
Destructor
*/
PriorityQ::~PriorityQ() // the only memory created on the heap is heapArr, so we can delete that and all memory is freed
{
    delete [] heapArr;
    heapArr = nullptr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    if (index == 0) // if index is 0 it does not have a parent so return itself
    {
        return 0;
    }
    else if (index % 2 == 0) // if it is even it is a right child so we minus 2 and divide by 2 to get to the parent
    {
        return (index - 2) / 2;
    }
    else // if it is not even (odd) then it is a left child so we minus 1 and divide by 2 to get to the parent
    {
        return (index - 1) / 2;
    }
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index) // the left child of a node is 2 times the index plus 1
{
    return (2 * index) + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index) // the right child of a node is 2 times the index plus 2
{
    return (2 * index) + 2;
}

void PriorityQ::peek()
{
    if (currentSize == 0) // if size is 0 it is empty, output no record
    {
        cout << "no record found" << endl;
    }
    else // otherwise peek
    {
        cout << "Restaurant: " << heapArr->restaurantName << endl;
        cout << "Customer: " << heapArr->customer << endl;
        cout << "Review: " << heapArr->review << endl;
        cout << "Time: " << heapArr->time << endl;
    }
}

void PriorityQ::heapify(int i)
{
    int left = leftChild(i);
    int right = rightChild(i);
    int max = i;

    if (heapArr[left].time > heapArr[max].time && left <= currentSize) // if left child is greater than current node set max to left
    {
        max = left;
    }
    
    if (heapArr[right].time > heapArr[max].time && right <= currentSize) // if right child is bigger than current node set max to right
    {
        max = right;
    }

    if (max != i) // if max is not at the original index passed, swap largest node with current node and call function again
    {
        swap(heapArr[i], heapArr[max]);
        heapify(max);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if (currentSize != capacity) // if capacity is not reached
    {
        heapArr[currentSize] = restaurant; // add new review to queue
        currentSize++; // increment size
        int i = currentSize - 1; // get index that item was just inserted at
        while (i != 0 && heapArr[parent(i)].time < heapArr[i].time) // while loop that swaps the inserted element and its parent until the inserted element has been inserted properly
        {
            swap(heapArr[parent(i)], heapArr[i]);
            i = parent(i);
        }
    }
    else // if capacity reached do not insert
    {
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for (int i = 0; i < currentSize; i++) // for loop that goes through and prints all review infos
    {
        cout << "\tCustomer: " << heapArr[i].customer << endl;
        cout << "\tReview: " << heapArr[i].review << endl;
        cout << "\tTime: " << heapArr[i].time << endl;
        cout << "\t=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    heapArr[0] = heapArr[currentSize - 1]; // set first element to last element in array
    currentSize--; // decrement currentSize
    heapify(0); // call heapify on root to fix any issues
}
