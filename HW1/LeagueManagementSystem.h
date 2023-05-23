// Yassin Younis (22101310)

#ifndef LMS_LEAGUEMANAGEMENTSYSTEM_H
#define LMS_LEAGUEMANAGEMENTSYSTEM_H

#include "Team.h"
#include "iostream"

class LeagueManagementSystem {
public:

    LeagueManagementSystem();
    ~LeagueManagementSystem();

    void addTeam( const std::string name, const int year );
    void removeTeam( const std::string name );

    void addPlayer( const std::string teamName, const std::string playerName, const int jersey, const int salary );
    void removePlayer( const std::string teamName, const std::string playerName );

    void transferPlayer( const std::string playerName, const std::string departTeamName, const std::string arriveTeamName );

    void showAllTeams() const;
    void showTeam( const std::string name ) const;
    void showPlayer( const std::string name ) const;

private:

    Team** pTeams;
    int m_noOfTeams;

    Player** pPlayers;
    int m_noOfPlayers;

    int findTeam(std::string teamName) const;
    int findPlayer(std::string playerName) const;

};


#endif //LMS_LEAGUEMANAGEMENTSYSTEM_H
