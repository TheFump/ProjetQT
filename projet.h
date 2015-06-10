#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QStringList>
#include <QDate>

#include "calendarexception.h"

class Tache;

class Projet
{
private:
    QString titre;
    QDate disponibilite;
    QDate echeance;

    Tache** tab;
    unsigned int nb;
    unsigned int nbMax;


    void addTache(Tache& t);
public:
     int getNb(){return nb;}
    Projet(const QString& t):titre(t),disponibilite(QDate::currentDate()),echeance(QDate::currentDate()),tab(0),nb(0),nbMax(0) {}
    ~Projet() {delete[] tab; }
    QString afficherProjet();
    Tache& trouverTache(const QString& t);
    void ajouterTache(QStringList& chemin,Tache& t);

    QString getTitre() const { return titre; }
    QDate getDisponibilite() const { return disponibilite; }
    QDate getEcheance() const { return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e);


    class Iterator {
        friend class Projet;
        Tache** currentTache;
        unsigned int nbRemain;
        Iterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentTache(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            nbRemain--;
            currentTache++;
        }
        Tache& current() const {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentTache;
        }
    };

    Iterator getIterator() { return Iterator(tab,nb); }
};

#endif // PROJET_H
