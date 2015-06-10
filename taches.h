#ifndef TACHES
#define TACHES

#include <QString>
#include <QDate>

#include "duree.h"
#include "calendarexception.h"



/*! \class Tache
        \brief Classe permettant de définir des taches
*/
class Tache{

    friend class TacheManager;

protected:
    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;

    Tache** tabPredecesseur;
    unsigned int nbp;
    unsigned int nbpMax;

    Tache** tabSuccesseur;
    unsigned int nbs;
    unsigned int nbsMax;

    bool isPredecesseur(Tache& t);
    bool isSuccesseur(Tache& t);
    void ajouterPredecesseur(Tache& t);
    void ajouterSuccesseur(Tache& t);

public:

    Tache(const QString& id,const QString& t, const QDate& dispo, const QDate& deadline);
    virtual ~Tache() { delete[] tabPredecesseur; delete[] tabSuccesseur; }
    virtual QString afficherTache();
    virtual void ajouterContraintePrecedance(Tache& t);

    const QString& getId() const { return identificateur; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString t) { titre=t; }
    const QDate& getDateDisponibilite() const {  return disponibilite; }//<!Retourne la disponibilité
    const QDate& getDateEcheance() const {  return echeance; }//<!Retourne l'echeance
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e);


    class Iterator {
            friend class Tache;
            friend class TacheComposite;
            friend class TacheUnitaire;
            Tache** currentTache;
            unsigned int nbRemain;
            Iterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
        public:
            Iterator():nbRemain(0),currentTache(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw CalendarException("error, next on an iterator which is done");
                nbRemain--;
                currentTache++;
            }
            Tache& current() const {
                if (isDone())
                    throw CalendarException("error, indirection on an iterator which is done");
                return **currentTache;
            }
        };

    Iterator getIteratorPredecesseur() { return Iterator(tabPredecesseur,nbp); }
    Iterator getIteratorSuccesseur() { return Iterator(tabSuccesseur,nbs); }
};


//QTextStream &operator<<(QTextStream &f, const Tache &t);

#endif // TACHES

bool operator==(const Tache& t1, const Tache& t2);
