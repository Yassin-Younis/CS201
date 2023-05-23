//Yassin Younis 22101310

#ifndef MOVIERENTALSYSTEM_SUBSCRIBER_H
#define MOVIERENTALSYSTEM_SUBSCRIBER_H

// Import the necessary libraries
#include "Transaction.h"

// Define the Subscriber class
struct Subscriber {
    // The ID of the subscriber
    int id;

    // A list of the transactions associated with this subscriber
    LinkedList<Transaction> transactions;

    // The number of transactions associated with this subscriber
    int transactionCount;

    // Constructor for the Subscriber class
    explicit Subscriber(int id);

    // Overloaded comparison operators for comparing subscribers by ID
    bool operator<(Subscriber const &other) const;

    bool operator>(Subscriber const &other) const;

    bool operator==(Subscriber const &other) const;

    bool operator!=(Subscriber const &other) const;

    bool operator<=(Subscriber const &other) const;

    bool operator>=(Subscriber const &other) const;

    // Add a transaction to the list of transactions associated with this subscriber
    void addTransaction(Transaction *trans);

    // Check if this subscriber currently has any movies that have not been returned
    bool isRentee() const;

    int findTransaction(int movieId, int subscriberId, bool returned) const;

    // Check if there is a transaction associated with this subscriber for the given movie ID and return status
    bool isValidTransaction(int movieId, int subscriberId, bool returned) const;

    // Set the return status of a transaction associated with this subscriber for the given movie ID
    void returnMovie(int movieId, int subscriberId, bool returned) const;

    void printTransactions() const;
};


#endif //MOVIERENTALSYSTEM_SUBSCRIBER_H
