//Yassin Younis 22101310

#ifndef MOVIERENTALSYSTEM_MOVIERENTALSYSTEM_H
#define MOVIERENTALSYSTEM_MOVIERENTALSYSTEM_H

#include <string>
#include "SortedLinkedList.h"
#include "Movie.h"
#include "Subscriber.h"

class MovieRentalSystem {

public:
    MovieRentalSystem(const std::string movieInfoFileName, const std::string subscriberInfoFileName);

    ~MovieRentalSystem();

    void removeMovie(const int movieId);

    void addMovie(const int movieId, const int numCopies);

    void removeSubscriber(const int subscriberId);

    void rentMovie(const int subscriberId, const int movieId);

    void returnMovie(const int subscriberId, const int movieId);

    void showMoviesRentedBy(const int subscriberId) const;

    void showSubscribersWhoRentedMovie(const int movieId) const;

    void showAllMovies() const;

    void showAllSubscribers() const;

private:

    LinkedList<Movie> movies;
    int numMovies;

    LinkedList<Subscriber> subscribers;
    int numSubscribers;

    bool isValidTransaction(const int movieId, const int subscriberId, bool returned);

    int findMovie(const int movieId) const;

    int findSubscriber(int subscriberId) const;

    bool isAvail(int movieId);

    bool isRented(int movieId);

    bool isRentee(int subscriberId);


};

#endif //MOVIERENTALSYSTEM_MOVIERENTALSYSTEM_H
