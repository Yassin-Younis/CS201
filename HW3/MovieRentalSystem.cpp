//Yassin Younis 22101310

#include "MovieRentalSystem.h"
#include <fstream>
#include <iostream>

MovieRentalSystem::MovieRentalSystem(const std::string movieInfoFileName, const std::string subscriberInfoFileName) {

    std::ifstream moviesInput(movieInfoFileName);
    std::ifstream subscribersInput(subscriberInfoFileName);

    // Check if the input files exist
    if (!moviesInput) {
        std::cout << "Input file " << movieInfoFileName << " does not exist" << std::endl;
        numSubscribers = numMovies = 0;
        return;
    }
    if (!subscribersInput) {
        std::cout << "Input file " << subscriberInfoFileName << " does not exist" << std::endl;
        numSubscribers = numMovies = 0;
        return;
    }

    // Read the number of movies
    moviesInput >> numMovies;
    // Read each movie
    for (int i = 0; i < numMovies; i++) {
        int movieId;
        int copies;
        // Read the movie id and number of copies
        moviesInput >> movieId;
        moviesInput >> copies;
        // Insert the movie into the linked list
        movies.add(new Movie(movieId, copies));
    }
    // Read the number of subscribers
    subscribersInput >> numSubscribers;
    // Read each subscriber
    for (int i = 0; i < numSubscribers; i++) {
        int subscriberId;
        // Read the subscriber id
        subscribersInput >> subscriberId;
        // Insert the subscriber into the linked list
        subscribers.add(new Subscriber(subscriberId));

    }
    std::cout << numSubscribers << " subscribers and " << numMovies << " movies have been loaded" << std::endl;
}

MovieRentalSystem::~MovieRentalSystem() = default;

