#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>
///Not working yet////

std::vector<std::map<char,int>> NFA_to_DFA(std::vector<std::map<char, std::vector<int>>>& NFA){
    std::vector<std::map<char, int>> DFA;
    std::vector<char> alphabet;
    std::unordered_set<int> seen_it;
    for(int i = 0; i < NFA.size(); i++){

        for(auto & j : NFA[i]){////
            const std::vector<int> values = j.second;

            if(values.size() == 1){
                DFA[i][j.first] = values[0];
                /* nu trebuie sa combinam nimic*/

            }else{

                for (int value: values) {
                    DFA[i][j.first] += value;
                    }
                }
            }////
        }


    return DFA;
}

/// possible DFA
///{{ {'q01', 0(a)}, {'q01', 1(b)} }, --q0
///{ {'q012', 0}, {'q01', 1}}, --q01
///{ {'q012', 0}, {'q012', 1} }} --q012




int main() {
    std::vector<std::map<char, std::vector<int>>>
            AFN = {
            {{'a', {0, 1}}, {'b',{0}}},
            {{'a',{1, 2}}, {'b', {1}}},
            {{'a', {2}}, {'b', {2}}}};
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

