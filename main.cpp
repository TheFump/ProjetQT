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
    QDate d (2015,6,10); QDate du (2016, 7, 1);
    QDate d3 (2015,6,11);
    QDate d4 (2015,6,12);
    QDate d5 (2015,6,13);
    QTime t (2, 0); QTime t2(8, 0);
    //Tache t("id", "titre", 600, d, du, false);
    //TacheManager &m1 = TacheManager::getInstance();
    TacheManager &m = TacheManager::getInstance();
    //m.ajouterTacheUnitaire("id", "titre", 600, d, du, false);
    //m.ajouterTache("id2", "titre2", 600, d, du, true);

    ProgrammationManager &p = ProgrammationManager::getInstance();
    //p.ajouterProgrammation(m.getTache("id"), d5, t, t2);


    EventManager &e = EventManager::getInstance();
    //e.ajouterEvent("id", "titre", 200, d);
    e.ajouterEvent("id2", "titre", 200, d, t, t2);
   // e.ajouterEvent("id3", "titre", 200, d3);
    //e.ajouterEvent("id4", "titre", 200, d4, d5);
   // e.supprimerEvent("id3");

    ProjetManager &pm = ProjetManager::getInstance();
//    pm.ajouterProjet("id", "titre");
//    pm.ajouterProjet("id2", "titre2");
//    pm.ajouterTache("id", "id");
//    pm.ajouterTache("id2", "id");
//    pm.ajouterTache("id2", "id2");
//    pm.ajouterTache("id", "id2");
    //w.MainWindow::afficher(t);
    w.update();
    w.show();

    return a.exec();
    //todo corriger bug bouton programmationc
}
