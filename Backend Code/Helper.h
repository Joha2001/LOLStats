#pragma once
#include "Hero.h"
#include "Participant.h"
#include "Stat.h"
#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
using namespace std;
struct Helper {
    // Function in charge of extracting relevant data from the champ file
    static void extractChamps(unordered_map <string, Hero>& heroMap, ifstream& file) {
        string name;
        string id;
        getline(file, name);
        while (!file.eof()) {
            getline(file, name, ',');
            getline(file, id);
            Hero* tempHero = new Hero(name, id);
            if (!name.empty() && !id.empty()) {
                heroMap[id] = *tempHero;
            }
            //delete tempHero;
        }
    }
    // Function in charge of extracting relevant data from the spell file
    static void extractSpells(map <string, string>& spells, ifstream& file) {
        string name;
        string id;
        while (!file.eof()) {
            getline(file, name, ',');
            getline(file, id);
            if (!name.empty() && !id.empty()) {
                spells[id] = name;
            }
        }
    }
    // Function in charge of extracting relevant data from the item file
    static void extractItems(map <string, string>& spells, ifstream& file) {
        string name;
        string id;
        while (!file.eof()) {
            getline(file, id, ',');
            getline(file, name);
            if (!name.empty() && !id.empty()) {
                spells[id] = name;
            }
        }
    }
    // Function in charge of extracting relevant data from the participants file
    static void extractParticipants(vector<Participant>& participants, ifstream& file) {
        string hero_id;
        string spell_1;
        string spell_2;
        string role;
        string position;
        string temp;

        getline(file, temp);
        while (!file.eof()) {
            getline(file, temp, ',');
            getline(file, temp, ',');
            getline(file, temp, ',');
            getline(file, temp, '"');
            getline(file, hero_id, '"');
            getline(file, temp, '"');
            getline(file, spell_1, '"');
            getline(file, temp, '"');
            getline(file, spell_2, '"');
            getline(file, temp, '"');
            getline(file, role, '"');
            getline(file, temp, '"');
            getline(file, position, '"');
            getline(file, temp);

            if (role == "DUO_SUPPORT") {
                position = "SUPPORT";
            }

            Participant* tempParticipant = new Participant(hero_id, spell_1, spell_2, position);
            if (!hero_id.empty() && !spell_1.empty() && !spell_2.empty() && !position.empty()) {
                participants.push_back(*tempParticipant);
            }
            //delete tempParticipant;
        }
    }
    // Function in charge of extracting relevant data from the stats files
    static void extractStats(vector<Stat>& stats, ifstream& file) {
        string win;
        string item_1;
        string item_2;
        string item_3;
        string item_4;
        string item_5;
        string item_6;
        string temp;

        getline(file, temp);
        while (file.good()) {
            getline(file, temp, ',');
            getline(file, temp, '"');
            getline(file, win, '"');
            getline(file, temp, '"');
            getline(file, item_1, '"');
            getline(file, temp, '"');
            getline(file, item_2, '"');
            getline(file, temp, '"');
            getline(file, item_3, '"');
            getline(file, temp, '"');
            getline(file, item_4, '"');
            getline(file, temp, '"');
            getline(file, item_5, '"');
            getline(file, temp, '"');
            getline(file, item_6, '"');
            getline(file, temp);

            Stat* tempStat = new Stat(stoi(win), item_1, item_2, item_3, item_4, item_5, item_6);
            if (!win.empty() && !item_1.empty() && !item_2.empty() && !item_3.empty() && !item_6.empty()) {
                stats.push_back(*tempStat);
            }
            //        delete tempStat;
        }
    }
    // Extract the id of all champions that have been ban
    static void extractBans(vector<string>& bans, ifstream& file) {
        string hero_id;
        string temp;

        getline(file, temp);
        while (!file.eof()) {
            getline(file, temp, ',');
            getline(file, temp, ',');
            getline(file, temp, '"');
            getline(file, hero_id, '"');
            getline(file, temp);
            bans.push_back(hero_id);
        }
    }
};
