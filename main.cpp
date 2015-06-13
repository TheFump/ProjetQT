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

    ProgrammationManager &p = ProgrammationManager::getInstance();
    //p.ajouterProgrammation(m.getTache("id"), d5, t, t2);


    EventManager &e = EventManager::getInstance();
    //e.ajouterEvent("id", "titre", 200, d);
    //e.ajouterEvent("id2", "titre", 200, d, t, t2);
   // e.ajouterEvent("id3", "titre", 200, d3);
    //e.ajouterEvent("id4", "titre", 200, d4, d5);
   // e.supprimerEvent("id3");

    ProjetManager &pm = ProjetManager::getInstance();

    //w.MainWindow::afficher(t);
    w.update();
    w.show();

    return a.exec();
    //todo corriger bug bouton programmationc
}
