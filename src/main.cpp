#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>

#define ANSI_RESET "\033[0m"
#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"

namespace letter
{
    enum state
    {
        UNKNOWN,
        GRAY,
        YELLOW,
        GREEN
    };
}

int main(int argc, char* argv[])
{
    srand(time(0));

    std::ifstream full_file("full.txt");
    std::ifstream solutions_file("solutions.txt");
    if(full_file.fail() || solutions_file.fail())
        return 1;

    std::unordered_set<std::string> words;
    std::string word;
    while(full_file >> word)
    {
        words.insert(word);
    }
    std::vector<std::string> solutions_vec;
    while(solutions_file >> word)
    {
        if(word.size() != 5)
            continue;
        solutions_vec.push_back(word);
        words.insert(word);
    }

    std::string solution = solutions_vec[rand() % solutions_vec.size()];
    solutions_vec.clear();
    
    letter::state letters[26];
    memset(letters, letter::UNKNOWN, 26*sizeof(*letters));

    std::cout << "WORDLE! Enter a word: " << std::endl;

    int guesses = 1;
    while(guesses <= 6)
    {
        std::string guess;
        std::cin >> guess;

        if(solution == guess)
        {
            // guessed correctly
            std::cout << ANSI_GREEN << "CORRECT!" << ANSI_RESET << std::endl;
            goto quit;
        }
        else if(words.find(guess) != words.end())
        {
            // is a word, but not the solution
            char solution_temp[5];
            strncpy(solution_temp, solution.c_str(), 5);
            std::cout << ANSI_RESET << guesses << ": ";
            for(size_t i = 0; i < guess.size(); i++)
            {
                bool found_char = false;
                for(size_t j = 0; j < solution.size(); j++)
                {
                    if(guess[i] == solution_temp[j])
                    {
                        solution_temp[j] = '0';
                        if(i == j)
                        {
                            letters[guess[i] - 'a'] = letter::GREEN;
                            std::cout << ANSI_GREEN;
                        }
                        else
                        {
                            letters[guess[i] - 'a'] = letter::YELLOW;
                            std::cout << ANSI_YELLOW;
                        }
                        found_char = true;
                    }
                }
                if(!found_char)
                    letters[guess[i] - 'a'] = letter::GRAY;
                std::cout << guess[i] << ANSI_RESET;
            }
            std::cout << " ";
            for(size_t i = 0; i < 26; i++)
            {
                switch(letters[i])
                {
                    case letter::UNKNOWN:
                        break;
                    case letter::GRAY:
                        std::cout << ANSI_BLACK;
                        break;
                    case letter::YELLOW:
                        std::cout << ANSI_YELLOW;
                        break;
                    case letter::GREEN:
                        std::cout << ANSI_GREEN;
                        break;
                }
                std::cout << (char)(i + 'a') << ANSI_RESET;
            }
            std::cout << std::endl;

            guesses++;
        }
        else
        {
            // not a word
            std::cout << ANSI_RED << guess << " is not a word!" << ANSI_RESET << std::endl;
        }
    }
    std::cout << ANSI_RED << "You lose!" << ANSI_RESET << " Your word was: " << solution << std::endl;

quit:
    _getch();
    return 0;
}