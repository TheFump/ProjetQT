#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QTime>
#include <QDate>

#include "tachemanager.h"
#include "projetmanager.h"


class Programmation {
    friend class ProgrammationManager;
protected:

    const Tache* tache;
    QDate date;
    QTime horaire;
    QTime fin;
public:
    Programmation(const Tache& t, const QDate& d, const QTime& h, const QTime& f):tache(&t), date(d), horaire(h), fin(f){}
    const Tache& getTache() const { return *tache; }
    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
    QTime getfin() const {return fin;}

};

#endif // PROGRAMMATION_H
