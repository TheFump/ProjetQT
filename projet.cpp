#include "projet.h"
#include "taches.h"
#include "tachecomposite.h"

void Projet::setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e)
{
    //<!Définit la disponibilité et l'echeance en vérifiant que la première est bien inféreur a la seconde
    if (e<disp)
        throw CalendarException("erreur Tâche : date echéance < date disponibilité");
    disponibilite=disp;
    echeance=e;
}

 QString Projet::afficherProjet()
 {
     QString text;
     text.append("Description du porjet : \n");
     text.append("titre : " + getTitre() + "\n");
     text.append("disponibilite : " + getDisponibilite().toString() + "\n");
     text.append("echeance : " + getEcheance().toString() + "\n");
     return text;
 }

 void Projet::addTache(Tache& t){
     if (nb==nbMax){
         Tache** newtab=new Tache*[nbMax+10];
         for(unsigned int i=0; i<nb; i++)
             newtab[i]=tab[i];
         nbMax+=10;
         Tache** old=tab;
         tab=newtab;
         delete[] old;
     }
     tab[nb++]=&t;
}

Tache& Projet::trouverTache(const QString& t)
{
    for(Projet::Iterator it=getIterator(); !it.isDone(); it.next())
        if (it.current().getId() == t)
            return it.current();
    throw CalendarException("erreur projet: le chemin pour ajouter une tache n'existe pas");
}

void Projet::ajouterTache(QStringList& chemin,Tache& t)
{
    // maj de disponibilite si besoin
    if (getDisponibilite()>t.getDateDisponibilite())
        setDatesDisponibiliteEcheance(t.getDateDisponibilite(),getEcheance());
    // maj de echeance si besoin
    if (getEcheance()<t.getDateEcheance())
        setDatesDisponibiliteEcheance(getDisponibilite(),t.getDateEcheance());
    // tache a la racine du projet
    if (chemin.isEmpty())
        addTache(t);
    // tache dans une sous-tache
    else
    {
        // Vérifier que tmp est bien une TacheComposite
        TacheComposite& tmp=dynamic_cast<TacheComposite&>(trouverTache(chemin[0]));
        if (&tmp)
        {
            chemin.erase(chemin.begin());
            tmp.ajouterSousTache(chemin,t);
        }
        else
            throw CalendarException("erreur projet: le chemin pour ajouter une tache passe par une tache unitaire");
    }
}

/*Projet::~Projet()
{
    for(unsigned int i=0; i<nb; i++)
        delete tab[i];
    delete[] tab;
}*/
