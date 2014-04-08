
#include "agent.h"
#include "systememotivationnel.h"
#include "environnement.h"

int main(int, char**)
{
    Environnement* env = new Environnement3;
    SystemeMotivationnel* systemeBase = new SystemeMotivationnel4;
    Agent a(*env);
    QStack<Interaction> ep;

    ep.clear();
    for(int i = 0; i < 100; i ++)
    {
        if(ep.isEmpty())
        {
            Resultat r = a.chooseResult();
            ep = a.chooseExperience(r);
        }
        bool apprend = false;

        Interaction in = ep.pop();
        Resultat rt = env->result(in.experience());
        apprend = a.apprentissage(systemeBase->interaction(in.experience(), rt), in);

        if(apprend)
        {
            ep.clear();
        }
    }

    delete env;
    delete systemeBase;
    return 0;
}
