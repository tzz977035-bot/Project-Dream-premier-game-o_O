#include <iostream>
#include <vector>
#include <string>
#include "Random.cpp"
using namespace std;


struct Formation {
    string name;             
    string buffStat;         // สเตตัสที่จะได้บัฟตอนจบเกม ("FW", "DF", "MF")
    string buffPercent;         // เปอร์เซ็นต์บัฟ (20)
    vector<string> draftOrder; // ลำดับตำแหน่งที่จะให้เพื่อนเอาไปเขียนลูปสุ่ม
};


Formation chooseFormation(int playerNum) {
    vector<Formation> availableFormations = {
        {"4-3-3", "FW", "20", {"GK", "DF", "DF", "DF", "DF", "MF", "MF", "MF", "FW", "FW", "FW"}},
        {"5-3-2", "DF", "20", {"GK", "DF", "DF", "DF", "DF", "DF", "MF", "MF", "MF", "FW", "FW"}},
        {"4-4-2", "MF", "20", {"GK", "DF", "DF", "DF", "DF", "MF", "MF", "MF", "MF", "FW", "FW"}}
    };

    string playerName = (playerNum == 1) ? "Player 1 (Away)" : "Player 2 (Home)";
    int choice = 0;

    
    cout << "\n=========================================" << endl;
    cout << "   " << playerName << " - SELECT FORMATION" << endl;
    cout << "=========================================" << endl;
    for (int i = 0; i < availableFormations.size(); i++) {
        cout << "[" << i + 1 << "] " << availableFormations[i].name 
             << " (Buff: +" << availableFormations[i].buffPercent 
             << "% to " << availableFormations[i].buffStat << ")" << endl;
    }
    cout << "=========================================" << endl;

    
    while (true) {
        cout << "Select formation (1-3): ";
        cin >> choice;
        if (choice >= 1 && choice <= 3) {
            break;
        }
        cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
    }

    
    Formation selected = availableFormations[choice - 1];
    cout << "\n>> " << playerName << " selected " << selected.name << " <<" << endl;
    
    return selected;
}

int main() {
    // ---------------------------------------------------------
    // PLAYER 1 (AWAY) PHASE
    // ---------------------------------------------------------
    Formation p1Formation = chooseFormation(1);
    vector<player> team1;

    cout << "\n=========================================" << endl;
    cout << "      PLAYER 1: DRAFTING 11 PLAYERS      " << endl;
    cout << "=========================================" << endl;

    for (int i = 0; i < p1Formation.draftOrder.size(); i++) {
        string pos = p1Formation.draftOrder[i];
        string ball = RanBall();
        vector<int> powerOptions = Ranpower(ball); // สุ่มมา 3 พลัง

        cout << "\nROUND [" << i + 1 << "/11] POSITION: " << pos << " (" << ball << ")" << endl;
        cout << "Identify your targets:" << endl;

        // --- ส่วนที่เพิ่มเข้ามา: แสดงชื่อนักเตะก่อนเลือก ---
        vector<player> previews;
        for (int j = 0; j < powerOptions.size(); j++) {
            // จำลองการสุ่มดูว่าถ้าเลือกพลังนี้จะได้ใคร
            player p = GetRandomPlayerByStat(powerOptions[j], GetPoolByPosition(pos));
            previews.push_back(p);
            cout << "  [" << j + 1 << "] " << p.name << " (Power: " << p.power << ")" << endl;
        }

        int choice;
        while (true) {
            cout << "Draft player (1-3): ";
            cin >> choice;
            if (choice >= 1 && choice <= 3) break;
            cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
        }

        // เก็บนักเตะที่เลือกเข้าทีม
        team1.push_back(previews[choice - 1]);
        cout << ">> Confirmed: " << previews[choice - 1].name << " is now in your squad!" << endl;
        cout << "-----------------------------------------" << endl;
    }

    // ---------------------------------------------------------
    // PLAYER 2 (HOME) PHASE (ทำแบบเดียวกัน)
    // ---------------------------------------------------------
    cout << "\nPress Enter to start Player 2's turn...";
    cin.ignore(); cin.get();

    Formation p2Formation = chooseFormation(2);
    vector<player> team2;

    cout << "\n=========================================" << endl;
    cout << "      PLAYER 2: DRAFTING 11 PLAYERS      " << endl;
    cout << "=========================================" << endl;

    for (int i = 0; i < p2Formation.draftOrder.size(); i++) {
        string pos = p2Formation.draftOrder[i];
        string ball = RanBall();
        vector<int> powerOptions = Ranpower(ball);

        vector<player> previews;
        cout << "\nROUND [" << i + 1 << "/11] POSITION: " << pos << " (" << ball << ")" << endl;
        for (int j = 0; j < powerOptions.size(); j++) {
            player p = GetRandomPlayerByStat(powerOptions[j], GetPoolByPosition(pos));
            previews.push_back(p);
            cout << "  [" << j + 1 << "] " << p.name << " (Power: " << p.power << ")" << endl;
        }

        int choice;
        while (true) {
            cout << "Draft player (1-3): ";
            cin >> choice;
            if (choice >= 1 && choice <= 3) break;
            cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
        }

        team2.push_back(previews[choice - 1]);
        cout << ">> Confirmed: " << previews[choice - 1].name << " is now in your squad!" << endl;
        cout << "-----------------------------------------" << endl;
    }

    return 0;
}