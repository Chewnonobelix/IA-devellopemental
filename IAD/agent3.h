#ifndef AGENT3_H
#define AGENT3_H

#include "agent2.h"

class Agent3: public Agent2
{
public:
    Agent3(const Environnement&, QString, int = 2);
    ~Agent3();

    bool apprentissage(const Interaction * eff, const Interaction * exp);
    QStack<Interaction*> chooseExperience(const Resultat&);
    virtual void addMotivation(Interaction*);
};

#endif // AGENT3_H
