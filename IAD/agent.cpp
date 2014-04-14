#include "agent.h"

Agent1::Agent1(const Environnement& e, QString fileName, int nbExp): m_environnement(e), m_motivationScore(0), m_fileName(fileName)
{
    for(int i = 1; i <= nbExp; i++ )
    {
        m_exp[i] = Experience(i);;
    }

    QFile file(fileName + "_trace.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Ouverture du fichier \"trace.txt\" impossible";
        return;
    }
    file.close();
}

Agent1::~Agent1()
{
}

void Agent1::save()
{
    QFile file(m_fileName + "_trace.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug()<<"Ouverture du fichier \"trace.txt\" impossible";
        return;
    }

    const Interaction& it = *(m_trace.last());

    QString toWrite;
    toWrite = "Experience: " + QString::number(it.experience().num()) + ", ";
    toWrite += "Resultat: " + QString::number(it.resultat().num()) + ", ";
    toWrite += "Motivation: " + QString::number(it.motivation()) + ", Total = " + QString::number(m_motivationScore) + "\n";

    file.write(toWrite.toLatin1());


    file.close();
}

Resultat Agent1::chooseResult() const
{
    QMap<QPair<const Experience, const Resultat>, Interaction> temp = m_motivation.systeme();

    Resultat ret;
    int motiv = 0;
    if(!temp.isEmpty())
    {
        motiv = temp.first().motivation();
        ret = temp.first().resultat();
    }

    foreach(const Interaction& it, temp)
    {
        if(it.motivation() > motiv)
        {
            ret = it.resultat();
            motiv = it.motivation();
        }
    }

    return ret;
}

Experience Agent1::chooseExperience(const Resultat& r) const
{
    QMap<int, Experience> temp = m_environnement.experience();

    Experience ret;
    if(r.num() == 0)
    {
        ret = m_exp.first();
    }
    else
    {
        bool find = true;

        foreach (const Experience& e, m_exp)
        {
            find &= m_motivation.contain(e);
            if(!m_motivation.contain(e))
            {
                ret = e;
            }
        }

        if(find)
        {
            ret = m_motivation.exp(r)[0];
        }
    }

    return ret;
}

void Agent1::addMotivation(const Interaction& i)
{
    m_exp[i.experience().num()] = i.experience();
    m_motivation.add(i.experience(), i.resultat(), i.motivation());
    m_motivationScore += m_motivation.interaction(i.experience(), i.resultat()).motivation();
    m_trace<<&(m_motivation.interaction(i));
    save();
}

bool Agent1::apprentissage(const Interaction * eff, const Interaction * expected)
{
    addMotivation(*eff);
    return true;
}

