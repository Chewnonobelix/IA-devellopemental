#include "agent.h"

Agent::Agent(const Environnement& e, int nbExp): m_environnement(e), m_motivationScore(0)
{
    for(int i = 1; i <= nbExp; i++ )
    {
        m_exp[i] = Experience(i);;
    }

    QFile file("trace.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Ouverture du fichier \"trace.txt\" impossible";
        return;
    }
    file.close();
}

Agent::~Agent()
{
}

void Agent::save()
{
    QFile file("trace.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug()<<"Ouverture du fichier \"trace.txt\" impossible";
        return;
    }

    const Interaction& it = m_trace.last();

    QString toWrite;
    toWrite = "Experience: " + QString::number(it.experience().num()) + ", ";
    toWrite += "Resultat: " + QString::number(it.resultat().num()) + ", ";
    toWrite += "Motivation: " + QString::number(it.motivation()) + ", Total = " + QString::number(m_motivationScore) + "\n";

    file.write(toWrite.toLatin1());


    file.close();
}

Resultat Agent::chooseResult() const
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

QStack<Interaction> Agent::chooseExperience(const Resultat& r) const
{
    QStack<Interaction> ret;
    Experience exp;
    if(r.num() == 0)
    {
        exp = m_exp.first();
        ret.push(Interaction(new Experience(exp)));
    }
    else
    {
        bool find = true;

        foreach (const Experience& e, m_exp)
        {
            find &= m_motivation.contain(e);
            if(!m_motivation.contain(e))
            {
                ret.clear();
                ret.push(Interaction(new Experience(e), new Resultat));
            }
        }

        if(find)
        {
            QList<Experience> exclue;
            exp = m_motivation.exp(r);


            Interaction i = m_motivation.interaction(exp, r);

            while(i.hasPrec())
            {
                ret.push(i);
                i = *(i.prec());
            }

            ret.push(i);
        }
    }

    return ret;
}

void Agent::addMotivation(const Interaction& i)
{
    m_motivation.add(i.experience(), i.resultat(), i.motivation());
    m_motivationScore += m_motivation.interaction(i.experience(), i.resultat()).motivation();
    m_trace<<m_motivation.interaction(i.experience(), i.resultat());
    save();
}

bool Agent::apprentissage(const Interaction & eff, const Interaction & expected)
{
    bool ret = false;
    if(!(eff == expected) || (expected.resultat() == Resultat()))
    {
        qDebug()<<"Apprend";
        int lastIndex = m_trace.lastIndexOf(expected);
        int nb = 0;
        Interaction prec = expected;
        while(prec.hasPrec())
        {
            nb++;
            prec = *(prec.prec());
        }
        if(lastIndex - nb - 1 >= 0)
        {
            prec.addPrec(new Interaction(m_trace[lastIndex - nb - 1]));
        }
    }
    m_last = qMakePair(eff, expected);
    addMotivation(eff);

    return ret;
}
