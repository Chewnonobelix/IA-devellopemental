#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <QList>
#include <QPair>
#include <QMultiMap>
#include <QString>

#include "resultat.h"
#include "experience.h"
#include "interaction.h"

class Environnement
{
private:
    QList<QPair<int, int>> m_liste; //first experience, second resultat

protected:
    int size() const;
    void addPair(int, int);
    bool removePair(int, int);
    QMap<int, Resultat> m_resultat;
    QMap<int, Experience> m_experience;
    virtual void appliqueTransfo(Experience, Resultat);

public:
    Environnement(int, int);
    Resultat result(const Experience&);
    const QMap<int, Experience>& experience() const;
    const Resultat &resultat(int) const;
    const Experience& experience(int) const;
    int nbExperience() const;
    int nbResulat() const;
    void affichage() const;
};


class Environnement1: public Environnement
{
public:
    Environnement1();
};

class Environnement2: public Environnement
{
public:
    Environnement2();
};

class Environnement3: public Environnement
{
protected:
    void appliqueTransfo(Experience, Resultat);
public:
    Environnement3();
};

class Environnement4: public Environnement
{
private:
    int m_turn;

protected:
    void appliqueTransfo(Experience, Resultat);

public:
    Environnement4();
};

#endif // ENVIRONNEMENT_H
