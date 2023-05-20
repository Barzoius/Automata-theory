#include <iostream>
#include <unordered_map>
#include <vector>

bool valideaza(const std::unordered_map<char, std::vector<std::pair<char, std::string>>>& gramatica, char start_symbol, const std::string& ward) {
    if (ward.empty() && gramatica.at(start_symbol).size() > 0 && gramatica.at(start_symbol)[0].second == "l") {
        std::cout << "Cuvant Valid" << std::endl;
        return true;
    }

    for (const auto& regula : gramatica.at(start_symbol)) {
        if (islower(regula.first) && !ward.empty() && ward[0] == regula.first) {
            if (valideaza(gramatica, regula.second[0], ward.substr(1))) {
                return true;
            }
        }
        else if (isupper(regula.first)) {
            if (valideaza(gramatica, regula.first, regula.second + ward)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    std::unordered_map<char, std::vector<std::pair<char, std::string>>> gramatica = {
            {'S', {{'a', "A"}, {'d', "E"}}},
            {'A', {{'a', "B"}, {'a', "S"}}},
            {'B', {{'b', "C"}}},
            {'C', {{'b', "D"}, {'b', "B"}}},
            {'D', {{'c', "D"}, {'l', ""}}},
            {'E', {{'l', ""}}}
    };

    char start_symbol = 'S';
    std::string ward = "aabbdcc";

    if (!valideaza(gramatica, start_symbol, ward)) {
        std::cout << "Cuvantul " << ward << " este invalid" << std::endl;
    }

    return 0;
}
