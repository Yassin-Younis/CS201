// Yassin Younis (22101310)

#include <iostream>
#include "Team.h"

Team::Team(std::string inputName, const int inputYear) {
pTeamName = new std::string(inputName);
pYear = new int(inputYear);
m_noOfPlayers = 0;
pPlayers = new Player *[0]; //initialized with 0 to avoid mismatched delete operator.

}

Team::~Team() {
    delete pTeamName;
    delete pYear;
    delete[] pPlayers;
}

std::string Team::getName() {
    return *pTeamName;
}

/** Makes a bigger array with an extra pointer to the new player and makes pPlayers' point to that new array
 * Avoids copying of the player object since it only copies the pointer to that player object.
 * @param pointer to the player.*/
void Team::addPlayer(Player *player) {
    Player **temp = new Player *[m_noOfPlayers + 1];

    for (int i = 0; i < m_noOfPlayers; i++) {
        temp[i] = pPlayers[i];
    }
    temp[m_noOfPlayers] = player;
    delete[] pPlayers;
    pPlayers = temp;

    m_noOfPlayers++;
}

/** Makes a smaller array without the player to remove and makes pPlayers' point to that new array
 * Avoids copying of the player object since it only copies the pointer to that player object.
 * @param pointer to the player.*/
void Team::removePlayer(Player *player) {
    int playerIndex = findPlayer(player);
    Player **temp = new Player *[m_noOfPlayers - 1];

    int j = 0;
    for (int i = 0; i < m_noOfPlayers; i++) {
        if (i != playerIndex) {
            temp[j] = pPlayers[i];
            j++; // if i isn't equal to the index of the player to remove copy player and increment j;
        }
    }

    delete[] pPlayers;
    pPlayers = temp;

    m_noOfPlayers--;
}

/** Checks if a given jersey number is taken.
 * @param jersey number to check.
 * @return returns true if the number is take else false.*/
bool Team::isOccupied(int jersey) {
    for (int i = 0; i < m_noOfPlayers; i++) {
        if (pPlayers[i]->getJersey() == jersey) return true;
    }
    return false;
}

/** Calculates total salary by running thru player array.
* @return returns total salary of the team.*/
int Team::calcTotalSalary() {
    int total = 0;
    for (int i = 0; i < m_noOfPlayers; i++) {
        total += pPlayers[i]->getSalary();
    }
    return total;
}

/** Checks if player exists in team and returns his index if he does exist.
 * @param pointer to the player.
 * @return index of the player if exists otherwise return -1.*/
int Team::findPlayer(Player *player) {
    for (int i = 0; i < m_noOfPlayers; i++) {
        if (pPlayers[i] == player) {
            return i;
        }
    }
    return -1;
}

void Team::toBriefString() {
    std::cout << *pTeamName << ", " << *pYear << ", " << m_noOfPlayers << " players, " << calcTotalSalary()
              << " TL total salary\n";
}

void Team::toString() {
    std::cout << "Team: \n";
    toBriefString();
    std::cout << "Players: \n";
    if (m_noOfPlayers==0) std::cout << "None" << std::endl;
    for (int i = 0; i < m_noOfPlayers; i++) {
        pPlayers[i]->toBriefString();
    }
}