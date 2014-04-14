#include "systememotivationnel.h"

SystemeMotivationnel::SystemeMotivationnel()
{
}

Interaction SystemeMotivationnel::interaction(const Experience& e, const Resultat& r) const
{
    if(r == Resultat())
    {
        return Interaction(Experience(e));
    }
    return m_systeme[qMakePair(e,r)];
}

Interaction& SystemeMotivationnel::interaction(const Experience& e, const Resultat& r)
{
    return m_systeme[qMakePair(e,r)];
}

Interaction& SystemeMotivationnel::interaction(const Interaction & i)
{
    return m_systeme[qMakePair(i.experience(), i.resultat())];
}

void SystemeMotivationnel::add(Experience e, Resultat r, int m)
{
    m_systeme[qMakePair(e,r)] = Interaction(Experience(e), Resultat(r),m);
}

void SystemeMotivationnel::affichage() const
{
    qDebug()<<"Systeme Motivationel";
    foreach(const Interaction& it, m_systeme)
    {
        it.affichage();
    }
}


QMap<QPair<const Experience, const Resultat>, Interaction> SystemeMotivationnel::systeme() const
{
    return m_systeme;
}

Interaction SystemeMotivationnel::first() const
{
    return m_systeme.first();
}

bool SystemeMotivationnel::contain(const Interaction& i) const
{
    return m_systeme.contains(qMakePair(i.experience(), i.resultat()));
}

bool SystemeMotivationnel::contain(const Experience & e) const
{
    bool ret = false;

    foreach (const Interaction& i, m_systeme)
    {
        ret |= (i.experience() == e);
    }

    return ret;
}

QList<Experience> SystemeMotivationnel::exp(const Resultat & r) const
{
    QList<Experience> rt;
    QList<Interaction> temp;
    foreach (const Interaction& it, m_systeme)
    {
        if(r == it.resultat())
        {
            temp<<it;
        }
    }

    for(int i = 0; i < temp.size(); i ++)
    {
        for(int j = i; j < temp.size(); j ++)
        {
            if(temp[i] < temp[j])
            {
                temp.swap(i,j);
            }
        }
    }

    foreach (const Interaction& it, temp)
    {
        rt<<it.experience();
    }

    return rt;
}

SystemeMotivationnel1::SystemeMotivationnel1()
{
    add(Experience(1), Resultat(1), 1);
    add(Experience(1), Resultat(2), 1);
    add(Experience(2), Resultat(1), -1);
    add(Experience(2), Resultat(2), -1);
}

SystemeMotivationnel2::SystemeMotivationnel2()
{
    add(Experience(1), Resultat(1), -1);
    add(Experience(1), Resultat(2), -1);
    add(Experience(2), Resultat(1), 1);
    add(Experience(2), Resultat(2), 1);
}

SystemeMotivationnel3::SystemeMotivationnel3()
{
    add(Experience(1), Resultat(2), -1);
    add(Experience(1), Resultat(1), 1);
    add(Experience(2), Resultat(1), 1);
    add(Experience(2), Resultat(2), -1);
}

SystemeMotivationnel4::SystemeMotivationnel4()
{
    add(Experience(1), Resultat(2), 1);
    add(Experience(1), Resultat(1), -1);
    add(Experience(2), Resultat(1), -1);
    add(Experience(2), Resultat(2), 1);
}
