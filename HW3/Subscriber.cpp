//Yassin Younis 22101310

#include <iostream>
#include "Subscriber.h"

//Yassin Younis 22101310


// Constructor for the Subscriber class
Subscriber::Subscriber(int id) : id(id), transactionCount(0) {}

// Overloaded comparison operators for comparing subscribers by ID
bool Subscriber::operator<(Subscriber const &other) const {
    return (this->id < other.id);
}

bool Subscriber::operator>(Subscriber const &other) const {
    return (this->id > other.id);
}

bool Subscriber::operator==(Subscriber const &other) const {
    return (this->id == other.id);
}

bool Subscriber::operator!=(Subscriber const &other) const {
    return (this->id != other.id);
}

bool Subscriber::operator<=(Subscriber const &other) const {
    return (this->id <= other.id);
}

bool Subscriber::operator>=(Subscriber const &other) const {
    return (this->id >= other.id);
}

// Add a transaction to the list of transactions associated with this subscriber
void Subscriber::addTransaction(Transaction *trans) {
    transactions.add(trans);
    transactionCount++;
}

// Check if this subscriber currently has any movies that have not been returned
bool Subscriber::isRentee() const {
    // Iterate over the transactions associated with this subscriber
    for (int i = 0; i < transactions.getCount(); i++) {
        // If any of the transactions indicate that a movie has not been returned,
        // return true (indicating that the subscriber is currently renting a movie)
        if (!transactions.get(i)->returned) return true;
    }
    // If no transactions indicate that a movie has not been returned,
    // return false (indicating that the subscriber is not currently renting a movie)
    return false;
}

int Subscriber::findTransaction(const int movieId, const int subscriberId, bool returned) const {
    for (int i = 0; i < transactions.getCount(); i++) {
        // Check if the current transaction matches the given movie ID, subscriber ID, and returned flag
        if (*(transactions.get(i)) == Transaction(movieId, subscriberId, returned)) {
            return i;
        }
    }
    return -1;
}


// Check if there is a transaction associated with this subscriber for the given movie ID and return status
bool Subscriber::isValidTransaction(const int movieId, const int subscriberId, bool returned) const {
    return (findTransaction(movieId, subscriberId, returned) > -1);
}

// Set the return status of a transaction associated with this subscriber for the given movie ID
void Subscriber::returnMovie(const int movieId, const int subscriberId, bool returned) const {
    int index = findTransaction(movieId, subscriberId, returned);
    // Set the return status of the transaction with the given movie ID
    transactions.get(index)->setReturned();
}

void Subscriber::printTransactions() const {
    if (transactionCount > 0) std::cout << "Subscriber " << id << " has rented the following movies:" << std::endl;
    else std::cout << "Subscriber " << id << " has not rented any movies" << std::endl;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions.get(i)->returned) std::cout << transactions.get(i)->movieId << " returned" << std::endl;
        else std::cout << transactions.get(i)->movieId << " not returned" << std::endl;
    }
}
