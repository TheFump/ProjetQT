#include "duree.h"


void Duree::afficher(QTextStream &f) const
{
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<nb_minutes/60;
    f.setFieldWidth(0);
    f<<"H";
    f.setFieldWidth(2);
    f<<nb_minutes%60;
    f.setFieldWidth(0);
    f.setPadChar(' ');

}


QTextStream &operator<<(QTextStream &f, const Duree &d)
{
     d.afficher(f); return f;
}


QTextStream &operator>>(QTextStream &flot, Duree & d)
{
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot.status()!=QTextStream::Ok) ok=false;

    if(flot.read(1)=="H") {
        flot>>m;
        if (flot.status()!=QTextStream::Ok) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) d=Duree(h,m);
    return flot;
}
