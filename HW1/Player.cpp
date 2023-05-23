// Yassin Younis (22101310)

#include <iostream>
#include "Player.h"

Player::Player(std::string teamName, std::string playerName, int jersey, int salary) {
    pPlayerName = new std::string(playerName);
    pTeamName = new std::string(teamName);
    pSalary = new int(salary);
    pJerseyNo = new int(jersey);
}

Player::~Player() {
    delete pPlayerName;
    delete pTeamName;
    delete pSalary;
    delete pJerseyNo;
}

std::string Player::getName() {
    return *pPlayerName;
}

std::string Player::getTeam() {
    return *pTeamName;
}

int Player::getSalary() {
    return *pSalary;
}

int Player::getJersey() {
    return *pJerseyNo;
}

void Player::transferTeam(std::string teamName) {
    *pTeamName = teamName;
}

void Player::toString() {
    std::cout << "Player: \n";
    toBriefString();
    std::cout << "Plays in team " << *pTeamName << ".\n";
}

void Player::toBriefString() {
    std::cout << *pPlayerName << ", jersey " << *pJerseyNo << ", " << *pSalary << " TL salary\n";
}
