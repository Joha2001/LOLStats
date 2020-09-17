#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;
class Hero
{
private:
    int matchesplayed;
    int wins;
    int bans;
    string id;
    string name;
    string spells[2];
    string items[3];
    string position;
    double ratePlayed;
    double rateWins;
    double rateBans;
    map<string, int> totalItems;
    map<string, int> totalSpells;
    map<string, int> totalPositions;
    void addToMap(map<string, int>& map, string data);
public:
    Hero() {
        this->name = "null";
        this->id = "-1";
        matchesplayed = 0;
        wins = 0;
        bans = 0;
        ratePlayed = 0;
        rateWins = 0;
        rateBans = 0;
    }
    Hero(string name, string id) {
        this->name = name;
        this->id = id;
        matchesplayed = 0;
        wins = 0;
        bans = 0;
        ratePlayed = 0;
        rateWins = 0;
        rateBans = 0;
    }
    string* getSpells() { return spells; }
    string* getItems() { return items; }
    string getName() { return name; }
    string getId() { return id; }
    string getPosition() { return position; }
    int getBans() { return bans; }
    int getMatchPlayed() { return matchesplayed; }
    double getRatePlayed() {
        ratePlayed = ((double)matchesplayed / 184070.0) * 100.0;
        return ratePlayed;
    }
    double getRateWins() {
        rateWins = ((double)wins / (double)matchesplayed) * 100.0;
        return rateWins;
    }
    double getRateBans() {
        rateBans = ((double)bans / 184070.0) * 100.0;
        return rateBans;
    }
    void setTotalSpells(string spell_1, string spell_2);
    void setTotalItems(string item_1, string item_2, string item_3, string item_4, string item_5, string item_6);
    void setTotalPosition(string pos);
    void addMatch() {
        matchesplayed += 1;
    }
    void addWin(int w) {
        wins += w;
    }
    void addBan() {
        bans += 1;
    }
    void findMostUsedSpells();
    void findMostUsedItems();
};

