#include "projetmanager.h"
#include "projet.h"

ProjetManager::ProjetManager()
    :projets(0),nb(0),nbMax(0){}

ProjetManager ProjetManager::m_instance = ProjetManager();

ProjetManager& ProjetManager::getInstance()
{
    return m_instance;
}

void ProjetManager::addItem(Projet* p){
    if (nb==nbMax){
        Projet** newtab=new Projet*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=projets[i];
        // ou memcpy(newtab,Projets,nb*sizeof(Projet*));
        nbMax+=10;
        Projet** old=projets;
        projets=newtab;
        delete[] old;
    }
    projets[nb++]=p;
}

Projet* ProjetManager::trouverProjet(const QString& t)const{
    for(unsigned int i=0; i<nb; i++)
        if (t==projets[i]->getTitre()) return projets[i];
    return 0;
}

Projet& ProjetManager::ajouterProjet(const QString& t){
    if (trouverProjet(t))
        throw CalendarException("erreur, ProjetManager, Projet deja existante");
    Projet* newp=new Projet(t);
    addItem(newp);
    return *newp;
}

Projet& ProjetManager::getProjet(const QString& n){
    Projet* p=trouverProjet(n);
    if (!p) throw CalendarException("erreur, ProjetManager, Projet inexistante");
    return *p;
}

void ProjetManager::ajouterTache(QStringList chemin,Tache& t)
{
    if (chemin.isEmpty())
        throw CalendarException("erreur ProjetManager: pas de nom de Projet");
    Projet* tmp=trouverProjet(chemin[0]);
    chemin.erase(chemin.begin());
    tmp->ajouterTache(chemin,t);
}

//const Projet& ProjetManager::getProjet(const QString& n)const{
//    return const_cast<Projet*>(this->getProjet(n);
//}

//ProjetManager::~ProjetManager(){
//    //if (file!="") save(file);
//    for(unsigned int i=0; i<nb; i++) delete projets[i];
//    delete[] projets;
//    //file="";
//}



//void ProjetManager::viderProjets()
//{
//    for(unsigned int i=0; i<nb; i++) delete projets[i];
//    delete[] projets;
//}


