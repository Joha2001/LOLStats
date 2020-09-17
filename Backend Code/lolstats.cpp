#include "lolstats.h"
#include "ui_lolstats.h"

#include <QtWidgets>

LOLStats::LOLStats(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LOLStats)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;

    //Fixed window size
    this->setFixedSize(QSize(970,560));

    //Create background
    QPixmap background(":/asset/images/LeagueAssets/download.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    //Set scroll area background
    ui->scrollArea->setStyleSheet("QScrollArea {background-color:transparent;}");

    //Add search placeholder text
    ui->searchBox->setPlaceholderText("Search");

    //Create list of champ icons
    QString path = ":/champs/images/ChampionIcons/";
    QDir source(path);
    if(!source.exists()) {
        QMessageBox::warning(this, "Warning", "Cannot find source for champ icons");
    }
    QFileInfoList list = source.entryInfoList();

    //Get list of champ id
    QMap<QString, QString> *id = new QMap<QString, QString>;
    path = ":/champID/data/champsNameModified.csv";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot find file for champ icons");
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList lineList = line.split(',');
        id->insert(lineList[0], lineList[1]);
    }

    //Create list of item icons
    path = ":/items/images/LeagueItems/";
    source.setPath(path);
    if(!source.exists()) {
        QMessageBox::warning(this, "Warning", "Cannot find source for items");
    }
    QFileInfoList itemList = source.entryInfoList();

    //Get list of item id
    QMap<QString, QString> *itemID = new QMap<QString, QString>;
    path = ":/itemID/data/items.csv";
    QFile fileItem(path);
    if(!fileItem.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot find file for items");
    }
    QTextStream inItem(&fileItem);
    while(!inItem.atEnd()) {
        QString line = inItem.readLine();
        QStringList lineList = line.split(',');
        itemID->insert(lineList[1], lineList[0]);
    }

    //Set item id to item png path in items map
    for (int i = 0; i < itemList.size(); i++) {
        QFileInfo itemFile(itemList[i]);
        QString itemPath = itemFile.filePath();
        QString itemName = itemFile.completeBaseName();
        itemName.remove("_item");
        itemName.replace("_", " ");
        itemName.replace("%1", ":");
        itemName.replace("%27", "'");
        itemName.replace("%28", "(");
        itemName.replace("%29", ")");
        QString searchID = itemID->value(itemName);
        itemMap.insert(itemName, itemPath);
    }

    //Create list of spell icons
    path = ":/spells/images/LeagueSpells/";
    source.setPath(path);
    if(!source.exists()) {
        QMessageBox::warning(this, "Warning", "Cannot find source for spells");
    }
    QFileInfoList spellList = source.entryInfoList();

    //Get list of spell id
    QMap<QString, QString> *spellID = new QMap<QString, QString>;
    path = ":/spellID/data/spells.csv";
    QFile fileSpell(path);
    if(!fileSpell.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot find file for spells");
    }
    QTextStream inSpell(&fileSpell);
    while(!inSpell.atEnd()) {
        QString line = inSpell.readLine();
        QStringList lineList = line.split(',');
        spellID->insert(lineList[0], lineList[1]);
    }

    //Set spell id to spell png path in spell map
    for (int i = 0; i < spellList.size(); i++) {
        QFileInfo spellFile(spellList[i]);
        QString spellPath = spellFile.filePath();
        QString spellName = spellFile.completeBaseName();
        QString searchID = spellID->value(spellName);
        spellMap.insert(spellName, spellPath);
    }

    //Get list of lane icons
    path = ":/roles/images/LaneIcons/";
    source.setPath(path);
    if(!source.exists()) {
        QMessageBox::warning(this, "Warning", "Cannot find source for lanes");
    }
    QFileInfoList laneList = source.entryInfoList();
    for (int i = 0; i < laneList.size(); i++) {
        QFileInfo laneFile(laneList[i]);
        QString lanePath = laneFile.filePath();
        QString laneName = laneFile.completeBaseName();
        laneName.remove("_icon");
        if (laneName == "Bottom") {
            laneName = "BOT";
        }
        else if (laneName == "Middle") {
            laneName = "MID";
        }
        else {
            laneName = laneName.toUpper();
        }
        laneMap.insert(laneName, lanePath);
    }

    //Loop creating each button
    for (int i = 0; i < 138; i++) {
        QString s = QString::number(i);
        QPushButton *button = new QPushButton(s);
        QFileInfo file(list[i]);
        QPixmap pixmap(file.filePath());
        QString champName = file.completeBaseName();
        champName.remove("Square");
        champName.replace("_", " ");
        button->setObjectName(id->value(champName));
        champName.replace("&", "&&");

        //Create data object

        button->setIcon(pixmap);
        button->setText(champName);
        button->setStyleSheet("text-align:left;");
        button->setIconSize(QSize(50, 50));
        QFont font = button->font();
        font.setPixelSize(25);
        button->setFont(font);
        layout->addWidget(button);

        connect(button, SIGNAL(clicked()), this, SLOT(commonSlot()));

    }
    layout->addStretch();

    //Create and modify ui elements
    ui->scrollAreaWidgetContents->setLayout(layout);

    QFont font = ui->banRate->font();
    font.setPixelSize(21);
    ui->summonerSpell->setFont(font);
    ui->mapButton->setFont(font);
    ui->treeButton->setFont(font);
    ui->itemList->setFont(font);
    ui->efficiency->setFont(font);
    font.setPixelSize(25);
    ui->banRate->setFont(font);
    ui->winRate->setFont(font);
    ui->pickRate->setFont(font);
    font.setPixelSize(30);
    ui->roleName->setFont(font);
    font.setPixelSize(40);
    ui->champName->setFont(font);
}

