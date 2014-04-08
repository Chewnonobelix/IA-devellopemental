#include "interaction.h"

Interaction::Interaction(const Experience* experience, const Resultat* resultat, int motiv): m_experience(experience),
    m_resultat(resultat), m_motiv(motiv), m_prec(nullptr)
{
}

Interaction::Interaction(const Interaction & i): m_experience(i.m_experience),
    m_resultat(i.m_resultat), m_motiv(i.motivation()), m_prec(i.m_prec)
{
}

Interaction::~Interaction()
{
    if(m_prec != nullptr)
    {
        delete m_prec;
    }
}

int Interaction::motivation() const
{
    return m_motiv;
}

void Interaction::setMotivation(int val)
{
    m_motiv = val;
}

Experience Interaction::experience() const
{
    return *m_experience;
}

Resultat Interaction::resultat() const
{
    if(m_resultat == nullptr)
    {
        return Resultat();
    }
    else
    {
        return *m_resultat;
    }
}

void Interaction::affichage() const
{
//    qDebug()<<"Experience: "<<m_experience->num()<<"Resultat: "<<m_resultat->num()<<"Motivation: "<<m_motiv;
}

bool Interaction::operator <(const Interaction& i) const
{
    return motivation() < i .motivation();
}

bool Interaction::operator ==(const Interaction& i) const
{
    bool ret;
    ret = (resultat() == Resultat() && i.resultat() == Resultat()) ||
            ((!(resultat() == Resultat()) && !(i.resultat() == Resultat()) && resultat() == i.resultat()) &&
             motivation() == i.motivation());


    return (experience() == i.experience()) &&
            ret;
}

Interaction& Interaction::operator = (const Interaction& i)
{
    m_experience = i.m_experience;
    m_resultat = i.m_resultat;
    m_motiv = i.motivation();
    return *this;
}

uint qHash(const Interaction& i)
{
    return i.motivation();
}

Interaction* Interaction::prec() const
{
    return m_prec;
}

bool Interaction::hasPrec() const
{
    return m_prec != nullptr;
}

void Interaction::addPrec(Interaction * i)
{
    if(m_prec == nullptr)
    {
        m_prec = i;
    }
}
