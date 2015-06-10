#include "tacheunitaire.h"

TacheUnitaire::TacheUnitaire(const QString& id, const QString& i, const QString& t, const QDate& dispo, const QDate& deadline, const Duree& d, bool p)
    :Event(id,i,d),Tache(id,t,dispo,deadline),preempte(p),dureeRestante(d)
{
    if(!preempte && duree.getDureeEnMinutes()>Duree(12,0).getDureeEnMinutes())
        throw CalendarException("erreur TacheUnitaire: tache non preempté et duree supérieur a 12h");
}

QString TacheUnitaire::afficherTache()
{
    QString text=Tache::afficherTache();
    text.append("Duree : " + QString::number(getDuree().getDureeEnMinutes()) + "\n");
    text.append("Preempte : " + QString::number(getPreempte()) + "\n");
    text.append("Duree restante à programmer: " + QString::number(getDureeRestante().getDureeEnMinutes()) + "\n");
    return text;
}
