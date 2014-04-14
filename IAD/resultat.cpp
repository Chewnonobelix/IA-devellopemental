#include "resultat.h"

Resultat::Resultat(int num): m_num(num)
{
}

Resultat::Resultat(const Resultat & r): m_num(r.num()) {}

Resultat::~Resultat()
{
}

int Resultat::num() const
{
    return m_num;
}

void Resultat::affichage() const
{
    qDebug()<<"Resultat "<<num();
}

bool Resultat::operator <(const Resultat& r) const
{
    return num() < r.num();
}

bool Resultat::operator == (const Resultat& r) const
{
    return num() == r.num();
}

bool Resultat::operator != (const Resultat& r) const
{
    return num() != r.num();
}

Resultat& Resultat::operator =(const Resultat& r)
{
    m_num = r.num();

    return *this;
}

uint qHash(const Resultat& r)
{
    return r.num();
}
