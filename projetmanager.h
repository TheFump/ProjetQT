#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "calendarexception.h"

class Projet;
class Tache;


/** \class ProjetManager
 * @brief The ProjetManager class : gestion des projets
 */
class ProjetManager {

    friend class Projet;

public :
     int getNb(){return nb;}
    static ProjetManager& getInstance();//<! Retourne instance Projetmanager
    Projet& ajouterProjet(const QString& t);//<! ajoute un projet �  l'appli
    Projet& getProjet(const QString& t);//<! retourne une Projet via son titre
    void ajouterTache(QStringList chemin, Tache& t);
    bool isProjetExistante(const QString& t) const { return trouverProjet(t)!=0; }//retourne l'existance d'un projet
//    const Projet& getProjet(const QString& n) const;//<! récupère un projet via un nom
//    void viderProjets();//<! vide les Projets

    class Iterator {
        friend class ProjetManager;
        Projet** currentProjet;
        unsigned int nbRemain;
        Iterator(Projet** u, unsigned nb):currentProjet(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentProjet(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw CalendarException("error, next on an iterator which is done");
            nbRemain--;
            currentProjet++;
        }
        Projet& current() const {
            if (isDone())
                throw CalendarException("error, indirection on an iterator which is done");
            return **currentProjet;
        }
    };

    Iterator getIterator() {
        return Iterator(projets,nb);
    }

private :
    Projet** projets;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Projet* p);
    Projet* trouverProjet(const QString& t) const;


    static ProjetManager m_instance;
    //~ProjetManager();
    ProjetManager& operator=(ProjetManager& t);
    ProjetManager();

};


#endif // PROJETMANAGER_H
