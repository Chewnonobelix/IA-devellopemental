#include "agent2.h"

Agent2::Agent2(const Environnement& e, QString fileName, int nbExp): Agent1(e, fileName, nbExp)
{
}

Agent2::~Agent2()
{
    QFile file(m_fileName + "_pattern.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Ouverture du fichier \"pattern.txt\" impossible";
        return;
    }

    QTextStream stream(&file);

    foreach (const Interaction& it, m_motivation.systeme())
    {
        if(it.hasPrec())
        {
            for(int i = 0; i < it.prec().size(); i ++)
            {
                stream<<it.prec()[i]->toString()<<" => ";
            }
        }

        stream<<it<<'\n';
    }
    file.close();
}


Resultat Agent2::chooseResult() const
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

QStack<Interaction *> Agent2::chooseExperience(const Resultat& r)
{
    QStack<Interaction*> ret;
    QList<Experience> exps;
    if(r.num() == 0)
    {
        ret.push(new Interaction(Experience(m_exp.first())));
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
                ret.push(new Interaction(Experience(e)));
            }
        }

        if(find)
        {
            exps = m_motivation.exp(r);
            Interaction& i = m_motivation.interaction(exps[0], r);

            for(int j = i.prec().size() - 1; j >= 0; j --)
            {
                ret.push(i.prec()[j]);
            }
            ret.push(&i);
        }
    }

    return ret;
}

void Agent2::addMotivation(Interaction *i)
{
    if(!m_motivation.contain(*i))
    {
        m_motivation.add(i->experience(), i->resultat(), i->motivation());
    }
    m_trace<<&(m_motivation.interaction(*i));

    m_motivationScore += m_motivation.interaction(i->experience(), i->resultat()).motivation();
    save();
}

bool Agent2::apprentissage(const Interaction *eff, const Interaction *expected)
{
    bool ret = false;

    if((*eff != *expected) && ((*expected).resultat() != Resultat()))
    {
        int lastIndex = m_trace.lastIndexOf(const_cast<Interaction*>(expected));
        Interaction& base = m_motivation.interaction(*expected);

        if(lastIndex != -1 && lastIndex - base.prec().size() - 1 >= 0 && !base.prec().contains(m_trace[lastIndex - base.prec().size() - 1]) && m_trace[lastIndex - base.prec().size() - 1] != expected)
        {
            base.addPrec(m_trace[lastIndex - base.prec().size() - 1]);
            ret = true;
        }
    }

    addMotivation(const_cast<Interaction*>(eff));
    m_last = qMakePair(*eff, *expected);

    return ret;
}
