//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Bid bid;
        Node *next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {

    head = nullptr;
    tail = nullptr;
    
    
    // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to null
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    Node *temp = new Node(bid);                 //Create new node
    if (head == nullptr) {                      //if head is null (list is empty)
        head = temp;                                //head and tail become new node
        tail = temp;                            
    }
    else {                                     //else
        tail->next = temp;                         //set current tail's next to point to new node
        tail = temp;                               //new node becomes tail
    }
    size = size + 1;                          //increase size count
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {

    Node* temp = new Node(bid);                 //Create new node
    if (head == nullptr) {                      //if head is null (list is empty)
        head = temp;                                //head and tail become new node
        tail = temp;
    }
    else {                                      //else
        temp->next = head;                          //new nodes next point's to current head
        head = temp;                                //head becomes new node
    }
    size = size + 1;                            //increase size count
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {

    Node* pos = head;                                                                                                   //Start at the head of the list
    while (pos != nullptr) {                                                                                            //While the list is not finished
        Bid current = pos->bid;                                                                                         //Create local bid from current iteration's bid
        cout << current.bidId << "| " << current.title << "| " << current.fund << "| " << current.amount << endl;       //Output current iteration's bid information
        pos = pos->next;                                                                                                //move to the next list item
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (5): Implement remove logic
    Node* current = head;                                                       //create new node to traverse list, start at head
    Node* prev = head;                                                          //create node to temporarily maintain node behind current, have it also start at head
    Bid searchBid;                                                              //create new bid to store current iterations bid
    while (current != nullptr) {                                                //traverse through to the end of the list
        searchBid = current->bid;                                               //store current bids information in searchBid for comparison
        if (searchBid.bidId == bidId && current == head) {                      //if bidId is matching and the matching bid is the head
            head = current->next;                                                   //head becomes the next bid in the list, removing the current bid
            size = size - 1;                                                        //decrease size count
            return;                                                                 //return
        }
        else if (searchBid.bidId == bidId && current == tail) {                 //else if bidId is matching and matching bid is the tail
            tail = prev;                                                            //tail now becomes the previous bid
            prev->next = nullptr;                                                   //previous bid now points to null removing the current bid
            size = size - 1;                                                        //decrease size count
            return;                                                                 //return
        }
        else if (searchBid.bidId == bidId) {                                    //else if bidId matches and was not the head or the tail
                prev->next = current->next;                                         //previous bid now points to current bid's next, removing current bid
                size = size - 1;                                                    //decrease size count
                return;                                                             //return
            }
        
        /*Maintanence of current and prev nodes pointers to traverse through list*/

        if (current == head) {                                                  //if current is equal to head              
            prev = head;                                                            //prev becomes head
        }
        else {                                                                  //else prev will be the bid behind current
            prev = prev->next;                                                      //make prev the next node
        }
        current = current->next;                                                //make current the next node
    }
        
    }



/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (6): Implement search logic
    
    Node* current = head;                           //start at the head to traverse list
    Bid searchBid = Bid();                                  //creation of bid variable to store bid being searched
    while (current != nullptr) {                    //traverse through to the end of the list
        searchBid = current->bid;                   //searchBid is equal to the current iteration's bid
        if (searchBid.bidId == bidId) {             //if bidId's match 
            return searchBid;                           //return the bid
        }
        current = current->next;                    //if they do not match current becomes next node
    }
    searchBid = Bid();                             //the end of the list was reached without a match, set searchBid equal to an empty bid
    return searchBid;                              //return empty bid
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98129";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