void MovieRentalSystem::removeMovie(const int movieId) {
    // Check if the movie exists
    if (findMovie(movieId) < 0) {
        // If the movie does not exist, print an error message
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else if (isRented(movieId)) {
        // If the movie is rented, print an error message
        std::cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned"
                  << std::endl;
    } else {
        // If the movie exists and is not rented, remove it from the list of movies
        movies.remove(Movie(movieId));
        numMovies--;
        // Print a success message
        std::cout << "Movie " << movieId << " has been removed" << std::endl;
    }
}

void MovieRentalSystem::addMovie(const int movieId, const int numCopies) {
    // Check if the movie already exists
    if (findMovie(movieId) > -1) {
        // If the movie already exists, print an error message
        std::cout << "Movie " << movieId << " already exists" << std::endl;
    } else {
        // If the movie does not already exist, add it to the list of movies
        movies.add(new Movie(movieId, numCopies));
        numMovies++;
        // Print a success message
        std::cout << "Movie " << movieId << " has been added" << std::endl;
    }
}

void MovieRentalSystem::removeSubscriber(const int subscriberId) {
    // Check if the subscriber exists
    if (findSubscriber(subscriberId) < 0) {
        // If the subscriber does not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if (isRentee(subscriberId)) {
        // If the subscriber is currently renting a movie, print an error message
        std::cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned"
                  << std::endl;
    } else {
        // If the subscriber exists and is not currently renting a movie, remove them from the list of subscribers
        subscribers.remove(Subscriber(subscriberId));
        numSubscribers--;
        for (int i = 0; i < movies.getCount(); i++) {
            movies.get(i)->removeSubscriberFromTransactions(subscriberId);
        }
        // Print a success message
        std::cout << "Subscriber " << subscriberId << " has been removed" << std::endl;
    }
}

void MovieRentalSystem::rentMovie(const int subscriberId, const int movieId) {
    int movIndex = findMovie(movieId);
    int subIndex = findSubscriber(subscriberId);

    // Check if the subscriber and the movie exist
    if (movIndex < 0 && subIndex < 0) {
        // If the subscriber and the movie do not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << std::endl;
    } else if (movIndex < 0) {
        // If the movie does not exist, print an error message
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else if (subIndex < 0) {
        // If the subscriber does not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if (!isAvail(movieId)) {
        // If the movie is not available for renting, print an error message
        std::cout << "Movie " << movieId << " has no available copy for renting" << std::endl;
    } else {
        // If the subscriber and the movie exist and the movie is available for renting,
        // add a transaction for the rental to the movie and the subscriber
        movies.get(movIndex)->addTransaction(new Transaction(movieId, subscriberId, false));
        subscribers.get(subIndex)->addTransaction(new Transaction(movieId, subscriberId, false));
        // Print a success message
        std::cout << "Movie " << movieId << " has been rented by subscriber " << subscriberId << "" << std::endl;
    }
}


void MovieRentalSystem::returnMovie(const int subscriberId, const int movieId) {

    int movIndex = findMovie(movieId);
    int subIndex = findSubscriber(subscriberId);

    // Check if the subscriber and the movie exist
    if (movIndex < 0 && subIndex < 0) {
        // If the subscriber and the movie do not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << std::endl;
    } else if (movIndex < 0) {
        // If the movie does not exist, print an error message
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else if (subIndex < 0) {
        // If the subscriber does not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if (!isValidTransaction(movieId, subscriberId, false)) {
        // If the movie is not currently rented by the subscriber, print an error message
        std::cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << std::endl;
    } else {
        // If the subscriber and the movie exist and the movie is currently rented by the subscriber,
        // create a new transaction object in both movies and subscribers
        movies.get(movIndex)->returnMovie(movieId, subscriberId, false);
        subscribers.get(subIndex)->returnMovie(movieId, subscriberId, false);
        std::cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << std::endl;
    }
}

void MovieRentalSystem::showMoviesRentedBy(int subscriberId) const {
    int index = findSubscriber(subscriberId);
    // Check if the subscriber exists
    if (index < 0) {
        // If the subscriber does not exist, print an error message
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else {
        subscribers.get(index)->printTransactions();
    }
}

void MovieRentalSystem::showSubscribersWhoRentedMovie(const int movieId) const {
    int index = findMovie(movieId);
    // Check if the movie exists
    if (index < 0) {
        // If the movie does not exist, print an error message
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else {
        movies.get(index)->printTransactions();
    }
}

void MovieRentalSystem::showAllMovies() const {
    // Print a header for the list of movies
    std::cout << "Movies in the movie rental system:" << std::endl;

    // Iterate over the list of movies
    for (int i = 0; i < numMovies; i++) {
        // Print the ID and number of copies of each movie
        std::cout << movies.get(i)->id << " " << movies.get(i)->count << std::endl;
    }
}

void MovieRentalSystem::showAllSubscribers() const {
    // Print a header for the list of subscribers
    std::cout << "Subscribers in the movie rental system:" << std::endl;

    // Iterate over the list of subscribers
    for (int i = 0; i < numSubscribers; i++) {
        // Print the ID of each subscriber
        std::cout << subscribers.get(i)->id << std::endl;
    }
}

bool MovieRentalSystem::isRented(int movieId) {
    int index = findMovie(movieId);
    return movies.get(index)->isRented();
}

bool MovieRentalSystem::isRentee(int subscriberId) {
    int index = findSubscriber(subscriberId);
    return subscribers.get(index)->isRentee();
}

bool MovieRentalSystem::isAvail(int movieId) {
    int index = findMovie(movieId);
    return movies.get(index)->isAvail();
}

bool MovieRentalSystem::isValidTransaction(const int movieId, const int subscriberId, bool returned) {
    int subIndex = findSubscriber(subscriberId);
    int movIndex = findMovie(movieId);

    // Check if the transaction is valid for the subscriber and the movie
    bool b0 = subscribers.get(subIndex)->isValidTransaction(movieId, subscriberId, returned);
    bool b1 = movies.get(movIndex)->isValidTransaction(movieId, subscriberId, returned);

    // If there is a discrepancy between the subscriber and the movie, print an error message (for testing purposes)
    if (b0 != b1) {
        std::cout << "Syncing error" << std::endl;
    }

    // Return whether or not the transaction is valid
    if (b0) return true;
    else return false;

}

int MovieRentalSystem::findMovie(const int movieId) const {
    for (int i = 0; i < movies.getCount(); i++) {
        if (*(movies.get(i)) == Movie(movieId)) {
            return i;
        }
    }
    return -1;
}

int MovieRentalSystem::findSubscriber(int subscriberId) const {
    for (int i = 0; i < subscribers.getCount(); i++) {
        if (*(subscribers.get(i)) == Subscriber(subscriberId)) {
            return i;
        }
    }
    return -1;
}