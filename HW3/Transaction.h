//Yassin Younis 22101310

#ifndef MOVIERENTALSYSTEM_TRANSACTION_H
#define MOVIERENTALSYSTEM_TRANSACTION_H

// Import the necessary libraries
#include "SortedLinkedList.h"

// Define the Transaction structure
struct Transaction {

    bool sortByMovie;

    // The ID of the movie associated with this transaction
    int movieId;

    // The ID of the subscriber associated with this transaction
    int subscriberId;

    // A flag indicating whether the movie associated with this transaction has been returned or not
    bool returned;

    // Default constructor for the Transaction structure
    Transaction();

    // Constructor for the Transaction structure with the given movie ID and subscriber ID
    Transaction(int movieId, int subscriberId);

    // Constructor for the Transaction structure with the given movie ID, subscriber ID, and return status
    Transaction(int movieId, int subscriberId, bool returned);


    // Overloaded comparison operators for comparing transactions by movie ID
    bool operator<(Transaction const &other) const;

    bool operator>(Transaction const &other) const;

    // Overloaded equality operator for comparing transactions by movie ID, subscriber ID, and return status
    bool operator==(Transaction const &other) const;

    // Overloaded inequality operator for comparing transactions by movie ID, subscriber ID, and return status
    bool operator!=(Transaction const &other) const;

    // Overloaded comparison operators for comparing transactions by movie ID
    bool operator<=(Transaction const &other) const;

    bool operator>=(Transaction const &other) const;

    // Setter function for the returned flag of a transaction
    void setReturned();
};

#endif //MOVIERENTALSYSTEM_TRANSACTION_H