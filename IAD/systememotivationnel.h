#ifndef SYSTEMEMOTIVATIONNEL_H
#define SYSTEMEMOTIVATIONNEL_H

#include "interaction.h"

class Agent;

class SystemeMotivationnel
{
    friend class Agent;
private:
    QMap<QPair<const Experience, const Resultat>, Interaction> m_systeme;

protected:

public:
    SystemeMotivationnel();
    Interaction first() const;
    QMap<QPair<const Experience, const Resultat>, Interaction> systeme() const;
    QMap<QPair<const Experience, const Resultat>, Interaction>& systeme();
    QList<Experience> exp(const Resultat&) const;
    QList<Interaction> interaction(const Experience &) const;
    Interaction& interaction(const Interaction&);
    Interaction interaction(const Experience&, const Resultat&) const;
    Interaction& interaction(const Experience&, const Resultat&);
    void add(Experience, Resultat, int);
    void affichage() const;

    bool contain(const Experience&) const;
    bool contain(const Interaction&) const;
};

class SystemeMotivationnel1: public SystemeMotivationnel
{
public:
    SystemeMotivationnel1();
};

class SystemeMotivationnel2: public SystemeMotivationnel
{
public:
    SystemeMotivationnel2();
};

class SystemeMotivationnel3: public SystemeMotivationnel
{
public:
    SystemeMotivationnel3();
};

class SystemeMotivationnel4: public SystemeMotivationnel
{
public:
    SystemeMotivationnel4();
};

#endif // SYSTEMEMOTIVATIONNEL_H
