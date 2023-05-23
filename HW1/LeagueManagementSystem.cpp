// Yassin Younis (22101310)

#include <iostream>
#include "LeagueManagementSystem.h"

LeagueManagementSystem::LeagueManagementSystem() {
    m_noOfPlayers = 0;
    m_noOfTeams = 0;
    pPlayers = new Player *[0]; //initialized with 0 to avoid mismatched delete operator.
    pTeams = new Team *[0];
}

LeagueManagementSystem::~LeagueManagementSystem() {
    for (int i = 0; i < m_noOfTeams; i++) {
        delete pTeams[i]; //delete each team.
    }
    delete[] pTeams; //delete all pointers to the teams.

    for (int i = 0; i < m_noOfPlayers; i++) {
        delete pPlayers[i]; //delete each player.
    }
    delete[] pPlayers; //delete all pointers to the players.
}


/** adds team to pTeams.
 * @param teamName for the new team.
 * @param year new team was created.*/
void LeagueManagementSystem::addTeam(std::string teamName, const int year) {
    int teamIndex = findTeam(teamName);
    if (teamIndex > -1) std::cout << "Cannot add team. Team " << teamName << " already exists." << std::endl;
    else {
        Team **temp = new Team *[m_noOfTeams + 1];

        for (int i = 0; i < m_noOfTeams; i++) {
            temp[i] = pTeams[i];
        }

        temp[m_noOfTeams] = new Team(teamName, year);

        delete[] pTeams; //deallocate old array
        pTeams = temp; // old array now points to new array with extra team

        m_noOfTeams++;
        std::cout << "Added team " << teamName << "." << std::endl;
    }
}

/** removes team from PTeams.
 * @param teamName to remove.*/
void LeagueManagementSystem::removeTeam(const std::string teamName) {
    int teamIndex = findTeam(teamName);
    if (teamIndex < 0) std::cout << "Cannot remove team. Team " << teamName << " does not exist." << std::endl;
    else {
        Team **temp = new Team *[m_noOfTeams - 1];
        int j = 0;
        for (int i = 0; i < m_noOfTeams; i++) {
            if (i != teamIndex) {
                temp[j] = pTeams[i];
                j++; // if i isn't equal to the index of the pTeamName to remove copy pTeamName and increment j;
            }
        }

        for (int i=0; i<m_noOfPlayers; i++) {
            if (pPlayers[i]->getTeam()==teamName) {
                removePlayer(teamName, pPlayers[i]->getName()); //delete all players in team too.
            }
        }

        delete pTeams[teamIndex];
        delete[] pTeams;

        pTeams = temp;
        m_noOfTeams--;
        std::cout << "Removed team " << teamName << "." <<  std::endl;
    }
}

/** adds player to pPlayers and to pPlayers of their respective team
 * @param teamName to which to add the player to.
 * @param playerName.
 * @param jerseyNo for the new player.
 * @param salary for the new player.
 * @param year new team was created.*/
void LeagueManagementSystem::addPlayer(const std::string teamName, const std::string playerName, const int jersey,
                                       const int salary) {
    int playerIndex = findPlayer(playerName);
    int teamIndex = findTeam(teamName);

    if (playerIndex > -1) std::cout << "Cannot add player. Player " << playerName << " already exists." << std::endl;
    else if (teamIndex < 0) std::cout << "Cannot add player. Team " << teamName << " does not exist." << std::endl;
    else if ((pTeams[teamIndex]->isOccupied(jersey)))
        std::cout << "Cannot add player. Jersey number " << jersey
                  << " already exists in team " << teamName << "." << std::endl;
    else {

        Player **temp = new Player *[m_noOfPlayers + 1];

        for (int i = 0; i < m_noOfPlayers; i++) {
            temp[i] = pPlayers[i];
        }

        Player *tempPlayer = new Player(teamName, playerName, jersey, salary);

        temp[m_noOfPlayers] = tempPlayer;
        pTeams[teamIndex]->addPlayer(tempPlayer);

        delete[] pPlayers;
        pPlayers = temp;

        m_noOfPlayers++;
        std::cout << "Added player " << playerName << " to team " << teamName << "." << std::endl;
    }
}

/** removes player from pPlayers and pPlayers from his respective team.
 * @param teamName to remove player from.
 * @param playerName of player to remove.*/
