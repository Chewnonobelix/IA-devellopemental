#include "experience.h"


Experience::Experience(int num): m_num(num)
{
}

Experience::Experience(const Experience & e): m_num(e.num()) {}

Experience::~Experience()
{
}

int Experience::num() const
{
    return m_num;
}

void Experience::affichage() const
{
    qDebug()<<"Experience "<<num();
}

bool Experience::operator <(const Experience& e) const
{
    return num() < e.num();
}

bool Experience::operator == (const Experience& e) const
{
    return num() == e.num();
}

Experience& Experience::operator =(const Experience& e)
{
    m_num = e.num();

    return *this;
}

uint qHash(const Experience& e)
{
    return e.num();
}

