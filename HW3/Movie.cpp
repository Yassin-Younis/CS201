//Yassin Younis 22101310

#include <iostream>
#include "Movie.h"


// Construct a Movie object with the specified ID and number of copies
Movie::Movie(int in, int cnt) : id(in), count(cnt) {}

// Construct a Movie object with the specified ID
Movie::Movie(int id) : id(id), count(0) {}

// Check if there is a transaction associated with this subscriber for the given movie ID and return status
bool Movie::isValidTransaction(const int movieId, const int subscriberId, bool returned) const {
    return (findTransaction(movieId, subscriberId, returned) > -1);
}

int Movie::findTransaction(const int movieId, const int subscriberId, bool returned) const {
    for (int i = 0; i < transactions.getCount(); i++) {
        // Check if the current transaction matches the given movie ID, subscriber ID, and returned flag
        if (*(transactions.get(i)) == Transaction(movieId, subscriberId, returned)) {
            return i;
        }
    }
    return -1;
}

// Returns true if at least one copy of the movie is available for rent, false otherwise
bool Movie::isAvail() const {
    int tempCnt = 0; //no of unreturned transactions
    // Iterate over the transactions for this movie
    for (int i = 0; i < transactions.getCount(); i++) {
        // If the transaction has not been returned, increment tempCnt
        if (!transactions.get(i)->returned) tempCnt++;
    }
    // If tempCnt is less than the number of copies of the movie, return true
    if (tempCnt < count) return true;
    // Otherwise, return false
    return false;
}

// Returns true if at least one copy of the movie is currently rented, false otherwise
bool Movie::isRented() const {
    // Iterate over the transactions for this movie
    for (int i = 0; i < transactions.getCount(); i++) {
        // If the transaction has not been returned, return true
        if (!transactions.get(i)->returned) return true;
    }
    // Otherwise, return false
    return false;
}

// Adds a Transaction to the list of transactions for this movie
void Movie::addTransaction(Transaction *trans) {
    trans->sortByMovie = false;
    transactions.add(trans);
}

// Set the return status of a transaction associated with this subscriber for the given movie ID
void Movie::returnMovie(const int movieId, const int subscriberId, bool returned) const {
    int index = findTransaction(movieId, subscriberId, returned);
    // Set the return status of the transaction with the given movie ID
    transactions.get(index)->setReturned();
}

// Overload the comparison operators for comparing two Movie objects
bool Movie::operator<(Movie const &other) const {
    return (this->id < other.id);
}

bool Movie::operator>(Movie const &other) const {
    return (this->id > other.id);
}

bool Movie::operator==(Movie const &other) const {
    return (this->id == other.id);
}

bool Movie::operator!=(Movie const &other) const {
    return (this->id != other.id);
}

bool Movie::operator<=(Movie const &other) const {
    return (this->id <= other.id);
}

bool Movie::operator>=(Movie const &other) const {
    return (this->id >= other.id);
}

void Movie::printTransactions() const {

    if (transactions.getCount() > 0)
        std::cout << "Movie " << id << " has been rented by the following subscribers:" << std::endl;
    else std::cout << "Movie " << id << " has not been rented by any subscriber" << std::endl;
    for (int i = 0; i < transactions.getCount(); i++) {
        if (transactions.get(i)->returned) std::cout << transactions.get(i)->subscriberId << " returned" << std::endl;
        else std::cout << transactions.get(i)->subscriberId << " not returned" << std::endl;
    }
}

void Movie::removeSubscriberFromTransactions(const int subscriberId) {
    // Create a list to store the transactions that should be removed
    LinkedList<Transaction> transactionsToRemove;

    // Iterate over the list of transactions
    for (int i = 0; i < transactions.getCount(); i++) {
        // Get the current transaction
        Transaction *currentTransaction = transactions.get(i);

        // If the current transaction is associated with the specified subscriber ID,
        // add it to the list of transactions to remove
        if (currentTransaction->subscriberId == subscriberId) {
            transactionsToRemove.add(new Transaction(currentTransaction->movieId, currentTransaction->subscriberId,
                                                     currentTransaction->returned));
        }
    }

    // Iterate over the list of transactions to remove
    for (int i = 0; i < transactionsToRemove.getCount(); i++) {
        // Get the current transaction to remove
        Transaction *currentTransaction = transactionsToRemove.get(i);

        // Remove the current transaction from the original list of transactions
        transactions.remove(*currentTransaction);
    }
}


