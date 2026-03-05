#include<iostream>
#include<random>
#include<vector>
#include <string>
#include "PlayerNamePlan.cpp"

using namespace std;

static random_device rd;
static mt19937 gen(rd());

string RanBall(){
    
     uniform_int_distribution<> dist(0,3);
    
    int x=dist(gen);
      

    string Ball[]={"BRONZE","SILVER","GOLD","BLACK"};

    return Ball[x];
}

int GetStatByRate(const vector<int>& weights){
    discrete_distribution<> d(weights.begin(), weights.end());
    int tier = d(gen);

    int ranges[][2] = {{70, 76}, {77, 81}, {82, 85}, {86, 88}, {89, 91}};
    
    uniform_int_distribution<> statDist(ranges[tier][0], ranges[tier][1]);
    return statDist(gen);
}

vector<int> Ranpower(string ball) {
    vector<int> result;
    vector<int> weights;

    if (ball == "BRONZE") weights = {70, 14, 10, 5, 1};
    else if (ball == "SILVER") weights = {40, 25, 20, 12, 3};
    else if (ball == "GOLD")   weights = {30, 25, 25, 15, 5};
    else if (ball == "BLACK")  weights = {15, 20, 20, 30, 15};

    for (int i = 0; i < 3; i++) {
        result.push_back(GetStatByRate(weights));
    }
    return result;
}
vector<player>& GetPoolByPosition(string pos) {
    if (pos == "GK") return GK;
    if (pos == "DF") return DF;
    if (pos == "MF") return MF;
    return FW; 
}
player GetRandomPlayerByStat(int targetStat, vector<player>& pool) {
    if (pool.empty()) return {"Empty", 0};

    vector<int> matches;
    for (int i = 0; i < pool.size(); i++) {
        if (pool[i].power == targetStat) matches.push_back(i);
    }

    if (matches.empty()) {
        int minDiff = 100;
        for (const auto& p : pool) minDiff = min(minDiff, abs(p.power - targetStat));
        for (int i = 0; i < pool.size(); i++) {
            if (abs(pool[i].power - targetStat) == minDiff) matches.push_back(i);
        }
    }

    uniform_int_distribution<> d(0, matches.size() - 1);
    int selectedIdx = matches[d(gen)];
    
    player chosen = pool[selectedIdx]; 
    pool.erase(pool.begin() + selectedIdx); 
    return chosen;
}