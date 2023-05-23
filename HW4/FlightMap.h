//Yassin Younis 22101310


#ifndef HPAIR_FLIGHTMAP_H
#define HPAIR_FLIGHTMAP_H

#include <string>
#include <list>
#include "stack"
#include <vector>
#include <map>

using namespace std;

struct Flight {
    int id;
    int price;
    string dept;
    string dest;
    Flight(int id, int price, string dest, string dept) : id(id), price(price), dest(dest), dept(dept) {}


    bool operator<(const Flight& other) const {
        return dest[0] < other.dest[0];
    }

    bool operator==(const Flight& other) const {
        return id == other.id;
    }

    bool operator>(const Flight& other) const {
        return dest[0] > other.dest[0];
    }

};

class FlightMap {
    public:
        FlightMap( string cityFile, string flightFile );
        ~FlightMap();
        void displayAllCities() const;
        void displayAdjacentCities( string cityName ) const;
        void displayFlightMap() const;
        void findFlights( string deptCity, string destCity ) const;

private:
        map<string, list<Flight>> flightGraph; //city name and its corresponding flights.
    bool stackContains(stack<string> stack1, string basicString) const;

    bool alreadyExists(vector<vector<Flight>> vector1, stack<Flight> stack1) const;
};


#endif //HPAIR_FLIGHTMAP_H