void LeagueManagementSystem::removePlayer(const std::string teamName, const std::string playerName) {
    int playerIndex = findPlayer(playerName);
    int teamIndex = findTeam(teamName);

    if (teamIndex < 0) std::cout << "Cannot remove player. Team " << teamName << " does not exist." << std::endl;
    else if (playerIndex < 0 || (pPlayers[playerIndex]->getTeam() != teamName))
        std::cout << "Cannot remove player. Player " << playerName << " does not exist." << std::endl;
    else {
        Player **temp = new Player *[m_noOfPlayers - 1];

        int j = 0;
        for (int i = 0; i < m_noOfPlayers; i++) {
            if (i != playerIndex) {
                temp[j] = pPlayers[i];
                j++; // if i isn't equal to the index of the player to remove copy player and increment j;
            }
        }

        pTeams[teamIndex]->removePlayer(pPlayers[playerIndex]);
        delete pPlayers[playerIndex]; //actual deletion will be handled by this class
        delete[] pPlayers;
        pPlayers = temp;


        m_noOfPlayers--;
        std::cout << "Removed player " << playerName << " from team " << teamName << "." << std::endl;
    }
}

/** removes pointer of a player from departTeam and add that pointer to arriveTeamName.
 * @param playerName to transfer.
 * @param arriveTeamName to add player to.
 * @param departTeamName of player to remove.*/
void LeagueManagementSystem::transferPlayer(const std::string playerName, const std::string departTeamName,
                                            const std::string arriveTeamName) {
    int playerIndex = findPlayer(playerName);
    int departTeamIndex = findTeam(departTeamName);
    int arriveTeamIndex = findTeam(arriveTeamName);

    if (departTeamIndex < 0)
        std::cout << "Cannot transfer player. Team " << departTeamName << " does not exist." << std::endl;
    else if (arriveTeamIndex < 0)
        std::cout << "Cannot transfer player. Team " << arriveTeamName << " does not exist." << std::endl;
    else if (playerIndex < 0)
        std::cout << "Cannot transfer player. Player " << playerName << " does not exist." << std::endl;
    else if (pTeams[arriveTeamIndex]->isOccupied(pPlayers[playerIndex]->getJersey()))
        std::cout << "Cannot transfer player. Jersey number " << pPlayers[playerIndex]->getJersey()
                  << "  already exists in team " << arriveTeamName << "." << std::endl;

    else {
        pTeams[departTeamIndex]->removePlayer((pPlayers[playerIndex]));
        pTeams[arriveTeamIndex]->addPlayer((pPlayers[playerIndex]));
        pPlayers[playerIndex]->transferTeam(arriveTeamName);
        std::cout << "Transferred player " << playerName << " from team " << departTeamName << " to team "
                  << arriveTeamName << "." << std::endl;
    }

}

void LeagueManagementSystem::showAllTeams() const {
    std::cout << "Teams in the league management system:" <<std::endl;
    if (m_noOfTeams == 0) {
        std::cout << "None\n";
    }
    for (int i = 0; i < m_noOfTeams; i++) {
        pTeams[i]->toBriefString();
    }
}

void LeagueManagementSystem::showTeam(const std::string name) const {
    int teamIndex = findTeam(name);
    if (teamIndex < 0) {
        std::cout << "Team " << name << " does not exist.\n";
    } else pTeams[teamIndex]->toString();
}

void LeagueManagementSystem::showPlayer(std::string name) const {
    int playerIndex = findPlayer(name);
    if (playerIndex < 0) {
        std::cout << "Player " << name << " does not exist.\n";
    } else pPlayers[playerIndex]->toString();
}

/** Checks if team exists in league and returns its index if it does exist.
 * @param team name.
 * @return index of the team if exists otherwise return -1.*/
int LeagueManagementSystem::findTeam(const std::string name) const {
    for (int i = 0; i < m_noOfTeams; i++) {
        if (pTeams[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}

/** Checks if player exists in league and returns his index if he does exist.
 * @param player name.
 * @return index of the player if exists otherwise return -1.*/
int LeagueManagementSystem::findPlayer(const std::string name) const {
    for (int i = 0; i < m_noOfPlayers; i++) {
        if (pPlayers[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}





