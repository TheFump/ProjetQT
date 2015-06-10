#ifndef EVENT_H
#define EVENT_H

#include <QTextStream>
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include "duree.h"
#include <QString>


class Event {
    friend class EventManager;
protected:
    QString identificateur;
    QString titre;
    Duree duree;
    Event(){}
    Event(const QString& id, const QString& t, const Duree& dur):identificateur(id), titre(t), duree(dur){}

public :

    QString getId() const { return identificateur; }//<!Retourne l'identificateur
    void setId(const QString& str){
        //if (TacheManager::getInstance().isTacheExistante((str))) throw CalendarException("erreur TacheManager : tache id déj�  existante");
        identificateur=str;
    }
    QString getTitre() const { return titre; }//<!Retourne le titre
    void setTitre(const QString& str) { titre=str; }//<!Définir le titre
    Duree getDuree() const { return duree; }//<!Retourne la durée
    void setDuree(const Duree& d) { duree=d; }//<!Défini la durée
    virtual void afficher(int retour [8]) = 0;
};

class Evt1j  : public Event{
     friend class EventManager;
protected:
    QDate date;

    Evt1j(const QString& id, const QString& t, const Duree& dur, const QDate& date):Event(id, t, dur), date(date){}
public:
    QDate getDate() const { return date; }//<!Retourne le titre
    void setDate(const QDate& str) { date=str; }//<!Définir le titre
    void afficher(int retour [8]);
};

class EvtPj  : public Event{
     friend class EventManager;
protected:
    QDate debut;

    QDate fin;
    EvtPj(const QString& id, const QString& t, const Duree& dur, const QDate& deb, const QDate& fin):Event(id, t, dur), debut(deb), fin(fin) {}
public:
    QDate getdebut() const { return debut; }//<!Retourne le titre
    void setdebut (const QDate& str){ debut=str; } //<!Définir le titre
    QDate getFin() const { return fin; }//<!Retourne le titre
    void setFin (const QDate& str){ debut=str; } //<!Définir le titre
    void afficher(int  retour [8]);
};

class Rdv : public Evt1j{
     friend class EventManager;
protected:
    QTime debut;
    QTime fin;

    Rdv(const QString& id, const QString& t, const Duree& dur,const QDate& date, const QTime& deb, const QTime& fin):Evt1j(id, t, dur, date), debut(deb), fin(fin){}
public:
    QTime getdebut() const { return debut; }//<!Retourne le titre
    void setdebut (const QTime& str){ debut=str; } //<!Définir le titre
    QTime getFin() const { return fin; }//<!Retourne le titre
    void setFin (const QTime& str){ debut=str; } //<!Définir le titre
    void afficher(int  retour [8]);
};





#endif // EVENT_H
