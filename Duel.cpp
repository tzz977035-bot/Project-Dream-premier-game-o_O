#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
struct Player {
    string name;
    string position; 
    int stat;        
};

struct Team {
    string teamName;
    vector<Player> players;
    string buffedPosition;    
    int formationBuffPercent; 
};
////// 2
float getMidfieldAvg(const Team& t) {
    int totalStat = 0;
    int count = 0;
    for (const auto& p : t.players) {
        if (p.position == "MF") {
            totalStat += p.stat;
            count++;
        }
    }
    if (count == 0) return 0;
    return (float)totalStat / count;
}
Player getRandomPlayer(const Team& t, string targetPosition) {
    vector<Player> filteredPlayers;
    for (const auto& p : t.players) {
        if (p.position == targetPosition) {
            filteredPlayers.push_back(p);
        }
    }
      if (filteredPlayers.empty()) {
        return {"Unknown", targetPosition, 0}; 
    }
    
    int randomIndex = rand() % filteredPlayers.size();
    return filteredPlayers[randomIndex];
}
bool duel1v1(const Player& attacker, const Player& defender, const Team& attackingTeam, const Team& defendingTeam) {
    int attackerChance = 50;
    int defenderChance = 50;
     if (attackingTeam.buffedPosition == attacker.position) {
        attackerChance += attackingTeam.formationBuffPercent;
        defenderChance -= attackingTeam.formationBuffPercent;
    }
    if (defendingTeam.buffedPosition == defender.position) {
        defenderChance += defendingTeam.formationBuffPercent;
        attackerChance -= defendingTeam.formationBuffPercent;
    }
    int statDiff = attacker.stat - defender.stat;
    if (abs(statDiff) >= STAT_DIFF_THRESHOLD) {
        if (statDiff > 0) {
            attackerChance += STAT_DIFF_BONUS_PERCENT;
            defenderChance -= STAT_DIFF_BONUS_PERCENT;
        } else {
            defenderChance += STAT_DIFF_BONUS_PERCENT;
            attackerChance -= STAT_DIFF_BONUS_PERCENT;
        }
    }
    if (attackerChance < 0) attackerChance = 0;
    if (attackerChance > 100) attackerChance = 100;

    int roll = (rand() % 100) + 1;
    cout << "      [Win Chance: " << attacker.name << " " << attackerChance << "% | " 
         << defender.name << " " << (100 - attackerChance) << "%] -> Dice Roll: " << roll << endl;
    
    return (roll <= attackerChance);
}