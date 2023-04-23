#include <iostream>
#include <vector>
#include <algorithm>

int states;
int Groups;
int symbs; //Simbolurile tranzitiilor


struct State{

    int IDstate; // id/nunarul starii
    int IDgroup; // id/numarul grupei(partiriei)
    char Status; // stare finala sau non-finala
    int* PTRState; // pointeaza la un vector care care contine IDstate-ul starilor traversate
    void set(int, std::vector<int>); // Seteaza datele starii
};

void State::set(int symb, std::vector<int> finalStates)
{
    PTRState = new int[symb];
    std::cout<<"State: q";
    std::cin>>IDstate;
    std::cout<<std::endl;
    for(int i = 0; i < states; i++)
    {
        if(std::find(finalStates.begin(), finalStates.end(), IDstate) != finalStates.end()){
            Status = 'n';
        }else {
            Status = 'y';
        }
    }

    if(Status == 'n')
        IDgroup = 0;
    else if(Status == 'y')
        IDgroup = 1;

    std::cout<<"Input the transitions: ";
    std::cout<<std::endl;

    for(int i = 0; i < symb; i++){

        std::cout<<"Input: "<< i <<" q";
        std::cin>>PTRState[i];
        std::cout<<std::endl;

    }
}

int MINIMIZATION(State s[])
{
    int Current_GROUP[states]; //Aici stochez IDgroup-ul pentru starea la care am ajuns

    for(int i = 0; i < states ; i++){ //parcurge starile
        for(int j = 0; j < symbs; j++){ //parcurge tranzitiile
            for(int k = 0; k < states; k++)//
            {
                int aux = s[k].PTRState[j];
                Current_GROUP[k] = s[aux].IDgroup;

            }

            for(int z = 0; z < states - 1; z++)
            {
                int cat_group[states];// Arrayul asta tine cont de starile care creaza partitii noi
                for(int k = 0; k < states; k++)
                { cat_group[k] = -1; }

                for(int t = z + 1; t < states; t++)
                {
                    if(s[z].IDgroup == s[t].IDgroup && Current_GROUP[z] != Current_GROUP[t])
                    {
                        int f = -1;
                        for(int l = 0; l < states; l++)//aici verificam daca s[t] poate sa apartina unei partiti existente ***
                        {
                            if(Current_GROUP[t] == cat_group[l])
                            {
                                f = l;
                                break;
                            }
                        }

                        if(f == -1) // *** caz contrat cream o partitie noua
                        {
                            s[t].IDgroup = Groups;
                            Groups++;
                            cat_group[t] = Current_GROUP[t];

                        } else{ s[t].IDgroup = s[f].IDgroup; }
                    }
                }

            }
        }
    }
}


void PrintPartitions(State s[])
{
    std::cout<<"PARTITIONS: "<<std::endl;
    for(int i = 0; i < Groups; i++)
    {
        std::cout<<"{ ";
        for(int j = 0; j < states; j++)
        {
            if(s[j].IDgroup == i)
                std::cout<<"q"<<s[j].IDstate<<" , ";
        }
       std:: cout<<"}\n";
    }
}

int main()
{
    std::cout<<"Enter number of states: ";
    std::cin>>states;
    std::cout<<"Enter number of transitions: ";
    std::cin>>symbs;
    std::cout<<"Enter number of final states: ";
    int n;
    std::cin>>n;
    std::vector<int> finalStates;
    for (int i = 0; i < n; i++) {
        int finalState;
        std::cout << "Enter the ID of final state: ";
        std::cin >> finalState;
        finalStates.push_back(finalState);
    }
    State s[states];
    for(int i = 0;i < states; i++)
    {
        s[i].set(symbs, finalStates);
    }
    Groups = 2; //Primele doua partitii
    MINIMIZATION(s);
    PrintPartitions(s);
    return 0;
}
