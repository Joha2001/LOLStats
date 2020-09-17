#ifndef LOLSTATS_H
#define LOLSTATS_H

#include <QMainWindow>
#include <QtWidgets>

#include "Helper.h"

#include <map>
#include <string>
#include <sstream>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class LOLStats; }
QT_END_NAMESPACE

class LOLStats : public QMainWindow
{
    Q_OBJECT
private:
    QMap<QString, QString> itemMap;
    QMap<QString, QString> spellMap;
    QMap<QString, QString> laneMap;
    unordered_map <string, Hero> heroMap;
    Tree heroTree;

public:
    LOLStats(QWidget *parent = nullptr);
    ~LOLStats();

    void getMap(unordered_map<string, Hero> x, Tree y) {
        heroMap = x;
        heroTree = y;
    };

private slots:
    void commonSlot();
    void on_searchBox_textChanged(const QString &arg1);

private:
    Ui::LOLStats *ui;

};
#endif // LOLSTATS_H
