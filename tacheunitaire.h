#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "duree.h"
#include "taches.h"
#include "event.h"

class TacheUnitaire: public Tache, public Event
{
    friend class TacheManager;

private:
    bool preempte;
    Duree dureeRestante; // la durée qui reste a programmer

public:
    TacheUnitaire(const QString& id, const QString& i, const QString& t, const QDate& dispo, const QDate& deadline, const Duree& d, bool p);
    QString afficherTache();
    void afficher(int retour [8]) {}

    const Duree& getDuree() const { return duree; }
    bool getPreempte() const { return preempte; }
    const Duree& getDureeRestante() const { return dureeRestante; }

};

#endif // TACHEUNITAIRE_H
