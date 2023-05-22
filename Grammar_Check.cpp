#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

bool validate(const std::unordered_map<char, std::vector<std::pair<char, std::string>>>& grammar, char start_symbol, const std::string& word)
{
    std::cout << "Validating word: " << word << std::endl;

    if (word.empty())
    {
        const auto& start_rules = grammar.at(start_symbol);
        if (std::find_if(start_rules.begin(), start_rules.end(), [](const std::pair<char, std::string>& rule)
        { return rule.first == 'l' && rule.second.empty(); }) != start_rules.end())
        {
            std::cout << "Valid word" << std::endl;
            return true;
        }
    }

    for (const auto& rule : grammar.at(start_symbol))
    {
        std::cout << "Checking rule: " << rule.first << " -> " << rule.second << std::endl;

        if (std::islower(rule.first) && !word.empty() && word[0] == rule.first)
        {
            if (validate(grammar, rule.second[0], word.substr(1)))
            {
                return true;
            }
        }
        else if (std::isupper(rule.first))
        {
            if (validate(grammar, rule.first, rule.second + word))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::unordered_map<char, std::vector<std::pair<char, std::string>>> grammar = {
            {'S', {{'a', "A"}, {'d', "E"}}},
            {'A', {{'a', "B"}, {'a', "S"}}},
            {'B', {{'b', "C"}}},
            {'C', {{'b', "D"}, {'b', "B"}}},
            {'D', {{'c', "D"}, {'e', ""}, {'l', " "}}},
            {'E', {{'d', ""}}}
};


char start_symbol = 'S';
std::string word = "aabbcce";

if (!validate(grammar, start_symbol, word))
{
std::cout << "The word '" << word << "' is invalid." << std::endl;
}

return 0;
}

