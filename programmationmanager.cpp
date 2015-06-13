#include "programmationmanager.h"
#include "tacheunitaire.h"
#include "eventmanager.h"


ProgrammationManager::ProgrammationManager():programmations(0),nb(0),nbMax(0){}

void ProgrammationManager::addItem(Programmation* p){
    if (nb==nbMax){
        Programmation** newtab=new Programmation*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        Programmation** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=p;
}

Programmation* ProgrammationManager::trouverProgrammation(const TacheUnitaire& e)const{
    for(unsigned int i=0; i<nb; i++)
        if (&e==&programmations[i]->getTache()) return programmations[i];
    return 0;
}

void ProgrammationManager::ajouterProgrammation(TacheUnitaire& t, const QDate& d, const QTime& h,const QTime& f){
    // durée programmé supérieur a la durée restante
    if (t.getDureeRestante().getDureeEnMinutes() < h.msecsTo(f)/(1000*60))
        throw CalendarException("Erreur ProgrammationManager: duree restante à programmer < duree programmé");
    // cas non préemté: la programmation doit se faire en une fois
    if (t.getPreempte()==false && t.getDureeRestante().getDureeEnMinutes() != h.msecsTo(f)/(1000*60))
        throw CalendarException("Erreur ProgrammationManager: la totalite de la tache doit se programmer en une fois");
    // respect des dates de programmations par rapport à ma tache
    if (t.getDateDisponibilite()>d || t.getDateEcheance()<d)
        throw CalendarException("Erreur ProgrammationManager: la date programmé de la tache ne respecte les dates de la Tache");
    // controle chevauchement avec un event
//    EventManager &em=EventManager::getInstance();
//    for(EventManager::Iterator it=em.getIterator(); !it.isDone(); it.next())
//        if (it.current().get()==d && ((h>it.current().getHoraire() && h<it.current().getfin()) || (f>it.current().getHoraire() && f<it.current().getfin())))
//            throw CalendarException("Erreur ProgrammationManager: la programmation chevauche un evènement déjà programmé");
    // controle du chevauchement de 2 taches + respect contrainte precedance
    for(ProgrammationManager::Iterator it=getIterator(); !it.isDone(); it.next())
    {
        //chevauchement de 2 taches
        if (it.current().getDate()==d && ((h>=it.current().getHoraire() && h<it.current().getfin()) || (f>it.current().getHoraire() && f<=it.current().getfin())))
            throw CalendarException("Erreur ProgrammationManager: la programmation chevauche un evènement déjà programmé");
        // contrainte precedance
        for(Tache::Iterator itpred=t.getIteratorPredecesseur(); !itpred.isDone(); itpred.next())
            if((it.current().getTache()==itpred.current()) && d<=it.current().getDate() && h<=it.current().getfin())
                throw CalendarException("Erreur ProgrammationManager: les contrainte de précedance ne sont pas respecté1");
        // contrainte succession
        for(Tache::Iterator itsuc=t.getIteratorSuccesseur(); !itsuc.isDone(); itsuc.next())
            if(it.current().getTache()==itsuc.current() && d>=it.current().getDate() && h>=it.current().getfin())
                throw CalendarException("Erreur ProgrammationManager: les contrainte de précedance ne sont pas respecté");
    }
    Programmation* newt=new Programmation(t,d,h ,f);
    addItem(newt);
}



ProgrammationManager ProgrammationManager::m_instance = ProgrammationManager();

ProgrammationManager &ProgrammationManager::getInstance()
{
    return m_instance;
}

void ProgrammationManager::supprimerProgrammation(const QString &id)
{

        if(nb > 0)
        {
            unsigned int i = 0;
            while(!(id == &programmations[i]->getTache().Tache::getId()) && i <= nb)
            {
                i++;
            }
            if(i <= nb)
            {
                delete programmations[i];
                for(unsigned int j = i; j < nb; j++) programmations[j] = programmations[j+1];
                nb--;
            }
        }

}


ProgrammationManager::~ProgrammationManager(){
    for(unsigned int i=0; i<nb; i++) delete programmations[i];
    delete[] programmations;
}

ProgrammationManager::ProgrammationManager(const ProgrammationManager& um):nb(um.nb),nbMax(um.nbMax), programmations(new Programmation*[um.nb]){
    for(unsigned int i=0; i<nb; i++) programmations[i]=new Programmation(*um.programmations[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& um){
    if (this==&um) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<um.nb; i++) addItem(new Programmation(*um.programmations[i]));
    return *this;
}
