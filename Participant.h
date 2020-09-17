#pragma once
#include <string>
using namespace std;
// Class to organize all the data from the participants file
class Participant {
    string hero_id;
    string spell_1;
    string spell_2;
    string position;
public:
    Participant() {}
    Participant(string id, string sp1, string sp2, string pos) {
        hero_id = id;
        spell_1 = sp1;
        spell_2 = sp2;
        position = pos;
    }
    string getHero_id() { return hero_id; }
    string getSpell_1() { return spell_1; }
    string getSpell_2() { return spell_2; }
    string getPosition() { return position; }
};