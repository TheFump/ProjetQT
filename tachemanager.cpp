#include "tachemanager.h"
#include "tachecomposite.h"
#include "tacheunitaire.h"
#include "projetmanager.h"
#include "programmationmanager.h"


TacheManager::TacheManager():taches(0),nb(0),nbMax(0){}

TacheManager TacheManager::m_instance = TacheManager();

TacheManager &TacheManager::getInstance()
{
    return m_instance;
}

void TacheManager::addItem(Tache* t){
    if (nb==nbMax){
        Tache** newtab=new Tache*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=taches[i];
        // ou memcpy(newtab,taches,nb*sizeof(Tache*));
        nbMax+=10;
        Tache** old=taches;
        taches=newtab;
        delete[] old;
    }
    taches[nb++]=t;
}

Tache* TacheManager::trouverTache(const QString& t)const{
    for(unsigned int i=0; i<nb; i++)
        if (t==taches[i]->getId()) return taches[i];
    return 0;
}

void TacheManager::ajouterTacheUnitaire(const QString chemin, const QString& id, const QString& i, const QString& t, const QDate& dispo, const QDate& deadline, const Duree& d, bool p)
{
    if (trouverTache(t))
        throw CalendarException("erreur, TacheManager, tache deja existante");
    QStringList cheminformate=chemin.split('/');
    qDebug()<<"point 1";
    TacheUnitaire* newTache = new TacheUnitaire(id,i,t,dispo,deadline,d,p);
    qDebug()<<"point 2";
    ProjetManager pm = ProjetManager::getInstance();
    qDebug()<<"point 3";
    pm.ajouterTache(cheminformate,*newTache);
    qDebug()<<"point 4";
    addItem(newTache);
    qDebug()<<"point 5";
    //ProgrammationManager::getInstance().ajouterTacheAProgrammer(*newTache);
}

void TacheManager::ajouterTacheComposite(const QString chemin,const QString& id, const QString& t, const QDate& dispo, const QDate& deadline)
{
    if (trouverTache(t))
        throw CalendarException("erreur, TacheManager, tache deja existante");
    QStringList cheminformate=chemin.split('/');
    TacheComposite* newTache= new TacheComposite(id,t,dispo,deadline);
    ProjetManager pm = ProjetManager::getInstance();
    pm.ajouterTache(cheminformate,*newTache);
    addItem(newTache);
}


Tache& TacheManager::getTache(const QString& id){
    Tache* t=trouverTache(id);
    if (!t) throw CalendarException("erreur, TacheManager, tache inexistante");
    return *t;
}

//const Tache& TacheManager::getTache(const QString& id)const{
//    return const_cast<TacheManager*>(this)->getTache(id);
//}

//TacheManager::~TacheManager(){
//    if (file!="") save(file);
//    for(unsigned int i=0; i<nb; i++) delete taches[i];
//    delete[] taches;
//    file="";
//}

//void  TacheManager::save(const QString& f){
//    file=f;
//    QFile newfile( file);
//    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
//        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
//    QXmlStreamWriter stream(&newfile);
//    stream.setAutoFormatting(true);
//    stream.writeStartDocument();
//    stream.writeStartElement("taches");
//    for(unsigned int i=0; i<nb; i++){
//        stream.writeStartElement("tache");
//        stream.writeAttribute("preemptive", (taches[i]->isPreemptive())?"true":"false");
//        stream.writeTextElement("identificateur",taches[i]->getId());
//        stream.writeTextElement("titre",taches[i]->getTitre());
//        stream.writeTextElement("disponibilite",taches[i]->getDateDisponibilite().toString(Qt::ISODate));
//        stream.writeTextElement("echeance",taches[i]->getDateEcheance().toString(Qt::ISODate));
//        QString str;
//        str.setNum(taches[i]->getDuree().getDureeEnMinutes());
//        stream.writeTextElement("duree",str);
//        stream.writeEndElement();
//    }
//    stream.writeEndElement();
//    stream.writeEndDocument();
//    newfile.close();
//}

//void TacheManager::viderTaches()
//{
//    for(unsigned int i=0; i<nb; i++) delete taches[i];
//    delete[] taches;
//}

//void TacheManager::load(const QString& f){
//    //qDebug()<<"debut load\n";
//    this->~TacheManager();
//    file=f;
//    QFile fin(file);
//    // If we can't open it, let's show an error message.
//    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        throw CalendarException("Erreur ouverture fichier tâches");
//    }
//    // QXmlStreamReader takes any QIODevice.
//    QXmlStreamReader xml(&fin);
//    //qDebug()<<"debut fichier\n";
//    // We'll parse the XML until we reach end of it.
//    while(!xml.atEnd() && !xml.hasError()) {
//        // Read next element.
//        QXmlStreamReader::TokenType token = xml.readNext();
//        // If token is just StartDocument, we'll go to next.
//        if(token == QXmlStreamReader::StartDocument) continue;
//        // If token is StartElement, we'll see if we can read it.
//        if(token == QXmlStreamReader::StartElement) {
//            // If it's named taches, we'll go to the next.
//            if(xml.name() == "taches") continue;
//            // If it's named tache, we'll dig the information from there.
//            if(xml.name() == "tache") {
//                qDebug()<<"new tache\n";
//                QString identificateur;
//                QString titre;
//                QDate disponibilite;
//                QDate echeance;
//                Duree duree;
//                bool preemptive;

//                QXmlStreamAttributes attributes = xml.attributes();
//                /* Let's check that Task has attribute. */
//                if(attributes.hasAttribute("preemptive")) {
//                    QString val =attributes.value("preemptive").toString();
//                    preemptive=(val == "true" ? true : false);
//                }
//                //qDebug()<<"preemptive="<<preemptive<<"\n";

//                xml.readNext();
//                //We're going to loop over the things because the order might change.
//                //We'll continue the loop until we hit an EndElement named tache.


//                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
//                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
//                        // We've found identificteur.
//                        if(xml.name() == "identificateur") {
//                            xml.readNext(); identificateur=xml.text().toString();
//                            //qDebug()<<"id="<<identificateur<<"\n";
//                        }

//                        // We've found titre.
//                        if(xml.name() == "titre") {
//                            xml.readNext(); titre=xml.text().toString();
//                            //qDebug()<<"titre="<<titre<<"\n";
//                        }
//                        // We've found disponibilite
//                        if(xml.name() == "disponibilite") {
//                            xml.readNext();
//                            disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
//                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
//                        }
//                        // We've found echeance
//                        if(xml.name() == "echeance") {
//                            xml.readNext();
//                            echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
//                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
//                        }
//                        // We've found duree
//                        if(xml.name() == "duree") {
//                            xml.readNext();
//                            duree.setDuree(xml.text().toString().toUInt());
//                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
//                        }
//                    }
//                    // ...and next...
//                    xml.readNext();
//                }
//                //qDebug()<<"ajout tache "<<identificateur<<"\n";
//                ajouterTache(identificateur,titre,duree,disponibilite,echeance,preemptive);

//            }
//        }
//    }
//    // Error handling.
//    if(xml.hasError()) {
//        throw CalendarException("Erreur lecteur fichier taches, parser xml");
//    }
//    // Removes any device() or data from the reader * and resets its internal state to the initial state.
//    xml.clear();
//    //qDebug()<<"fin load\n";
//}
