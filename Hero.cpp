#include "Hero.h"
#include <iostream>
    // Helper function
    void Hero::addToMap(map<string, int>& map, string data) {
        if (map.find(data) != map.end()) {
            map[data] = map[data] + 1;
        }
        else {
            map[data] = 1;
        }
    }
    // Save all the spells used by this champion
    void Hero::setTotalSpells(string spell_1, string spell_2) {
        addToMap(totalSpells, spell_1);
        addToMap(totalSpells, spell_2);
        if (spells[0].empty()) {
            spells[0] = spell_1;
            spells[1] = spell_2;
        }
    }
    // Save all the items used by this champion
    void Hero::setTotalItems(string item_1, string item_2, string item_3, string item_4, string item_5, string item_6) {
        if (!item_1.empty()) {
            addToMap(totalItems, item_1);
            if (items[0].empty()) {
                items[0] = item_1;
            }
            else if (items[1].empty()) {
                items[1] = item_1;
            }
            else if (items[2].empty()) {
                items[2] = item_1;
            }
        }
        if (!item_2.empty()) {
            addToMap(totalItems, item_2);
            if (items[0].empty()) {
                items[0] = item_2;
            }
            else if (items[1].empty()) {
                items[1] = item_2;
            }
            else if (items[2].empty()) {
                items[2] = item_2;
            }
        }
        if (!item_3.empty()) {
            addToMap(totalItems, item_3);
            if (items[0].empty()) {
                items[0] = item_3;
            }
            else if (items[1].empty()) {
                items[1] = item_3;
            }
            else if (items[2].empty()) {
                items[2] = item_3;
            }
        }
        if (!item_4.empty()) {
            addToMap(totalItems, item_4);
            if (items[0].empty()) {
                items[0] = item_4;
            }
            else if (items[1].empty()) {
                items[1] = item_4;
            }
            else if (items[2].empty()) {
                items[2] = item_4;
            }
        }
        if (!item_5.empty()) {
            addToMap(totalItems, item_5);
            if (items[0].empty()) {
                items[0] = item_5;
            }
            else if (items[1].empty()) {
                items[1] = item_5;
            }
            else if (items[2].empty()) {
                items[2] = item_5;
            }
        }
        if (!item_6.empty()) {
            addToMap(totalItems, item_6);
            if (items[0].empty()) {
                items[0] = item_6;
            }
            else if (items[1].empty()) {
                items[1] = item_6;
            }
            else if (items[2].empty()) {
                items[2] = item_6;
            }
        }
    }
    // Get and find most used position
    void Hero::setTotalPosition(string pos) {
        addToMap(totalPositions, pos);
        if (position.empty()) {
            position = pos;
        }
        else {
            if (totalPositions[position] < totalPositions[pos]) {
                position = pos;
            }
        }
    }
    // Find the 2 most used spells
    void Hero::findMostUsedSpells() {
        for (auto it = totalSpells.begin(); it != totalSpells.end(); it++) {
            if (totalSpells[spells[0]] < it->second && it->first != spells[1]) {
                spells[0] = it->first;
            }
            if (totalSpells[spells[1]] < it->second && it->first != spells[0]) {
                spells[1] = it->first;
            }
        }
    }
    // Find the 3 most used items
    void Hero::findMostUsedItems() {
        for (auto it = totalItems.begin(); it != totalItems.end(); it++) {
            if (totalItems[items[0]] < it->second && it->first != items[1] && it->first != items[2]) {
                items[0] = it->first;
            }
            if (totalItems[items[1]] < it->second && it->first != items[0] && it->first != items[2]) {
                items[1] = it->first;
            }
            if (totalItems[items[2]] < it->second && it->first != items[0] && it->first != items[1]) {
                items[2] = it->first;
            }
        }
    }