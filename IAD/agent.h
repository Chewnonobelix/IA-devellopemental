#ifndef AGENT_H
#define AGENT_H

#include <QFile>
#include <QList>
#include "resultat.h"
#include "experience.h"
#include "systememotivationnel.h"
#include "environnement.h"

class Agent1
{
private:

protected:
    SystemeMotivationnel m_motivation;
    QList<Interaction*> m_trace;
    QMap<int, Experience> m_exp;
    const Environnement& m_environnement;
    int m_motivationScore;
    QString m_fileName;
    void save();

public:
    Agent1(const Environnement&, QString , int = 2);
    virtual ~Agent1();

    Resultat chooseResult() const;
    virtual Experience chooseExperience(const Resultat&) const;
    void addMotivation(const Interaction&);
    virtual bool apprentissage(const Interaction*, const Interaction*);
};

#endif // AGENT_H
