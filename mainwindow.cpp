#include "mainwindow.h"
#include "tachemanager.h"
#include "programmation.h"
#include "programmationmanager.h"
#include "ui_mainwindow.h"
#include "projetmanager.h"
#include "eventmanager.h"

#include "tachemanager.h"
#include "taches.h"
#include "tacheunitaire.h"
#include "tachecomposite.h"

#include "projetmanager.h"
#include "projet.h"

///voldjinn




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(afficherT(Tache& t)));
    //QMetaObject::connectSlotsByName(this);

    ui->Calendar->setRowCount(24);
    ui->Calendar->setColumnCount(7);

    QStringList days;
    days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday";
    ui->Calendar->setHorizontalHeaderLabels(days);
    QStringList hours;
    hours << "00h00" << "01h00" << "02h00" << "03h00" <<  "04h00" << "05h00" << "06h00" << "07h00" << "08h00" << "09h00" << "10h00" << "11h00" << "12h00" << "13h00" << "14h00" << "15h00" << "16h00" << "17h00" << "18h00" << "19h00" << "20h00" << "21h00" << "22h00" << "23h00" << "24h00";
    ui->Calendar->setVerticalHeaderLabels(hours);
    for(int i =0; i < 24; i++){
        for(int j =0; j < 7; j++){
            ui->Calendar->setItem(i, j, new QTableWidgetItem);

        }
    }
    ui->CalendarDate->setDate(QDate::currentDate());
    ui->ProjetDisplay->setColumnCount(3);
    QStringList headers;
    headers << tr("Projet") << tr("Tache") << tr("Tache Précédente");
    ui->ProjetDisplay->setHeaderLabels(headers);

}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::update()
{

    ui->Display->clear();
     ProgrammationManager &p = ProgrammationManager::getInstance();
     TacheManager &t = TacheManager::getInstance();
     ProjetManager &m = ProjetManager::getInstance();
     EventManager &e = EventManager::getInstance();
     ui->Display->appendPlainText("Programmations : ");
     ui->Display->appendPlainText(QString::number(p.getNb()));
     ui->Display->appendPlainText("Taches : ");
     ui->Display->appendPlainText(QString::number(t.getNb()));
     ui->Display->appendPlainText("Projets : ");
     ui->Display->appendPlainText(QString::number(m.getNb()));
     ui->Display->appendPlainText("Events : ");
     ui->Display->appendPlainText(QString::number(e.getNb()));


    this->afficherCalendar();
    this->treeGestion();
    this->afficherEvents();

}

void MainWindow::afficherCalendar()
{
    ProgrammationManager &p = ProgrammationManager::getInstance();
    ProgrammationManager::Iterator i = p.getIterator();
    QDate comp = ui->CalendarDate->date();
    for(int i =0; i < 24; i++){
        for(int j =0; j < 7; j++){
            ui->Calendar->item(i, j)->setBackgroundColor(Qt::white);
        }
    }
    while(!i.isDone()){
        if(i.current().getDate().weekNumber() == comp.weekNumber() ){
            if(i.current().getDate().year() == comp. year()){
                MainWindow::displayProgrammation(i.current());

            }
        }
        i.next();}
}

void MainWindow::displayProgrammation(const Programmation &p)
{
    int date = p.getDate().dayOfWeek() -1;
    int i=0;
    for( i = p.getHoraire().toString("h").toInt(); i <p.getfin().toString("h").toInt(); i++)
    {
        ui->Calendar->item(i, date)->setBackgroundColor(Qt::gray);
    }
}

void MainWindow::addTreeRoot(QString name, Projet& p)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->ProjetDisplay);
    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    /*QTreeWidgetItem *treeItem2 = new QTreeWidgetItem(treeItem);
        treeItem2->setText(0, "name");
        treeItem2->addChild(treeItem2);*/
        Projet::Iterator Ip = p.getIterator();
        while(!Ip.isDone())
        {
            this->addTreeChild(treeItem, Ip.current().Tache::getTitre());
            TacheManager &m = TacheManager::getInstance();
            ui->Display->appendPlainText( m.getTache(Ip.current().getId()).afficherTache());
            Ip.next();
        }
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, QString name)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(parent);
        // QTreeWidgetItem::setText(int column, const QString & text)
        treeItem->setText(0, name);
        // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
        parent->addChild(treeItem);
        TacheManager &m = TacheManager::getInstance();
        qDebug()<<"erreur 1";
        qDebug()<<"erreur 1.5";
        TacheComposite* tc =dynamic_cast<TacheComposite*>(m.trouverTache(name));
        qDebug()<<"erreur 2";
        if(tc != 0)
        {
            qDebug()<<"erreur 3";
            TacheComposite::Iterator it=tc->getIteratorComposite();
            qDebug()<<"erreur 3bis";
            while (!it.isDone())
            {
                qDebug()<<"erreur 3.3";
                this->addTreeChild(treeItem,it.current().Tache::getTitre());
                it.next();
                qDebug()<<"erreur 3.7";
            }
            qDebug()<<"erreur 4";
        }

}

void MainWindow::treeGestion()
{

    ProjetManager &p = ProjetManager::getInstance();

    ProjetManager::Iterator Ip = p.getIterator();
    ui->ProjetDisplay->clear();

    while(!Ip.isDone())
    {
        this->addTreeRoot(Ip.current().getTitre(), Ip.current());
        Ip.next();
    }
}