LOLStats::~LOLStats()
{
    delete ui;
}

//When a champ button is clicked
void LOLStats::commonSlot()
{
    auto start = chrono::high_resolution_clock::now();

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QPixmap pixmap = buttonSender->icon().pixmap(120, 120);
    QString name = buttonSender->text();
    QString champID = buttonSender->objectName();
    name.replace("&&", "&");
    ui->champImage->setPixmap(pixmap);
    ui->champName->setText(name);

    //Change rates
    string cID = champID.toLocal8Bit().constData();

    Hero hero;
    if (ui->mapButton->isEnabled()) {
        hero = heroMap.at(cID);
    }
    else {
        hero = heroTree.Search(cID)->data;
    }

    double winRate = hero.getRateWins();
    stringstream buffer;
    buffer << setprecision(2) << fixed << winRate;
    QString text = QString::fromStdString(buffer.str());
    text = "Win Rate: " + text + "%";
    ui->winRate->setText(text);

    double pickRate = hero.getRatePlayed();
    stringstream buffer2;
    buffer2 << setprecision(2) << fixed << pickRate;
    text = QString::fromStdString(buffer2.str());
    text = "Pick Rate: " + text + "%";
    ui->pickRate->setText(text);

    double banRate = hero.getRateBans();
    stringstream buffer3;
    buffer3 << setprecision(2) << fixed << banRate;
    text = QString::fromStdString(buffer3.str());
    text = "Ban Rate: " + text + "%";
    ui->banRate->setText(text);

    //Change items
    QPixmap image;
    cID = hero.getItems()[0];
    image = itemMap.value(QString::fromStdString(cID));
    ui->item1->setPixmap(image);

    cID = hero.getItems()[1];
    image = itemMap.value(QString::fromStdString(cID));
    ui->item2->setPixmap(image);

    cID = hero.getItems()[2];
    image = itemMap.value(QString::fromStdString(cID));
    ui->item3->setPixmap(image);

    //Change spells
    cID = hero.getSpells()[0];
    image = spellMap.value(QString::fromStdString(cID));
    ui->summonerSpellP1->setPixmap(image);

    cID = hero.getSpells()[1];
    image = spellMap.value(QString::fromStdString(cID));
    ui->summonerSpellP2->setPixmap(image);

    //Change roles
    cID = hero.getPosition();
    QString role = QString::fromStdString(cID);
    image = laneMap.value(role);
    ui->roleIcon->setPixmap(image);
    if (role == "TOP") {
        role = "Top";
    }
    else if (role == "MID") {
        role = "Middle";
    }
    else if (role == "BOT") {
        role = "Bottom";
    }
    else if (role == "JUNGLE") {
        role = "Jungle";
    }
    else if (role == "SUPPORT") {
        role = "Support";
    }
    ui->roleName->setText(role);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    stringstream time;
    time << duration.count();
    ui->efficiency->setText("Efficiency: " + QString::fromStdString(time.str()) + " μs");
}

//When text in search box changed
void LOLStats::on_searchBox_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QList<QPushButton*> buttons = ui->scrollAreaWidgetContents->findChildren<QPushButton*>();
    for(int i = 0; i < 138; i++) {
        if(buttons[i]->text().contains(searchText, Qt::CaseInsensitive)) {
            buttons[i]->show();
        }
        else {
            buttons[i]->hide();
        }
    }
}
