#ifndef Agent2_H
#define Agent2_H

#include <QFile>
#include <QList>
#include <QStack>
#include "resultat.h"
#include "experience.h"
#include "systememotivationnel.h"
#include "environnement.h"
#include "agent.h"

class Agent2: public Agent1
{
private:
     QPair<Interaction, Interaction> m_last;

public:
    Agent2(const Environnement&, QString, int = 2);
    ~Agent2();

    Resultat chooseResult() const;
    QStack<Interaction*> chooseExperience(const Resultat&);
    void addMotivation(Interaction*);
    bool apprentissage(const Interaction*, const Interaction*);
};

#endif // Agent2_H
