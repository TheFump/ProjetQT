#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include <QString>
#include <QStringList>
#include "taches.h"

class TacheComposite: public Tache
{
    friend class TacheManager;

private:
    Tache** tabSousTache;
    unsigned int nb;
    unsigned int nbMax;

    void addTache(Tache& t);
public:
    TacheComposite(const QString& id,const QString& t, const QDate& dispo, const QDate& deadline):Tache(id,t,dispo,deadline),tabSousTache(0),nb(0),nbMax(0) {}
    ~TacheComposite() { Tache::~Tache(); delete[] tabSousTache; }
    void ajouterContraintePrecedance(Tache& t);
    Tache& trouverSousTache (const QString& t);
    void ajouterSousTache(QStringList& chemin, Tache& t);
    Iterator getIteratorComposite() { return Iterator(tabSousTache,nb); }
};

#endif // TACHECOMPOSITE_H
