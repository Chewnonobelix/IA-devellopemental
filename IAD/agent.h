#ifndef AGENT_H
#define AGENT_H

#include <QFile>
#include <QList>
#include <QStack>
#include "resultat.h"
#include "experience.h"
#include "systememotivationnel.h"
#include "environnement.h"

class Agent
{
private:
    SystemeMotivationnel m_motivation;
    int m_motivationScore;
    QList<Interaction> m_trace;
    const Environnement& m_environnement;
    QMap<int, Experience> m_exp;
    QPair<Interaction, Interaction> m_last;
    void save();

public:
    Agent(const Environnement&, int = 2);
    ~Agent();

    Resultat chooseResult() const;
    QStack<Interaction> chooseExperience(const Resultat&) const;
    void addMotivation(const Interaction&);
    bool apprentissage(const Interaction&, const Interaction&);
};

#endif // AGENT_H
