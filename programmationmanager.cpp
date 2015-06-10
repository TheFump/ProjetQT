#include "programmationmanager.h"


ProgrammationManager::ProgrammationManager():programmations(0),nb(0),nbMax(0){}

void ProgrammationManager::addItem(Programmation* t){
    if (nb==nbMax){
        Programmation** newtab=new Programmation*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        Programmation** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=t;
}

Programmation* ProgrammationManager::trouverProgrammation(const Tache& t)const{
    for(unsigned int i=0; i<nb; i++)
        if (&t==&programmations[i]->getTache()) return programmations[i];
    return 0;
}

void ProgrammationManager::ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h,const QTime& f){
    if (trouverProgrammation(t)) throw CalendarException("erreur, ProgrammationManager, Programmation deja existante");
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
            while(!(id == &programmations[i]->getTache().getId()) && i <= nb)
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
