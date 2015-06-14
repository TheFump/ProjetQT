//#include "duree.h"
#include "mainwindow.h"
//#include "taches.h"
#include"tachemanager.h"
#include "projetmanager.h"
#include "eventmanager.h"
#include "programmationmanager.h"


#include <QApplication>
#include <QFileDialog>
#include <QDate>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TacheManager &m = TacheManager::getInstance();
    w.update();
    w.show();

    return a.exec();
    //todo corriger bug bouton programmationc
}
