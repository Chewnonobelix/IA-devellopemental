#ifndef INTERACTION_H
#define INTERACTION_H

#include <QMultiMap>
#include <QDebug>
#include <QList>;
#include <QTextStream>

#include "resultat.h"
#include "experience.h"

class Interaction;

class Interaction
{
private:
    Experience m_experience;
    Resultat m_resultat;
    int m_motiv;
    int m_poid;

    QList<Interaction*> m_prec;

public:
    Interaction(const Experience = Experience(), const Resultat = Resultat(), int = 0);// Experience, resultat, motiv
    Interaction(const Interaction&);
    ~Interaction();

    int poid() const;
    void setPoid(int);
    double procl() const;
    int motivation() const;
    void setMotivation(int);
    Experience experience() const;
    Resultat resultat() const;
    const QList<Interaction*>& prec() const;
    QList<Interaction*>& prec();
    bool hasPrec() const;
    void addPrec(Interaction*);
    void affichage() const;
    QString toString() const;
    bool operator == (const Interaction&) const;
    bool operator != (const Interaction&) const;
    bool operator < (const Interaction&) const;
    Interaction& operator = (const Interaction&);

    friend QTextStream& operator<< (QTextStream&, const Interaction&);
    friend QDebug& operator<< (QDebug& , const Interaction& );

};



uint qHash(const Interaction&);
#endif // INTERACTION_H
