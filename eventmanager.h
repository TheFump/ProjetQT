#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "event.h"


class EventManager {
    friend class Event;
    friend class Evt1j;
    friend class EvtPj;
    friend class Rdv;
private :
    Event** events;
    unsigned int nb;
    unsigned int nbMax;

    void addItem( Event* t);
     Event* trouverEvent(const QString& id) const;
    QString file;

    static  EventManager m_instance;
    ~EventManager();
    EventManager& operator= ( EventManager& t);
    EventManager();

public :
    static  EventManager& getInstance();//<! Retourne instance Eventmanager
    int getNb(){return nb;}
    //Event & ajouterEvent(const QString& id, const QString& t, const Duree& dur);//<! ajoute une tahce Ã  l'appli
    Evt1j & ajouterEvent(const QString& id, const QString& t, const Duree& dur, const QDate& date);//<! ajoute une tahce Ã  l'appli
    EvtPj & ajouterEvent(const QString& id, const QString& t, const Duree& dur, const QDate& deb, const QDate& fin);//<! ajoute une tahce Ã  l'appli
    Rdv & ajouterEvent(const QString& id, const QString& t, const Duree& dur, const QDate& date, const QTime& deb, const QTime& fin);//<! ajoute une tahce Ã  l'appli
    Event & getEvent(const QString& id);//<! retourne une Event via son id
    bool isEventExistante(const QString& id) const { return trouverEvent(id)!=0; }//retourne l'existance d'une tahce
    //const Event& getEvent(const QString& code) const;//<! rÃ©cupÃ¨re une tahce via code
    void load(const QString& f); //<! enregistre l'Ã©tat des Events
    void save(const QString& f); //charge les Events
    void viderEvent();//<! vide les Events
    void afficherEvent(const QString& id, int retour [8]);
    void supprimerEvent(const QString& id);

    class Iterator {
        friend class EventManager;
        Event** currentEvent;
        unsigned int nbRemain;
        Iterator(Event** u, unsigned nb):currentEvent(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentEvent(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            nbRemain--;
            currentEvent++;
        }
        Event& current() const {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentEvent;
        }
    };

    Iterator getIterator() {
        return Iterator(events,nb);
    }
};


#endif // EVENTMANAGER_H

