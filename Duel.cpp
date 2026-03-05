#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
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

void showPitch(string zone, string attacker, string defender) {
    cout << "\n---------------------------------------------------" << endl;
    if (zone == "MF") {
        cout << "[ GK |  DF  |  MF(O)  |  DF  | GK ]  << BATTLE AREA" << endl;
        cout << "            " << attacker << " vs " << defender << endl;
    } 
    else if (zone == "ATTACK_HOME") {
        cout << "[ GK |  DF  |   MF    | DF(O)| GK ]  << BATTLE AREA" << endl;
        cout << "                        " << attacker << " vs " << defender << endl;
    }
    else if (zone == "ATTACK_AWAY") {
        cout << "[ GK | DF(O)|   MF    |  DF  | GK ]  << BATTLE AREA" << endl;
        cout << "       " << attacker << " vs " << defender << endl;
    }
    else if (zone == "GK_HOME") {
        cout << "[ GK |  DF  |   MF    |  DF  |GK(O)] << BATTLE AREA" << endl;
        cout << "                               " << attacker << " vs " << defender << endl;
    }
    else if (zone == "GK_AWAY") {
        cout << "[GK(O)|  DF  |   MF    |  DF  | GK ] << BATTLE AREA" << endl;
        cout << "  " << attacker << " vs " << defender << endl;
    }
    cout << "---------------------------------------------------\n" << endl;
}

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
    int homeScore = 0;
    int awayScore = 0;

    cout << "==========================================\n";
    cout << "MATCH KICK-OFF: " << homeTeam.teamName << " (Home) VS " << awayTeam.teamName << " (Away)\n";
    cout << "==========================================\n";
    
    for (int minute = 1; minute <= 90; minute++) {
        
        cout << "\n[Minute: " << minute << "'] --- [MIDFIELD BATTLE: MF vs MF] ---" << endl;
        
        float homeMidAvg = getMidfieldAvg(homeTeam);
        float awayMidAvg = getMidfieldAvg(awayTeam);
        
        Team* attackingTeam = nullptr;
        Team* defendingTeam = nullptr;
        bool isHomeAttacking = false;
        
        int homePossessionChance = 50 + ((homeMidAvg - awayMidAvg) * 2); 
        
        if (homePossessionChance > 85) homePossessionChance = 85;
        if (homePossessionChance < 15) homePossessionChance = 15;

        int midfieldRoll = (rand() % 100) + 1; 

        if (midfieldRoll <= homePossessionChance) {
            attackingTeam = &homeTeam;
            defendingTeam = &awayTeam;
            isHomeAttacking = true;

            cout << ">> " << homeTeam.teamName << " wins the midfield! (Roll: " << midfieldRoll << " <= " << homePossessionChance << "%)" << endl;
        } else {
            attackingTeam = &awayTeam;
            defendingTeam = &homeTeam;
            isHomeAttacking = false;
            cout << ">> " << awayTeam.teamName << " wins the midfield! (Roll: " << midfieldRoll << " > " << homePossessionChance << "%)" << endl;
        }

        showPitch("MF", attackingTeam->teamName + " Mid", defendingTeam->teamName + " Mid");
        
        cout << "\n   --- [ATTACKING PHASE: FW vs DF] ---" << endl;
        Player attackerFW = getRandomPlayer(*attackingTeam, "FW");
        Player defenderDF = getRandomPlayer(*defendingTeam, "DF");
        
        if (isHomeAttacking) {
            showPitch("ATTACK_HOME", attackerFW.name, defenderDF.name);
        } else {
            showPitch("ATTACK_AWAY", attackerFW.name, defenderDF.name);
        }
             
        if (duel1v1(attackerFW, defenderDF, *attackingTeam, *defendingTeam)) {
            cout << "   => BRILLIANT SKILL! " << attackerFW.name << " dribbles past!" << endl;
            
            cout << "\n      --- [ONE-ON-ONE: FW vs GK] ---" << endl;
            Player defenderGK = getRandomPlayer(*defendingTeam, "GK");
            
            if (isHomeAttacking) {
                showPitch("GK_HOME", attackerFW.name, defenderGK.name);
            } else {
                showPitch("GK_AWAY", attackerFW.name, defenderGK.name);
            }
            
            if (duel1v1(attackerFW, defenderGK, *attackingTeam, *defendingTeam)) {
                
                cout << "      => GOAL!!! What a fantastic finish by " << attackerFW.name << "!" << endl;
                
                if (isHomeAttacking) {
                    homeScore++;
                } else {
                    awayScore++;
                }
                
                cout << "      [SCORE UPDATE: " << homeTeam.teamName << " " << homeScore << " - " << awayScore << " " << awayTeam.teamName << "]" << endl;
                
            } else {
                cout << "      => SAVED! " << defenderGK.name << " makes a crucial save!" << endl;
            }
        } else {
            cout << "      => TACKLED! Great defending by " << defenderDF.name << "!" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "\n==========================================\n";
    cout << "               FULL TIME SCORE            \n";
    cout << "      " << homeTeam.teamName << " " << homeScore << " - " << awayScore << " " << awayTeam.teamName << "\n";
    cout << "==========================================\n";
    
    if (homeScore > awayScore) {
        cout << "WINNER IS " << homeTeam.teamName << " !!!\n";
    } else if (awayScore > homeScore) {
        cout << "WINNER IS " << awayTeam.teamName << " !!!\n";
    } else {
        cout << "IT'S A DRAW!\n";
    }
}