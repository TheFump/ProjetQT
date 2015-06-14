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
    ui->ProjetDisplay->setColumnCount(1);
    QStringList headers;
    headers << tr("Arborecence des Projets");
    ui->ProjetDisplay->setHeaderLabels(headers);

}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::update()
{

    ui->Display->clear();
    this->afficherCalendar();
    this->treeGestion();
    this->afficherEvents();
    this->afficherTacheRestanteProgrammer();
}

void MainWindow::afficherCalendar()
{
    ProgrammationManager &p = ProgrammationManager::getInstance();
    ProgrammationManager::Iterator i = p.getIterator();
    QDate comp = ui->CalendarDate->date();
    for(int i =0; i < 24; i++){
        for(int j =0; j < 7; j++){
            ui->Calendar->item(i, j)->setBackgroundColor(Qt::white);
            ui->Calendar->item(i, j)->setText("");
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
        ui->Calendar->item(i, date)->setText(p.getTache().Tache::getTitre());
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
        TacheComposite* tc =dynamic_cast<TacheComposite*>(m.trouverTache(name));
        if(tc != 0)
        {
            TacheComposite::Iterator it=tc->getIteratorComposite();
            while (!it.isDone())
            {
                this->addTreeChild(treeItem,it.current().Tache::getTitre());
                it.next();
            }
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
                            ui->Calendar->item(h, d)->setText(it.current().getTitre());
                        }
                    }
                }
            }
        }
        it.next();
    }
}

void MainWindow::afficherTacheRestanteProgrammer()
{
    ui->TacheAProgrammer->clear();
    TacheManager &t = TacheManager::getInstance();
    for(TacheManager::Iterator it=t.getIterator(); !it.isDone(); it.next())
    {
        TacheUnitaire* tu =dynamic_cast<TacheUnitaire*>(&(it.current()));
        if(tu != 0 && tu->getDureeRestante().getDureeEnMinutes()!=0)
        {
            ui->TacheAProgrammer->addItem(tu->Tache::getTitre());
        }
    }
}

void MainWindow::on_ajoutEvent_clicked()
{
    try
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
    }catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }
}

/*
void MainWindow::on_MainWindow_quit()
{
    TacheManager &m = TacheManager::getInstance();
    //m.viderTaches();
}*/

void MainWindow::on_addProgTache_clicked()
{
    try
    {
        ProgrammationManager &p = ProgrammationManager::getInstance();
        TacheManager &m = TacheManager::getInstance();
        TacheUnitaire& tu = dynamic_cast<TacheUnitaire&>(m.getTache(ui->TacheAProgrammer->currentText()));
        if (&tu == 0)
            throw CalendarException("Ereur MainWindow: conversion en TacheUnitaire impossible");
        p.ajouterProgrammation(tu, ui->progDate->date(), QTime(ui->progHdebut->time().hour(),0), QTime(ui->progHfin->time().hour(),0));
        this->update();
    }catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }
}

void MainWindow::on_CalendarNext_clicked()
{
    ui->CalendarDate->setDate(ui->CalendarDate->date().addDays(7));
    update();
}

void MainWindow::on_CalendarPrevious_clicked()
{
    ui->CalendarDate->setDate(ui->CalendarDate->date().addDays(-7));
    update();

}

void MainWindow::on_addProjet_pressed()
{
    try
    {
        ProjetManager &pm=ProjetManager::getInstance();
        pm.ajouterProjet(ui->titreProjet->text());
        update();
    } catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }

}

void MainWindow::on_ajouterTache_pressed()
{
    try
    {
        TacheManager &tm=TacheManager::getInstance();
        // Tache Unitaire
        if (ui->UnitaireTache->isChecked())
            tm.ajouterTacheUnitaire(ui->CheminTache->text(),ui->idTache->text(),ui->titreTache->text(),ui->titreTache->text(),ui->disponibiliteTache->date(),ui->echeanceTache->date(),Duree(ui->dureeTache->value(),0),ui->preempteTache->isChecked());
        // Tache Composite
        if (ui->CompositeTache->isChecked())
            tm.ajouterTacheComposite(ui->CheminTache->text(),ui->idTache->text(),ui->titreTache->text(),ui->disponibiliteTache->date(),ui->echeanceTache->date());
        update();
        ui->Display->appendPlainText(tm.getTache(ui->idTache->text()).afficherTache());
    } catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }
}

void MainWindow::on_printTache_pressed()
{
    try
    {
        ui->Display->clear();
        TacheManager &m = TacheManager::getInstance();
        ui->Display->appendPlainText(m.getTache(ui->tacheId->text()).afficherTache());
    } catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }
}


void MainWindow::on_ajoutPrecedance_pressed()
{
    try
    {
        TacheManager &p=TacheManager::getInstance();
        p.getTache(ui->suivanteTache->text()).ajouterContraintePrecedance(p.getTache(ui->precedenteTache->text()));
    } catch(CalendarException e)
    {
        QMessageBox::warning(this,"Erreur",e.getInfo());
    }
}
