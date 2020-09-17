#include "lolstats.h"

#include "Helper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    // Variables
    unordered_map <string, Hero> heroMap;
    map <string, string> spells;
    map <string, string> items;
    vector<string> bans;
    vector<Participant> participants;
    vector<Stat> stats;

    QString qPath = qApp->applicationDirPath() + "/data/champs.csv";
    string filePath = qPath.toLocal8Bit().constData();
    ifstream fileChamps(filePath);

    qPath = qApp->applicationDirPath() + "/data/spells.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileSpells(filePath);

    qPath = qApp->applicationDirPath() + "/data/items.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileItems(filePath);

    qPath = qApp->applicationDirPath() + "/data/participants.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileParticipants(filePath);

    qPath = qApp->applicationDirPath() + "/data/stats1.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileStats1(filePath);

    qPath = qApp->applicationDirPath() + "/data/stats2.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileStats2(filePath);

    qPath = qApp->applicationDirPath() + "/data/teambans.csv";
    filePath = qPath.toLocal8Bit().constData();
    ifstream fileBans(filePath);


    // Check for errors opening files
    if (!fileChamps.is_open()) {
        cout << "Unable to open file champs";
        exit(1);
    }
    if (!fileSpells.is_open()) {
        cout << "Unable to open file spells";
        exit(1);
    }
    if (!fileItems.is_open()) {
        cout << "Unable to open file items";
        exit(1);
    }
    if (!fileParticipants.is_open()) {
        cout << "Unable to open file participants";
        exit(1);
    }
    if (!fileStats1.is_open()) {
        cout << "Unable to open file stats1";
        exit(1);
    }
    if (!fileStats2.is_open()) {
        cout << "Unable to open file stats2";
        exit(1);
    }
    if (!fileBans.is_open()) {
        cout << "Unable to open file bans";
        exit(1);
    }

    // Extract data from files
    Helper::extractChamps(heroMap, fileChamps);
    cout << "Extraction of Champions Complete" << endl;
    Helper::extractSpells(spells, fileSpells);
    cout << "Extraction of Spells Complete" << endl;
    Helper::extractItems(items, fileItems);
    cout << "Extraction of Items Complete" << endl;
    Helper::extractParticipants(participants, fileParticipants);
    cout << "Extraction of Participants Complete" << endl;
    Helper::extractStats(stats, fileStats1);
    cout << "Extraction of Stats One Complete" << endl;
    Helper::extractStats(stats, fileStats2);
    cout << "Extraction of Stats Two Complete" << endl;
    Helper::extractBans(bans, fileBans);
    cout << "Extraction of Bans Complete" << endl;

    // Load heroMap with all the data
    for (int i = 0; i < participants.size(); i++) {
        string heroID = participants[i].getHero_id();
        string spell_1 = participants[i].getSpell_1();
        string spell_2 = participants[i].getSpell_2();
        string i1 = stats[i].getItem_1();
        string i2 = stats[i].getItem_2();
        string i3 = stats[i].getItem_3();
        string i4 = stats[i].getItem_4();
        string i5 = stats[i].getItem_5();
        string i6 = stats[i].getItem_6();
        string position = participants[i].getPosition();
        heroMap[heroID].addMatch();
        heroMap[heroID].addWin(stats[i].getWin());
        heroMap[heroID].setTotalSpells(spells[spell_1], spells[spell_2]);
        heroMap[heroID].setTotalPosition(position);
        heroMap[heroID].setTotalItems(items[i1], items[i2], items[i3], items[i4], items[i5], items[i6]);
    }
    cout << "Loading into HeroMap Complete" << endl;
    for (int i = 0; i < bans.size() - 1; i++) {
        heroMap[bans[i]].addBan();
    }
    cout << "Loading Bans into HeroMap Complete" << endl;
    Tree heroTree = Tree();
    for (auto it = heroMap.begin(); it != heroMap.end(); it++) {
        heroMap[it->first].findMostUsedSpells();
        heroMap[it->first].findMostUsedItems();
    }
    for (auto iter = heroMap.begin(); iter != heroMap.end(); iter++) {
        heroTree.Insert(iter->second);
    }
    cout << "Copying Data from HeroMap to HeroTree complete" << endl;

    //GUI
    LOLStats w;
    w.getMap(heroMap, heroTree);
    w.show();
    return a.exec();
}
