//Yassin Younis 22101310

#ifndef MOVIERENTALSYSTEM_MOVIE_H
#define MOVIERENTALSYSTEM_MOVIE_H

#include "Transaction.h"

struct Movie {

    int id;
    int count;

    Movie(int in, int cnt);

    explicit Movie(int id);

    LinkedList<Transaction> transactions;

    bool isValidTransaction(int movieId, int subscriberId, bool returned) const;

    int findTransaction(int movieId, int subscriberId, bool returned) const;

    bool isAvail() const;

    bool isRented() const;

    void addTransaction(Transaction *trans);

    void returnMovie(int movieId, int subscriberId, bool returned) const;

    void printTransactions() const;

    void removeSubscriberFromTransactions(int subscriberId);

    bool operator<(Movie const &other) const;

    bool operator>(Movie const &other) const;

    bool operator==(Movie const &other) const;

    bool operator!=(Movie const &other) const;

    bool operator<=(Movie const &other) const;

    bool operator>=(Movie const &other) const;

};


#endif //MOVIERENTALSYSTEM_MOVIE_H
