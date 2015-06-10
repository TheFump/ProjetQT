#include "event.h"


void Evt1j::afficher(int retour[8])
{
    // retour [8] = {0, 24, this->date.dayOfWeek()-1, this->date.dayOfWeek(), this->date.weekNumber(),this->date.weekNumber(), this->date.month(), this->date.year() };
     retour [0] = 0;
     retour [1] = 23;
     retour [2] = this->date.dayOfWeek()-1;
     int test = retour [2];
     retour [3] = this->date.dayOfWeek();
      int test3 = retour [3];
     retour [4] = this->date.weekNumber();
     retour [5] = this->date.weekNumber();
     retour [6] = this->date.month();
     retour [7] = this->date.year();


     // return retour;
}

void EvtPj::afficher(int retour [8])
{

  // retour [8] = {0, 24, this->debut.dayOfWeek()-1, this->fin.dayOfWeek()-1, this->debut.weekNumber(),this->fin.weekNumber(), this->debut.month(), this->debut.year() };
   retour [0] = 0;
   retour [1] = 23;
   retour [2] = this->debut.dayOfWeek()-1;
   retour [3] = this->fin.dayOfWeek()-1;
   retour [4] = this->debut.weekNumber();
   retour [5] = this->fin.weekNumber();
   retour [6] = this->debut.month();
   retour [7] = this->debut.year();
   // return retour;
}

void Rdv::afficher(int retour [8])
{

    Evt1j::afficher(retour);
    retour [0] = this->debut.hour();
    retour [1] = this->fin.hour();

   // return retour;
}