void MainWindow::afficherEvents()
{
    //retour [8] = {0, 24, this->debut.dayOfWeek()-1, this->fin.dayOfWeek()-1, this->debut.weekNumber(),this->fin.weekNumber(), this->debut.month(), this->debut.year() };
    EventManager &e = EventManager::getInstance();
    EventManager::Iterator it = e.getIterator();
    int buf[8];
    QDate comp = ui->CalendarDate->date();
    while(!it.isDone())
    {
        it.current().afficher(buf);

        if(buf[4] == comp.weekNumber() || buf[5] == comp.weekNumber() ){
            if(buf[6] == comp.month() ){
                if(buf[7] == comp. year()){
                    for(int h = buf[0]; h <= buf[1]-1; h++){
                        for(int d = buf[2]; d < buf[3]; d++){
                            ui->Calendar->item(h, d)->setBackgroundColor(Qt::green);
                        }
                    }
                }
            }
        }
        it.next();
    }
}







/*

void MainWindow::on_printTache_clicked()
{
    ui->Display->clear();
    TacheManager &m = TacheManager::getInstance();
    ui->Display->appendPlainText(m.getTache(ui->tacheId->text()).Tache::afficherTache());
    update();
}



void MainWindow::on_ajouterProjet_pressed()
{
    ProjetManager &p = ProjetManager::getInstance();
    p.ajouterProjet(ui->Idprojet->text(), ui->titre->text());
}

*/
void MainWindow::on_ajoutEvent_clicked()
{
    EventManager &e = EventManager::getInstance();
    if(ui->event1j->isChecked() && !ui->eventpj->isChecked() && !ui->rdv->isChecked())
    {
        e.ajouterEvent(ui->idevent->text(), ui->titreevent->text(), ui->dureeevnt->value(), ui->datedebevent->date() );
    }
    else if(!ui->event1j->isChecked() && ui->eventpj->isChecked() && !ui->rdv->isChecked())
    {
        e.ajouterEvent(ui->idevent->text(), ui->titreevent->text(), ui->dureeevnt->value(), ui->datedebevent->date() , ui->datefinevent->date() );
    }
    else if(!ui->event1j->isChecked() && !ui->eventpj->isChecked() && ui->rdv->isChecked())
    {
        e.ajouterEvent(ui->idevent->text(), ui->titreevent->text(), ui->dureeevnt->value(), ui->datedebevent->date() , ui->timedebutevent->time(), ui->timefinevent->time() );
    }
    this->update();
}
/*
<<<<<<< HEAD
*/


/*void MainWindow::on_addtachetoproject_clicked()
{
    ProjetManager &p = ProjetManager::getInstance();

    p.ajouterTache(ui->tacheId->text(), ui->Idprojet->text());
}*/


/*
void MainWindow::on_MainWindow_quit()
{
    TacheManager &m = TacheManager::getInstance();
    //m.viderTaches();
}*/

void MainWindow::on_addProg_clicked()
{
    ProgrammationManager &p = ProgrammationManager::getInstance();
    TacheManager &m = TacheManager::getInstance();
    p.ajouterProgrammation(m.getTache(ui->progId->text()), ui->progDate->date(), ui->progHoraire->time(), ui->Progfin->time());
    this->update();
}

void MainWindow::on_CalendarNext_clicked()
{
    ui->CalendarDate->setDate(ui->CalendarDate->date().addDays(7));
    this->update();
}

void MainWindow::on_CalendarPrevious_clicked()
{
    ui->CalendarDate->setDate(ui->CalendarDate->date().addDays(-7));
    this->update();

}


//*********************************************************************CalendarWidgget***********************************************************************************





void MainWindow::on_addProjet_pressed()
{
    try
    {
        ProjetManager &pm=ProjetManager::getInstance();
        pm.ajouterProjet(ui->titreProjet->text());
    } catch(CalendarException e)
    {
        qDebug()<<e.getInfo();
    }
    update();
}

void MainWindow::on_ajouterTache_pressed()
{
    try
    {
        TacheManager &tm=TacheManager::getInstance();
        if (ui->UnitaireTache->isChecked())
        {
            int dur = ui->dureeTache->value();
            Duree d(dur/60,dur%60);
            tm.ajouterTacheUnitaire(ui->CheminTache->text(),ui->idTache->text(),ui->titreTache->text(),ui->titreTache->text(),ui->disponibiliteTache->date(),ui->echeanceTache->date(),d,ui->preempteTache->isChecked());
        }
        if (ui->CompositeTache->isChecked())
            tm.ajouterTacheComposite(ui->CheminTache->text(),ui->idTache->text(),ui->titreTache->text(),ui->disponibiliteTache->date(),ui->echeanceTache->date());
    ui->Display->clear();
    ui->Display->appendPlainText(tm.getTache(ui->idTache->text()).afficherTache());
    update();
    } catch(CalendarException e)
    {
        qDebug()<<e.getInfo();
    }
}

void MainWindow::on_printTache_pressed()
{
    ui->Display->clear();
    TacheManager &m = TacheManager::getInstance();
    ui->Display->appendPlainText(m.getTache(ui->tacheId->text()).afficherTache());
    update();
}


void MainWindow::on_ajoutPrecedance_pressed()
{
    TacheManager &p=TacheManager::getInstance();
    p.getTache(ui->suivanteTache->text()).ajouterContraintePrecedance(p.getTache(ui->precedenteTache->text()));
}
