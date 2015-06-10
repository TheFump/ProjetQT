#include "tachecomposite.h"


void TacheComposite::addTache(Tache& t){
    if (nb==nbMax){
        Tache** newtab=new Tache*[nbMax+10];
        for(unsigned int i=0; i<nb; i++)
            newtab[i]=tabSousTache[i];
        nbMax+=10;
        Tache** old=tabSousTache;
        tabSousTache=newtab;
        delete[] old;
    }
    tabSousTache[nb++]=&t;
}

Tache& TacheComposite::trouverSousTache (const QString& t)
{
    for(Tache::Iterator it=getIteratorComposite(); !it.isDone(); it.next())
        if (it.current().getTitre()==t)
            return it.current();
    throw CalendarException("erreur TâcheComposite : tache recherché non présente parmis les sous-taches");
}

void TacheComposite::ajouterSousTache(QStringList& chemin,Tache& t)
{
    // verification de la concordence des dates
    if (t.getDateDisponibilite()<getDateDisponibilite() || t.getDateEcheance()>getDateEcheance())
        throw CalendarException("erreur TacheComposite: la tache ajouter ne concorde pas avec les dates");
    // tache a a la racine de cette tache composite
    if (chemin.isEmpty())
        addTache(t);
    // tache dans une sous-tache
    else
    {
        // Vérifier que tmp est bien une TacheComposite
        TacheComposite& tmp=dynamic_cast<TacheComposite&>(trouverSousTache(chemin[0]));
        if (&tmp)
        {
            chemin.erase(chemin.begin());
            tmp.ajouterSousTache(chemin,t);
        }
        else
            throw CalendarException("erreur projet: le chemin pour ajouter une tache passe par une tache unitaire");    }
}

void TacheComposite::ajouterContraintePrecedance(Tache& t)
{
    Tache::ajouterContraintePrecedance(t);
    for(Tache::Iterator it=getIteratorComposite(); !it.isDone(); it.next())
        it.current().ajouterContraintePrecedance(t);
}
