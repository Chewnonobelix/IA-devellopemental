#include "interaction.h"

Interaction::Interaction(const Experience experience, const Resultat resultat, int motiv): m_experience(experience),
    m_resultat(resultat), m_motiv(motiv), m_poid(0)
{
}

Interaction::Interaction(const Interaction & i): m_experience(i.experience()),
    m_resultat(i.resultat()), m_motiv(i.motivation()), m_poid(i.poid()), m_prec(i.m_prec)
{
}

Interaction::~Interaction()
{
}

double Interaction::procl() const
{
    return motivation() * poid();
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
    return m_experience;
}

Resultat Interaction::resultat() const
{
    return m_resultat;
}

void Interaction::affichage() const
{
    qDebug()<<"Experience: "<<m_experience.num()<<"Resultat: "<<m_resultat.num()<<"Motivation: "<<m_motiv;
}

bool Interaction::operator <(const Interaction& i) const
{
    return motivation() < i.motivation();
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

    m_prec.clear();
    m_prec = i.m_prec;

    return *this;
}

uint qHash(const Interaction& i)
{
    return i.motivation();
}

const QList<Interaction*>& Interaction::prec() const
{
    return m_prec;
}

QList<Interaction*>& Interaction::prec()
{
    return m_prec;
}

bool Interaction::hasPrec() const
{
    return !(m_prec.isEmpty());
}

void Interaction::addPrec(Interaction *i)
{
    m_prec.push_front(i);
}

bool Interaction::operator !=(const Interaction& i) const
{
    return !((*this) == i);
}

QString Interaction::toString() const
{
    return "I"+QString::number(experience().num())+QString::number(resultat().num());
}
QTextStream& operator<< (QTextStream& stream, const Interaction& i)
{
    stream<<i.toString();
    return stream;
}

QDebug& operator<< (QDebug& d, const Interaction& i)
{
    d<<i.toString();
    return d;
}

int Interaction::poid() const
{
    return m_poid;
}

void Interaction::setPoid(int p)
{
    m_poid = p;
}
