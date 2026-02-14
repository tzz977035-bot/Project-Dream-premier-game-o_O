#include<iostream>
#include<random>

using namespace std;

string RanBall(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(1,3);
    
    int x=dist(gen)+1;
      
    string Ball[]={"COPPER","SILVER","GOLD","BLACK"};

    return Ball[x];
}



vector<int> RanPlayer(int a,int min_val, int max_val){

  vector<int> result;

    static random_device rd;
    static mt19937 gen(rd());
     uniform_int_distribution<> dist(min_val,max_val);
    
     for(int i=0; i<a; i++){
        result.push_back(dist(gen));
     }
    
    return result;
     
}

int main(){
     
    string ball=RanBall();
            
   cout << "Your Ball is " <<ball<<" !!!!";

    
}
