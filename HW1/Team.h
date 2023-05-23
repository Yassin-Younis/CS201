// Yassin Younis (22101310)

#ifndef LMS_TEAM_H
#define LMS_TEAM_H

#include "Player.h"
#include <string>

class Team {
private:

    std::string *pTeamName;
    int *pYear;

    Player **pPlayers;
    int m_noOfPlayers;

public:

    Team(std::string inputName, int inputYear);
    ~Team();

    std::string getName();

    void addPlayer(Player *player);
    void removePlayer(Player *player);

    bool isOccupied(int jersey);

    int calcTotalSalary();

    int findPlayer(Player *player);

    void toBriefString();
    void toString();
};


#endif //LMS_TEAM_H
