//Yassin Younis 22101310

#include "Transaction.h"

// Default constructor for the Transaction structure
Transaction::Transaction() : movieId(0), subscriberId(0), returned(false), sortByMovie(true) {}

// Constructor for the Transaction structure with the given movie ID and subscriber ID
Transaction::Transaction(int movieId, int subscriberId) : movieId(movieId), subscriberId(subscriberId), returned(false),
                                                          sortByMovie(true) {}

// Constructor for the Transaction structure with the given movie ID, subscriber ID, and return status
Transaction::Transaction(int movieId, int subscriberId, bool returned) : movieId(movieId), subscriberId(subscriberId),
                                                                         returned(returned), sortByMovie(true) {}

// Overloaded comparison operators for comparing transactions by movie ID
bool Transaction::operator<(Transaction const &other) const {
    if (sortByMovie) return (this->movieId < other.movieId);
    else return (this->subscriberId < other.subscriberId);
}

bool Transaction::operator>(Transaction const &other) const {
    if (sortByMovie) return (this->movieId > other.movieId);
    else return (this->subscriberId > other.subscriberId);
}

// Overloaded equality operator for comparing transactions by movie ID, subscriber ID, and return status
bool Transaction::operator==(Transaction const &other) const {
    return (this->subscriberId == other.subscriberId) && (this->movieId == other.movieId) &&
           (this->returned == other.returned);
}

// Overloaded inequality operator for comparing transactions by movie ID, subscriber ID, and return status
bool Transaction::operator!=(Transaction const &other) const {
    return (this->subscriberId != other.subscriberId) && (this->movieId != other.movieId) &&
           (this->returned != other.returned);
}

// Overloaded comparison operators for comparing transactions by movie ID
bool Transaction::operator<=(Transaction const &other) const {
    if (sortByMovie) return (this->movieId <= other.movieId);
    else return (this->subscriberId <= other.subscriberId);
}

bool Transaction::operator>=(Transaction const &other) const {
    if (sortByMovie) return (this->movieId >= other.movieId);
    else return (this->subscriberId >= other.subscriberId);
}

// Setter function for the returned flag of a transaction
void Transaction::setReturned() {
    returned = true;
}

