#include "systememotivationnel.h"

SystemeMotivationnel::SystemeMotivationnel()
{
}

Interaction SystemeMotivationnel::interaction(const Experience& e, const Resultat& r) const
{
    if(r == Resultat())
    {
        return Interaction(new Experience(e), new Resultat);
    }
    return m_systeme[qMakePair(e,r)];
}

void SystemeMotivationnel::add(Experience e, Resultat r, int m)
{
    m_systeme[qMakePair(e,r)] = Interaction(new Experience(e),new Resultat(r),m);
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
    Interaction ret = m_systeme.first();
    QList<Experience> rt;
    foreach (const Interaction& it, m_systeme)
    {
        if(r == it.resultat() && ret.motivation() < it.motivation())
        {
            ret = it;
        }
    }

    return ret.experience();
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
