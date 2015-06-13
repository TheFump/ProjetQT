#include "programmation.h"
#include "tacheunitaire.h"

Programmation::Programmation(TacheUnitaire& t, const QDate& d, const QTime& h, const QTime& f):tache(&t), date(d), horaire(h), fin(f)
{
    if (h>f)
        throw CalendarException("Erreur Programmation: l'heure de fin est inférieur à l'heure de début");
    int tmp=t.getDureeRestante().getDureeEnHeures()-h.msecsTo(f)/(1000*60*60);
    Duree dur(tmp,0);
    t.setDureeRestante(dur);
}

