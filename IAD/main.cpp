
#include "agent2.h"
#include "systememotivationnel.h"
#include "environnement.h"


void testAgent111()
{
    Environnement* env = new Environnement1;
    SystemeMotivationnel* systemeBase = new SystemeMotivationnel1;
    Agent1 a(*env, "test111");
    Experience ep;

    for(int i = 0; i < 100; i ++)
    {
        Resultat r = a.chooseResult();
        ep = a.chooseExperience(r);

        Resultat rt = env->result(ep);
        a.apprentissage(&(systemeBase->interaction(ep, rt)), &(systemeBase->interaction(ep, rt)));
    }

    delete env;
    delete systemeBase;
}

void testAgent121()
{
    Environnement* env = new Environnement2;
    SystemeMotivationnel* systemeBase = new SystemeMotivationnel1;
    Agent1 a(*env, "test121");
    Experience ep;

    for(int i = 0; i < 100; i ++)
    {
        Resultat r = a.chooseResult();
        ep = a.chooseExperience(r);

        Resultat rt = env->result(ep);
        a.apprentissage(&(systemeBase->interaction(ep, rt)), &(systemeBase->interaction(ep, rt)));
    }

    delete env;
    delete systemeBase;
}

void testAgent112()
{
    Environnement* env = new Environnement1;
    SystemeMotivationnel* systemeBase = new SystemeMotivationnel2;
    Agent1 a(*env, "test112");
    Experience ep;

    for(int i = 0; i < 100; i ++)
    {
        Resultat r = a.chooseResult();
        ep = a.chooseExperience(r);

        Resultat rt = env->result(ep);
        a.apprentissage(&(systemeBase->interaction(ep, rt)), &(systemeBase->interaction(ep, rt)));
    }

    delete env;
    delete systemeBase;
}

void testAgent234()
{
    Environnement* env = new Environnement3;
    SystemeMotivationnel* systemeBase = new SystemeMotivationnel4;
    Agent2 a(*env, "test234");
    QStack<Interaction*> ep;

    ep.clear();
    for(int i = 0; i < 100; i ++)
    {
        if(ep.isEmpty())
        {
            Resultat r = a.chooseResult();
            ep = a.chooseExperience(r);
        }
        bool apprend = false;
        Interaction* in = ep.pop();
        Resultat rt = env->result((*in).experience());
        apprend = a.apprentissage(&(systemeBase->interaction((*in).experience(), rt)), in);

        if(apprend)
        {
            ep.clear();
        }
    }

    delete env;
    delete systemeBase;
}

int main(int, char**)
{
    testAgent111();
    testAgent121();
    testAgent112();
    testAgent234();
    return 0;
}
