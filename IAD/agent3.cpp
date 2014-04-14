#include "agent3.h"

Agent3::Agent3(const Environnement& e, QString f, int nb): Agent2(e,f, nb)
{}

Agent3::~Agent3()
{}

QStack<Interaction*> Agent3::chooseExperience(const Resultat& r)
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

            QList<Interaction*> temp;

            foreach(const Experience& e, exps)
            {
                temp<<&(m_motivation.interaction(e,r));
            }

            for(int i = 0; i < temp.size(); i ++)
            {
                for(int j = i; j < temp.size(); j++)
                {
                    if(temp[i]->procl() < temp[j]->procl())
                    {
                        temp.swap(i,j);
                    }
                }
            }

            Interaction* i = temp[0];
            int j = 1;
            if(i->procl() < 0)
            {
                QMap<QPair<const Experience, const Resultat>, Interaction>& temp = m_motivation.systeme();
                QList<Interaction> toRemove;
                QList<Experience> temp2 = m_exp.values();
                temp2.removeOne(i->experience());

                foreach (const Experience& e, temp2)
                {
                    toRemove += m_motivation.interaction(e);
                }

                foreach (const Interaction& it, toRemove)
                {
                    temp.remove(qMakePair(it.experience(), it.resultat()));
                }
            }

            for(int j = i->prec().size() - 1; j >= 0; j --)
            {
                ret.push(i->prec()[j]);
            }
            ret.push(i);
        }
    }

    return ret;
}

void Agent3::addMotivation(Interaction* i)
{
    if(!m_motivation.contain(*i))
    {
        m_motivation.add(i->experience(), i->resultat(), i->motivation());
    }
    else
    {
        Interaction& temp = m_motivation.interaction(*i);
        temp.setPoid(temp.poid() + 1);
    }

    m_trace<<&(m_motivation.interaction(*i));

    m_motivationScore += m_motivation.interaction(i->experience(), i->resultat()).motivation();
    save();
}

bool Agent3::apprentissage(const Interaction* eff, const Interaction* exp)
{
    bool ret = Agent2::apprentissage(eff, exp);

    if(ret)
    {
        Interaction& i = m_motivation.interaction(*exp);
        i.setPoid(i.poid() - 1);
    }

    return ret;
}
