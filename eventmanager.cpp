#include "eventmanager.h"

EventManager::EventManager():events(0),nb(0),nbMax(0){}

EventManager EventManager::m_instance = EventManager();

EventManager &EventManager::getInstance()
{
    return m_instance;
}

void EventManager::addItem(Event* t){
    if (nb==nbMax){
        Event** newtab=new Event*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=events[i];
        // ou memcpy(newtab,Events,nb*sizeof(Event*));
        nbMax+=10;
        Event** old=events;
        events=newtab;
        delete[] old;
    }
    events[nb++]=t;
}

Event* EventManager::trouverEvent(const QString& id)const{
    for(unsigned int i=0; i<nb; i++)
        if (id==events[i]->getId()) return events[i];
    return 0;
}

/*Event& EventManager::ajouterEvent(const QString& id, const QString& t, const Duree& dur){
    if (trouverEvent(id)) throw CalendarException("erreur, EventManager, Event deja existante");
    Event* newt=new Event(id,t,dur);
    addItem(newt);
    return *newt;
}*/

Evt1j &EventManager::ajouterEvent(const QString &id, const QString &t, const Duree &dur, const QDate &date)
{
    if (trouverEvent(id)) throw CalendarException("erreur, EventManager, Event deja existante");
    Evt1j* newt=new Evt1j(id,t,dur,date);
    addItem(newt);
    return *newt;
}

EvtPj &EventManager::ajouterEvent(const QString &id, const QString &t, const Duree &dur, const QDate &deb, const QDate &fin)
{
    if (trouverEvent(id)) throw CalendarException("erreur, EventManager, Event deja existante");
    EvtPj* newt=new EvtPj(id,t,dur, deb, fin);
    addItem(newt);
    return *newt;
}

Rdv &EventManager::ajouterEvent(const QString &id, const QString &t, const Duree &dur, const QDate &date, const QTime &deb, const QTime &fin)
{
    if (trouverEvent(id)) throw CalendarException("erreur, EventManager, Event deja existante");
    Rdv* newt=new Rdv(id,t,dur, date, deb, fin);
    addItem(newt);
    return *newt;
}

Event& EventManager::getEvent(const QString& id){
    Event* t=trouverEvent(id);
    if (!t) throw CalendarException("erreur, EventManager, Event inexistante");
    return *t;
}


void EventManager::afficherEvent(const QString &id, int retour [8])
{
    Event*  t= EventManager::trouverEvent(id);
    if (!t) throw CalendarException("erreur, EventManager, Event inexistante");
    t->afficher(retour);

}

void EventManager::supprimerEvent(const QString &id)
{
    if(this->isEventExistante(id))
    {
        unsigned int i = 0;
        while(!(id == events[i]->getId()) && i <= nb)
        {
            i++;
        }
        if(i <= nb)
        {
            delete events[i];
            for(unsigned int j = i; j < nb; j++) events[j] = events[j+1];
            nb--;
        }
    }
}
/*
const Event& EventManager::getEvent(const QString& id)const{
    return const_cast<EventManager*>(this)->getEvent(id);
}*/

EventManager::~EventManager(){

    for(unsigned int i=0; i<nb; i++) delete events[i];
    delete[] events;
    file="";
}
