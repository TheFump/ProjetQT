#include "taches.h"
#include "calendarexception.h"

#include <qdebug.h>

Tache::Tache(const QString& id,const QString& t, const QDate& dispo, const QDate& deadline)
    : identificateur(id),titre(t),tabPredecesseur(0),nbp(0),nbpMax(0),tabSuccesseur(0),nbs(0),nbsMax(0)
{
    setDatesDisponibiliteEcheance(dispo, deadline);
}

void Tache::setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e)
{
    //<!Définit la disponibilité et l'echeance en vérifiant que la première est bien inféreur a la seconde
    if (e<disp)
        throw CalendarException("erreur Tâche : date echéance < date disponibilité");
    disponibilite=disp;
    echeance=e;
}

/*
QTextStream &operator<<(QTextStream &f, const Tache &t)
{
    f<<t.getTitre().toStdString()<<"\n";
    f<<t.getDateDisponibilite().toString(<<"\n";
    f<<t.getDateEcheance().toString(<<"\n";
    return f;

}*/


QString Tache::afficherTache()
{
    QString text;
    text.append("Description de la tache : \n");
    text.append("Id : " + getId() + "\n");
    text.append("Disponibilite : " + getDateDisponibilite().toString() + "\n");
    text.append("Echeance : " + getDateEcheance().toString() + "\n");
    return text;
}

bool Tache::isPredecesseur(Tache& t)
{
    if (*this==t)
        throw CalendarException("erreur Tâche : une tache ne peut se précéder elle même");
    // la tache est  présente parmis this->tabPredecesseur
    for (Tache::Iterator it=getIteratorPredecesseur(); !it.isDone(); it.next())
        if (it.current()==t)
            return true;
    // la tache n'est pas parmis this->tabPredecesseur
    return false;
}

bool Tache::isSuccesseur(Tache& t)
{
    if (*this==t)
        throw CalendarException("erreur Tâche : une tache ne peut se précéder elle même");
    // la tache est présente parmis tabPredecesseur
    for (Tache::Iterator it=getIteratorSuccesseur(); !it.isDone(); it.next())
        if (it.current()==t)
            return true;
    return false;
}

void Tache::ajouterPredecesseur(Tache& t)
{
    // t est déja prédécesseur de this
    if (this->isPredecesseur(t))
        return;
    // la disponibilité de t commence après l'echance de this
    if (t.disponibilite>this->echeance)
        throw CalendarException("erreur Tâche : incompatibilité date et contrainte de précédance");
    // création de boucle
    if (this->isSuccesseur(t))
        throw CalendarException("erreur Tâche : boucle au niveau de la Predecesseur");
    if (nbp==nbpMax)
    {
        Tache** newtab=new Tache*[nbpMax+10];
        for(unsigned int i=0; i<nbp; i++)
            newtab[i]=tabPredecesseur[i];
        nbpMax+=10;
        Tache** old=tabPredecesseur;
        tabPredecesseur=newtab;
        delete[] old;
    }
    tabPredecesseur[nbp++]=&t;
}

void Tache::ajouterSuccesseur(Tache& t)
{
    // t est déjà successeur de this
    if (this->isSuccesseur(t))
        return;
    // la disponibilité de this commence après l'echance de t
    if (this->disponibilite>t.echeance)
        throw CalendarException("erreur Tâche : incompatibilité date et contrainte de précédance");
    // création de bouble
    if (this->isPredecesseur(t))
        throw CalendarException("erreur Tâche : boucle au niveau de la Predecesseur");
    if (nbs==nbsMax)
    {
        Tache** newtab=new Tache*[nbsMax+10];
        for(unsigned int i=0; i<nbs; i++)
            newtab[i]=tabSuccesseur[i];
        nbsMax+=10;
        Tache** old=tabSuccesseur;
        tabSuccesseur=newtab;
        delete[] old;
    }
    tabSuccesseur[nbs++]=&t;
}

void Tache::ajouterContraintePrecedance(Tache& t)
{
    // doublechainage entre les 2 taches
    ajouterPredecesseur(t);
    t.ajouterSuccesseur(*this);
    // doublechainage entre les successeurs de this et t
    for(Tache::Iterator it=getIteratorSuccesseur(); !it.isDone(); it.next())
        it.current().ajouterContraintePrecedance(t);
    // doublechainage entre les predecesseur de t et this
    for(Tache::Iterator it=t.getIteratorPredecesseur(); !it.isDone(); it.next())
        ajouterContraintePrecedance(it.current());

}

bool operator==(const Tache& t1, const Tache& t2)
{
    return(t1.getId()==t2.getId());
}







