#include "environnement.h"

Environnement::Environnement(int nbExp, int nbRes)
{
    for(int i = 1; i <= nbExp; i ++)
    {
        m_experience.insert(i, Experience(i));
    }

    for(int i = 1; i <= nbRes; i ++)
    {
        m_resultat.insert(i, Resultat(i));
    }
}

Resultat Environnement::result(const Experience &e)
{
    QList<QPair<int, int>>::const_iterator it;
    for (it = m_liste.begin(); it != m_liste.end(); it ++)
    {
        if((*it).first == e.num())
        {
            Resultat r = m_resultat[(*it).second];
            appliqueTransfo(m_experience[(*it).first], m_resultat[(*it).second]);
            return r;
        }
    }

    throw QString("Couple non trouver");
}

void Environnement::addPair(int e, int r)
{
    m_liste.push_back(qMakePair(e, r));
}

const Resultat& Environnement::resultat(int num) const
{
    if(m_resultat.contains(num))
    {
        return m_resultat[num];
    }

    throw "Le resultat " + QString::number(num) + "n'existe pas";
}

const Experience& Environnement::experience(int num) const
{
    if(m_experience.contains(num))
    {
        return m_experience[num];
    }

    throw "L'experience " + QString::number(num) + "n'existe pas";
}

const QMap<int, Experience>& Environnement::experience () const
{
    return m_experience;
}

void Environnement::affichage() const
{
    qDebug()<<"Affichage environnement";
//    qDebug()<<"Experience";
//    foreach (const Experience& it, m_experience)
//    {
//        it.affichage();
//    }

//    qDebug()<<"Resultat";
//    foreach (const Resultat& it, m_resultat)
//    {
//        it.affichage();
//    }

    qDebug()<<"List";
    QPair<int, int> it;
    foreach(it, m_liste)
    {
        qDebug()<<it.first<<", "<<it.second;
    }
}

void Environnement::appliqueTransfo(Experience, Resultat)
{
}

bool Environnement::removePair(int e, int r)
{
    if(m_liste.contains(qMakePair(e,r)))
    {
        m_liste.removeOne(qMakePair(e,r));
        return true;
    }

    return false;
}

Environnement1::Environnement1(): Environnement(2, 2)
{
    addPair(1, 1);
    addPair(2, 2);
}

Environnement2::Environnement2(): Environnement(2,2)
{
    addPair(1, 2);
    addPair(2, 1);
}
Environnement3::Environnement3():Environnement(2,2)
{
    addPair(1,2);
    addPair(2,1);
}

int Environnement::size() const
{
    return m_liste.size();
}

void Environnement3::appliqueTransfo(Experience e, Resultat r)
{
    if(e == Experience(1) && r == Resultat(2))
    {
        removePair(1,2);
        removePair(2,1);

        addPair(1,1);
        addPair(2,2);
    }

    if(e == Experience(2) && r == Resultat(2))
    {
        removePair(2,2);
        removePair(1,1);

        addPair(1,2);
        addPair(2,1);
    }
}

