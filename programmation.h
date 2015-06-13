#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QTime>
#include <QDate>

class TacheUnitaire;


class Programmation {
    friend class ProgrammationManager;
protected:

    const TacheUnitaire* tache;
    QDate date;
    QTime horaire;
    QTime fin;
public:
    Programmation(TacheUnitaire& t, const QDate& d, const QTime& h, const QTime& f);
    const TacheUnitaire& getTache() const { return *tache; }
    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
    QTime getfin() const {return fin;}

};

#endif // PROGRAMMATION_H
