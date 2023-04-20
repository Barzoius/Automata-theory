#include <iostream>

struct State{

    int IDstate;
    int IDgroup;
    char Status;
    int* PTRState;
    void set(int);
};

void State::set(int symbs) // inputs states represents the number of states
{
    PTRState = new int[symbs];
    std::cout<<"State: q";
    std::cin>>IDstate;
    std::cout<<std::endl;
    std::cout<<"Final/NonFinal state(f/n): ";
    std::cin>>Status;
    std::cout<<std::endl;

    if(Status == 'n')
        IDgroup = 0;
    else if(Status == 'f')
        IDgroup = 1;

    std::cout<<"Input the transitions: ";
    std::cout<<std::endl;

    for(int i = 0; i < symbs; i++){

        std::cout<<"Input: "<< i <<" q";
        std::cin>>PTRState[i];
        std::cout<<std::endl;

    }
}

int states;
int Groups;
int symbs;

int MINIMIZATION(State s[])
{
    int Current_GROUP[states];

    for(int i = 0; i < states; i++){
        for(int j = 0; j < symbs; j++){
            for(int k = 0; k < states; k++)
            {
                int aux = s[k].PTRState[j];
                Current_GROUP[k] = s[aux].IDgroup;

            }

            for(int z = 0; z < states - 1; z++)
            {
                int cat_group[states];
                for(int k = 0; k < states; k++)
                { cat_group[k] = -1; }

                for(int t = z + 1; t < states; t++)
                {
                    if(s[z].IDgroup == s[t].IDgroup && Current_GROUP[z] != Current_GROUP[t])
                    {
                        int f = -1;
                        for(int l = 0; l < states; l++)
                        {
                            if(Current_GROUP[t] == cat_group[l])
                            {
                                f = l;
                                break;
                            }
                        }

                        if(f == -1)
                        {
                            s[t].IDgroup = Groups;
                            Groups++;
                            cat_group[t] = Current_GROUP[t];

                        } else{ s[t].IDgroup = s[f].IDgroup; }
                    }
                }

            }
        }

        int equiv = i;
        for(int g = 0; g < states; g++)
        {
            if(s[g].IDgroup != Current_GROUP[i])
            {
                equiv = -1;
                break;
            }
        }

        if(equiv != -1) { return equiv; }
    }
}

void run(State s[])
{

    for(int i = 0; i < states - 1; i++){
        if(s[i].IDstate != -1){
            for(int j = i + 1; j < states; j++){
                if(s[i].IDgroup == s[j].IDgroup){
                    for(int k = 0; k < states; k++){
                        for(int z = 0; z < states; z++){
                            if(s[k].PTRState[z] == s[j].IDstate)
                            { s[k].PTRState[z] = i; }
                        }
                    }

                    s[j].IDstate = -1;

                    if(s[j].Status == 'f')
                    { s[i].Status = 'f';}
                }
            }
        }

    }
}
void PrintPartitions(State s[])
{
    std::cout<<"PARTITIONS: "<<std::endl;
    for(int i=0;i<Groups;i++)
    {
        std::cout<<"{ ";
        for(int j=0;j<states;j++)
        {
            if(s[j].IDgroup==i)
                std::cout<<"q"<<s[j].IDstate<<" , ";
        }
       std:: cout<<"}\n";
    }
}

int main()
{
    std::cout<<"Enter number of states: ";
    std::cin>>states;
    std::cout<<"Enter number of input symbols: ";
    std::cin>>symbs;
    State s[states];
    for(int i=0;i<states;i++)
    {
        s[i].set(symbs);
    }
    Groups=2; 
    MINIMIZATION(s);
    PrintPartitions(s);
    run(s);

    return 0;
}
