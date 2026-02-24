#include<iostream>
#include<random>
#include<vector>
#include <string>
#include "PlayerNamePlan.cpp"

using namespace std;

static random_device rd;
static mt19937 gen(rd());

string RanBall(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(0,3);
    
    int x=dist(gen);
      

    string Ball[]={"COPPER","SILVER","GOLD","BLACK"};

    return Ball[x];
}

int GetStatByRate(const vector<int>& weights){
    discrete_distribution<> d(weights.begin(), weights.end());
    int tier = d(gen);

    int ranges[][2] = {{70, 76}, {77, 81}, {82, 85}, {86, 88}, {89, 91}};
    
    uniform_int_distribution<> statDist(ranges[tier][0], ranges[tier][1]);
    return statDist(gen);
}

vector<int> Ranpower(string ball){

 vector<int> result;
    int count = 0;
    vector<int> weights;

    if (ball == "BRONZE") {
        count = 6 + 5 + 4 + 3 + 3; 
        
        weights = {70, 14, 10, 5, 1}; 
        count = 3; 
    } 
    else if (ball == "SILVER") {
        weights = {40, 25, 20, 12, 3};
        count = 3;
    }
    else if (ball == "GOLD") {
        weights = {30, 25, 25, 15, 5};
        count = 3;
    }
    else if (ball == "BLACK") {
        weights = {15, 20, 20, 30, 15};
        count = 3;
    }

    for (int i = 0; i < count; i++) {
        result.push_back(GetStatByRate(weights));
    }
    return result;
    
}
player GetRandomPlayerByStat(int targetStat, const vector<player>& pool) {
    vector<player> matches;
    

    for (const auto& p : pool) {
        if (p.power == targetStat) {
            matches.push_back(p);
        }
    }


    if (matches.empty()) {
        int closest = -1;
        int minDiff = 100;
        for (const auto& p : pool) {
            if (abs(p.power - targetStat) < minDiff) {
                minDiff = abs(p.power - targetStat);
                closest = p.power;
            }
        }
        for (const auto& p : pool) {
            if (p.power == closest) matches.push_back(p);
        }
    }


    uniform_int_distribution<> d(0, matches.size() - 1);
    static mt19937 g(random_device{}()); 
    return matches[d(g)];
}

