#pragma once
#include <string>
using namespace std;
// Class to organize all the data from the stats files
class Stat {
    int win;
    string item_1;
    string item_2;
    string item_3;
    string item_4;
    string item_5;
    string item_6;
public:
    Stat() {
        win = 0;
        item_1 = "no_item";
        item_2 = "no_item";
        item_3 = "no_item";
        item_4 = "no_item";
        item_5 = "no_item";
        item_6 = "no_item";
    }         
    Stat(int win, string i1, string i2, string i3, string i4, string i5, string i6) {
        this->win = win;
        item_1 = i1;
        item_2 = i2;
        item_3 = i3;
        item_4 = i4;
        item_5 = i5;
        item_6 = i6;
    }
    int getWin() { return win; }
    string getItem_1() { return item_1; }
    string getItem_2() { return item_2; }
    string getItem_3() { return item_3; }
    string getItem_4() { return item_4; }
    string getItem_5() { return item_5; }
    string getItem_6() { return item_6; }
};