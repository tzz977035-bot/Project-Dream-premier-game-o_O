#include<iostream>
#include<random>
#include<vector>
#include <string>

using namespace std;

static random_device rd;
static mt19937 gen(rd());

string RanBall(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(0,3);
    
    int x=dist(gen);
      
<<<<<<< HEAD
    string Ball[]={"BRONZE","SILVER","GOLD","BLACK"};
=======
    string Ball[]={"COPPER","SILVER","GOLD","BLACK"};
>>>>>>> edeef2aece51c2ec3c607dbbceee7a5116dc1c6d

    return Ball[x];
}

int GetStatByRate(const vector<int>& weights){
    discrete_distribution<> d(weights.begin(), weights.end());
    int tier = d(gen);

    int ranges[][2] = {{70, 76}, {77, 81}, {82, 85}, {86, 88}, {89, 91}};
    
    uniform_int_distribution<> statDist(ranges[tier][0], ranges[tier][1]);
    return statDist(gen);
}

vector<int> RanPlayer(string ball){

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

int main(){
     
    string ball=RanBall();
            
<<<<<<< HEAD
   cout << "Your Ball is " <<ball<<" !!!";
=======
   cout << "Your Ball is " <<ball<<" !!!!";
>>>>>>> edeef2aece51c2ec3c607dbbceee7a5116dc1c6d

   vector<int> PLAYER = RanPlayer(ball);
   
   cout << "\nYour Player Stats: ";
    for (int stat : PLAYER) {
        cout << "[" << stat << "] ";
    }
    cout << endl;
    
    return 0;
   
    
}
