
#include "agent3.h"
#include "systememotivationnel.h"
#include "environnement.h"

void testAgent1(Environnement* env, SystemeMotivationnel* systemeBase, QString file)
{
    Agent1 a(*env, file);
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

    qDebug()<<file<<"ok";
}

void testAgent2(Environnement* env, SystemeMotivationnel* systemeBase, QString file)
{
    Agent2 a(*env, file);
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

        while(!ep.isEmpty()&& !apprend)
        {
            Interaction* in = ep.pop();
            Resultat rt = env->result((*in).experience());
            apprend = a.apprentissage(&(systemeBase->interaction((*in).experience(), rt)), in);
            if(apprend)
            {
                ep.clear();
            }
        }
    }

    delete env;
    delete systemeBase;
    qDebug()<<file<<"ok";
}

void testAgent3(Environnement* env, SystemeMotivationnel* systemeBase, QString file)
{
    Agent3 a(*env, file);
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
    qDebug()<<file<<"ok";
}

int main(int, char**)
{
    //Nommage fichier Agent/Environnement/SystemeM
    testAgent1(new Environnement1, new SystemeMotivationnel1, "test111");
    testAgent1(new Environnement1, new SystemeMotivationnel2, "test112");
    testAgent1(new Environnement1, new SystemeMotivationnel3, "test113");
    testAgent1(new Environnement1, new SystemeMotivationnel4, "test114");
    testAgent1(new Environnement2, new SystemeMotivationnel1, "test121");
    testAgent1(new Environnement2, new SystemeMotivationnel2, "test122");
    testAgent1(new Environnement2, new SystemeMotivationnel3, "test123");
    testAgent1(new Environnement2, new SystemeMotivationnel4, "test124");

    testAgent2(new Environnement1, new SystemeMotivationnel1, "test211");
    testAgent2(new Environnement1, new SystemeMotivationnel2, "test212");
    testAgent2(new Environnement1, new SystemeMotivationnel3, "test213");
    testAgent2(new Environnement1, new SystemeMotivationnel4, "test214");
    testAgent2(new Environnement2, new SystemeMotivationnel1, "test221");
    testAgent2(new Environnement2, new SystemeMotivationnel2, "test222");
    testAgent2(new Environnement2, new SystemeMotivationnel3, "test223");
    testAgent2(new Environnement2, new SystemeMotivationnel4, "test224");
    testAgent2(new Environnement3, new SystemeMotivationnel1, "test231");
    testAgent2(new Environnement3, new SystemeMotivationnel2, "test232");
    testAgent2(new Environnement3, new SystemeMotivationnel3, "test233");
    testAgent2(new Environnement3, new SystemeMotivationnel4, "test234");

    testAgent3(new Environnement1, new SystemeMotivationnel1, "test311");
    testAgent3(new Environnement1, new SystemeMotivationnel2, "test312");
    testAgent3(new Environnement1, new SystemeMotivationnel3, "test313");
    testAgent3(new Environnement1, new SystemeMotivationnel4, "test314");
    testAgent3(new Environnement2, new SystemeMotivationnel1, "test321");
    testAgent3(new Environnement2, new SystemeMotivationnel2, "test322");
    testAgent3(new Environnement2, new SystemeMotivationnel3, "test323");
    testAgent3(new Environnement2, new SystemeMotivationnel4, "test324");
    testAgent3(new Environnement3, new SystemeMotivationnel1, "test331");
    testAgent3(new Environnement3, new SystemeMotivationnel2, "test332");
    try
    {
            testAgent3(new Environnement3, new SystemeMotivationnel3, "test333");
    }
    catch(QString execp)
    {
        qDebug()<<"fail 333"<<execp;
    }
    try
    {
        testAgent3(new Environnement3, new SystemeMotivationnel4, "test334");
    }
    catch(QString execp)
    {
        qDebug()<<"fail 334"<<execp;
    }

    testAgent3(new Environnement4, new SystemeMotivationnel1, "test341");
    testAgent3(new Environnement4, new SystemeMotivationnel2, "test342");
    testAgent3(new Environnement4, new SystemeMotivationnel3, "test343");
    testAgent3(new Environnement4, new SystemeMotivationnel4, "test344");

    return 0;
}
