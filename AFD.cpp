#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class AFD {
private:
    int num_states;
    vector<char> alphabet;
    vector<map<char, int>> transition_table;
    int start_state;
    vector<int> accept_states;
public:
    AFD(int n, vector<char> a, vector<map<char, int>> tt, int s, vector<int> ac) :
            num_states(n), alphabet(a), transition_table(tt), start_state(s), accept_states(ac) {}
    vector<int> run(string input) 
    {
        int current_state = start_state;
        vector<int> states = {current_state};
        for (char c : input) 
        {
            if (find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) 
            {
                // Daca starea incearca sa tranzitioneze la o stare care nu exisita in alfabet
                return {};
            }
            if (transition_table[current_state].count(c) == 0) 
            {
                // Daca nu exista tranzitie pentru starea curenata
                return {};
            }
            current_state = transition_table[current_state][c];
            states.push_back(current_state);
        }
        if (find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end()) 
        {
            // Daca starea finala este o stare acceptata se returneaza un vector cu stari
            return states;
        } else {
            //In caz contrar se va afisa un veactor gol
            return {};
        }
    }
};

int main(){

    int num_states = 4; // numarul starilor
    vector<char> alphabet = {'0', '1', '2'}; //alfabetul
    //Aici se introduc tranzitiile. Tabelul de tranzitii de mai jos e cel de la exemplul 2:
    vector<map<char,int>> transition_table = {{ {'0', 1}, {'1', 0} },
                                              { {'0', 2}, {'1', 0}},
                                              { {'2', 3} },
                                              {  }};
    int start_state = 0;
    vector<int> accept_states = {1, 3};
    AFD my_afd(num_states, alphabet, transition_table, start_state, accept_states);
    string input = "110101002";
    vector<int> states = my_afd.run(input);
    if (states.empty()) {
        cout << "Cuvantul nu e valid" << endl;
    } else {
        cout << "Cuvantul este valid" << endl;
        cout << "Drumul este: ";
        for (int state : states) {
            cout << state << " ";
        }
        cout << endl;
    }
    return 0;
}
