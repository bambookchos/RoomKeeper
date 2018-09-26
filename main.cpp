#include "login.h"
#include "secondui.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //DB CONNECT
    QSqlDatabase dbase= QSqlDatabase::addDatabase("QSQLITE");
    const QString documents_folder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    dbase.setDatabaseName(documents_folder+"/main_dev.sqlite");
    qDebug() << documents_folder;
    if (!dbase.open()) {

        QMessageBox::critical(0, QObject::tr("Error"), QObject::tr(dbase.lastError().text().toStdString().c_str()), QMessageBox::Cancel);
    }

    QSqlQuery query;

    query.exec("PRAGMA foreign_keys = ON;");



    query.exec("DROP TABLE IF EXISTS `reservations`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `room_characters`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `character_vars`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `rooms`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `customers`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `personal`");
    qDebug() << query.lastError();
    query.exec("DROP TABLE IF EXISTS `characters`");


    query.exec("CREATE TABLE IF NOT EXISTS `characters` ("
               "	`ID`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "	`Name`	TEXT"
               ")");
    query.exec("INSERT INTO `characters` VALUES (1,'Вместимость')");
    query.exec("INSERT INTO `characters` VALUES (2,'Тип')");



    query.exec("CREATE TABLE IF NOT EXISTS `character_vars` ("
               "	`ID`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "	`C_ID`	INTEGER,"
               "	`Name`	TEXT,"
               "	FOREIGN KEY(`C_ID`) REFERENCES `characters`(`ID`)"
               ")");
    query.exec("INSERT INTO `character_vars` VALUES (1,1,'1')");
    query.exec("INSERT INTO `character_vars` VALUES (2,1,'2')");
    query.exec("INSERT INTO `character_vars` VALUES (3,1,'3')");
    query.exec("INSERT INTO `character_vars` VALUES (4,1,'4')");
    query.exec("INSERT INTO `character_vars` VALUES (5,2,'Люкс')");
    query.exec("INSERT INTO `character_vars` VALUES (6,2,'Эконом')");

    query.exec("CREATE TABLE IF NOT EXISTS `rooms` ("
               "	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "	`Number`	INTEGER UNIQUE"
               ")");
    query.exec("INSERT INTO `rooms` VALUES (1,1)");
    query.exec("INSERT INTO `rooms` VALUES (2,2)");
    query.exec("INSERT INTO `rooms` VALUES (3,3)");
    query.exec("INSERT INTO `rooms` VALUES (4,4)");

    query.exec("CREATE TABLE IF NOT EXISTS `room_characters` ("
               "	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "	`R_ID`	INTEGER,"
               "	`C_ID`	INTEGER,"
               "	`C_V_ID`	INTEGER,"
               "	FOREIGN KEY(`C_V_ID`) REFERENCES `character_vars`(`ID`),"
               "	FOREIGN KEY(`R_ID`) REFERENCES `rooms`(`ID`),"
               "	FOREIGN KEY(`C_ID`) REFERENCES `characters`(`ID`)"
               ")");
    query.exec("INSERT INTO `room_characters` VALUES (1,1,1,1)");
    query.exec("INSERT INTO `room_characters` VALUES (2,1,2,5)");
    query.exec("INSERT INTO `room_characters` VALUES (3,2,1,2)");
    query.exec("INSERT INTO `room_characters` VALUES (4,2,2,5)");
    query.exec("INSERT INTO `room_characters` VALUES (5,3,1,3)");
    query.exec("INSERT INTO `room_characters` VALUES (6,3,2,5)");
    query.exec("INSERT INTO `room_characters` VALUES (7,4,1,4)");
    query.exec("INSERT INTO `room_characters` VALUES (8,4,2,6)");



    query.exec("CREATE TABLE IF NOT EXISTS `customers` ("
               "	`ID`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "	`Name`	TEXT,"
               "	`Birthdate`	DATE,"
               "	`Passport`	TEXT"
               ")");
    query.exec("INSERT INTO `customers` VALUES (1,'Pupkin Vasia','1998-12-02','0312 056670')");
    query.exec("INSERT INTO `customers` VALUES (2,'Dupkin Petia','1998-01-03','3542 643264')");
    query.exec("INSERT INTO `customers` VALUES (3,'Jupkin Gena','1998-05-12','6235 765744')");
    query.exec("INSERT INTO `customers` VALUES (4,'Kupkin Sasha','1998-04-22','6326 432422')");


    query.exec("CREATE TABLE IF NOT EXISTS `reservations` ("
               "	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "	`Customer_ID`	INTEGER,"
               "	`Room_ID`	INTEGER,"
               "	`Start_Date`	DATE,"
               "	`End_Date`	DATE,"
               "	`Status`	INTEGER,"
               "	FOREIGN KEY(`Customer_ID`) REFERENCES `customers`(`ID`),"
               "	FOREIGN KEY(`Room_ID`) REFERENCES `rooms`(`ID`)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS `personal` ("
               "	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "	`Name`	TEXT,"
               "	`Password`	TEXT,"
               "	`Permission 1`	INTEGER,"
               "	`Permission 2`	INTEGER,"
              "	`Permission 3`	INTEGER,"
              "	`Permission 4`	INTEGER,"
              "	`Permission 5`	INTEGER,"
              "	`Permission 6`	INTEGER,"
              "	`Permission 7`	INTEGER,"
               "	`Permission 8`	INTEGER"
               ")");
    query.exec("INSERT INTO `personal` VALUES (1,'Quest','Quest',0,0,0)");
    query.exec("INSERT INTO `personal` VALUES (2,'Administrator','Password',1,1,1,1,1,1,1,1)");

    Login login;
    login.show();

    int status = login.exec();

    if (!status) {
        return  0;
    }

    SecondUI s;
    s.show();


    return a.exec();
}
