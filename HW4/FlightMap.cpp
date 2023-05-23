//Yassin Younis 22101310

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include "FlightMap.h"

FlightMap::FlightMap(string cityFile, string flightFile) {

    std::ifstream cityInput(cityFile);
    std::ifstream flightInput(flightFile);

    // Check if the input files exist
    if (!cityInput) {
        std::cout << "Input file " << cityFile << " does not exist" << std::endl;
        return;
    }
    if (!flightInput) {
        std::cout << "Input file " << flightFile << " does not exist" << std::endl;
        return;
    }

    int numCities = 0;
    int numFlights = 0;

    string city;
    while (cityInput >> city) {
        // Insert an empty vector of edges for each city in the map
        flightGraph[city] = list<Flight>();
        numCities++;
    }


    string line;
    while (flightInput >> line) {
        string origin;
        int i = 0;

        while (line[i] != ';') {
            origin += line[i];
            i++;
        }
        string dest;
        i++; //skip ;
        while (line[i] != ';') {
            dest += line[i];
            i++;
        }

        string id, cost;

        i++; //skip ;
        while (line[i] != ';') {
            id += line[i];
            i++;
        }

        i++; //skip ;
        while (i<line.size()) {
            cost += line[i];
            i++;
        }

        // Insert an edge representing the flight into the adjacency list for the origin city
        flightGraph[origin].push_back(Flight(stoi(id), stoi(cost), dest, origin));
        numFlights++;
    }

    for (auto it = flightGraph.begin(); it != flightGraph.end(); ++it) {
        it->second.sort();
    }

    std::cout << numCities << " cities and " << numFlights << " flights have been loaded" << std::endl;
}

FlightMap::~FlightMap() {

}

void FlightMap::displayAllCities() const {

    cout << "The list of the cities that HPAir serves is given below:" << endl;

    for (auto it = flightGraph.begin(); it != flightGraph.end(); ++it) {
        std::cout << it->first << ", ";
    }
    std::cout << std::endl;
}

void FlightMap::displayAdjacentCities(string cityName) const {
    cout << "The cities adjacent to "<< cityName<<" are:" << endl;
    cout << cityName << " -> ";
    for (const auto& flight : flightGraph.at(cityName)) {
        cout << flight.dest << ", ";
    }
    cout << endl;
}

void FlightMap::displayFlightMap() const {
    cout << "The whole flight map is given below:" << endl;
    for (auto it = flightGraph.begin(); it != flightGraph.end(); ++it) {
        string cityName = it->first;
        cout << cityName << " -> ";
        for (const auto& flight : flightGraph.at(cityName)) {
            cout << flight.dest << ", ";
        }
        cout << endl;
    }
    std::cout << std::endl;
}

void FlightMap::findFlights(string deptCity, const string destCity) const {

    cout << "Request is to fly from " << deptCity << " to " << destCity <<":" << endl;
    stack<string> stk;
    stack<Flight> fltStk;
    vector<string> visitedCities;
    vector<vector<Flight>> solutions;
    vector<int> respectivePrices;
    vector<string> visitedDestFrom;
    stk.push(deptCity);
    visitedCities.push_back(deptCity);
    map<string ,vector<string>> visitedByCity;

    while (!stk.empty()) {

        list<Flight> availableFlights = flightGraph.at(stk.top());

        bool foundNext = false;

        for (auto it = availableFlights.begin(); it != availableFlights.end() && !foundNext; ++it) {
            if ( !stackContains(stk, it->dest) && std::find(visitedByCity[it->dept].begin(), visitedByCity[it->dept].end(), it->dest) == visitedByCity[it->dept].end()) { //vector doesn't contain city //std::find(visitedCities.begin(), visitedCities.end(), it->dest) == visitedCities.end() ||
                if (it->dest!=destCity) {
                    stk.push(it->dest);
                    fltStk.push(*it);
                    visitedByCity[it->dept].push_back(it->dest);
                    visitedCities.push_back(it->dest);
                    foundNext = true;
                }
                else if (!alreadyExists(solutions, fltStk)) {
                    fltStk.push(*it);
                    stk.push(it->dest);
                    vector<Flight> solution;
                    int cost = 0;
                    std::stack<Flight> copy(fltStk);
                    visitedDestFrom.push_back(it->dept);
                    while (!copy.empty()) {
                        solution.push_back(copy.top());
                        cost += copy.top().price;
                        copy.pop();
                    }
                    solutions.push_back(solution);
                    respectivePrices.push_back(cost);
                }
            }
        }
        if (!foundNext && !stk.empty()) {
            stk.pop();
            if (!fltStk.empty()) fltStk.pop();
        }
        if (stk.empty()) {
            for (int i=0; i<respectivePrices.size(); i++) { //sort by cheapest
                for (int j=i; j<respectivePrices.size(); j++) {
                    if (respectivePrices[j] < respectivePrices[i]) {
                        int tempPrice = respectivePrices[i];
                        vector<Flight> tempSolution = solutions[i];

                        respectivePrices[i] = respectivePrices[j];
                        respectivePrices[j] = tempPrice;

                        solutions[i] = solutions[j];
                        solutions[j] = tempSolution;
                    }
                }
            }

            if (solutions.size()==0) cout << "Sorry. HPAir does not fly from "<< deptCity <<" to "<< destCity <<"." << endl;

            for (int i=0; i<solutions.size(); i++) {
                for (int j=solutions[i].size()-1; j>-1; j--) {
                    cout << "Flight #"<<solutions[i][j].id<<" from "<< solutions[i][j].dept<<" to "<< solutions[i][j].dest<<", Cost: "<< solutions[i][j].price<<" TL" << endl;
                }
                cout << "Total Cost: "<< respectivePrices[i] <<" TL" << endl;
            }
            return;
        }
    }


}

bool FlightMap::stackContains(stack<string> stk, string entry) const {
    std::stack<string> copy(stk);
    while (!copy.empty()) {
        if (copy.top()==entry) return true;
        copy.pop();
    }
    return false;
}

bool FlightMap::alreadyExists(vector<vector<Flight>> solutions, stack<Flight> solution) const {
    for (int i=0; i<solutions.size(); i++) {
        int count = 0;

        std::stack<Flight> copy(solution);
        for (int j=1; j<solutions[i].size() && !copy.empty(); j++) {
            if (solutions[i][j]==copy.top()) count++;
            copy.pop();
        }
        if (count==solutions[i].size()-1) return true;
    }
    return false;
}
