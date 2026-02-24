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

const int STAT_DIFF_THRESHOLD = 10;     
const int STAT_DIFF_BONUS_PERCENT = 10;

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

void startMatch(Team homeTeam, Team awayTeam) {
    cout << "==========================================\n";
    cout << "MATCH KICK-OFF: " << homeTeam.teamName << " (Home) VS " << awayTeam.teamName << " (Away)\n";
    cout << "==========================================\n";
    
    bool matchEnded = false;
    
    while (!matchEnded) {
        cout << "\n--- [MIDFIELD BATTLE: MF vs MF] ---" << endl;
        float homeMidAvg = getMidfieldAvg(homeTeam);
        float awayMidAvg = getMidfieldAvg(awayTeam);
        
        Team* attackingTeam = nullptr;
        Team* defendingTeam = nullptr;
        
        if (homeMidAvg >= awayMidAvg) {
            cout << ">> " << homeTeam.teamName << " dominates the midfield! (Avg Stat: " << homeMidAvg << " vs " << awayMidAvg << ")" << endl;
            attackingTeam = &homeTeam;
            defendingTeam = &awayTeam;
        } else {
            cout << ">> " << awayTeam.teamName << " takes control of the midfield! (Avg Stat: " << awayMidAvg << " vs " << homeMidAvg << ")" << endl;
            attackingTeam = &awayTeam;
            defendingTeam = &homeTeam;
        }
        
        cout << "\n   --- [ATTACKING PHASE: FW vs DF] ---" << endl;
        Player attackerFW = getRandomPlayer(*attackingTeam, "FW");
        Player defenderDF = getRandomPlayer(*defendingTeam, "DF");
        
        cout << "   " << attackingTeam->teamName << " goes on the offensive! " << attackerFW.name << " (FW, Stat:" << attackerFW.stat << ") "
             << "takes on " << defenderDF.name << " (DF, Stat:" << defenderDF.stat << ")!" << endl;
             
        if (duel1v1(attackerFW, defenderDF, *attackingTeam, *defendingTeam)) {
            cout << "   => BRILLIANT SKILL! " << attackerFW.name << " dribbles past the defender and enters the penalty box!" << endl;
            
            cout << "\n      --- [ONE-ON-ONE: FW vs GK] ---" << endl;
            Player defenderGK = getRandomPlayer(*defendingTeam, "GK");
            
            cout << "      It's just " << attackerFW.name << " against the goalkeeper, " << defenderGK.name << " (GK, Stat:" << defenderGK.stat << ")!" << endl;
            
            if (duel1v1(attackerFW, defenderGK, *attackingTeam, *defendingTeam)) {
                cout << "      => GOAL!!! What a fantastic finish by " << attackerFW.name << "!" << endl;
                cout << "\n==========================================" << endl;
                cout << "         WINNER IS " << attackingTeam->teamName << " !!!" << endl;
                cout << "==========================================\n" << endl;
                matchEnded = true; 
            } else {
                cout << "      => SAVED! " << defenderGK.name << " makes a crucial save! The ball is cleared back to the midfield..." << endl;
            }
        } else {
            cout << "      => TACKLED! Great defending by " << defenderDF.name << "! The ball is cleared back to the midfield..." << endl;
        }
    }
}