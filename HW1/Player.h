// Yassin Younis (22101310)

#ifndef LMS_PLAYER_H
#define LMS_PLAYER_H
#include <string>

class Player {

private:

    std::string *pTeamName;
    std::string *pPlayerName;

    int *pJerseyNo;
    int *pSalary;

public:

    Player(std::string teamName, std::string playerName, int jersey, int salary);

    ~Player();

    std::string getName();

    std::string getTeam();

    int getSalary() ;

    int getJersey();

    void transferTeam(std::string teamName);

    void toString();

    void toBriefString();
};


#endif //LMS_PLAYER_H
