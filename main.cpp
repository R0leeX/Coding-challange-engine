#include <iostream>

#include "LevelHandler.h"
#include "Levels.h"

constexpr const char* STR_WELCOME = "Welcome in C++ CodingChallenge!\n";
constexpr const char* STR_NEXT_LEVEL_QUESTION = "Do you want the next challenge? (Y = Yes, N = Exit)\n";
constexpr const char* STR_NEXT_LEVEL = "Next challenege\n";
constexpr const char* STR_SOLVE_IT = "Solve the problem according to this sample:\n\n";
constexpr const char* STR_WRITE_THE_CODE = "Write the code in the editor, save it and then exit!\n";
constexpr const char* STR_CAN_WE_TEST = "Do you want to test your solution? (Y = Yes, N = Exit)\n";
constexpr const char* STR_BAD_SOLUTION = "Unfortunately wrong solution! Try it again!\n";
constexpr const char* STR_SOLVED = "Correct solution!\n";
constexpr const char* STR_THANKS = "You cleared every level.\n Thanks for playing\n";
constexpr const char* STR_NUMBER_OF_PASSED_LEVELS = "Number of Passed Levels: ";


using lvl1 = CodingChallenge::LevelHandler<CodingChallenge::Level1>;
using lvl2 = CodingChallenge::LevelHandler<CodingChallenge::Level2>;

std::vector<std::unique_ptr<CodingChallenge::ILevelHandler>> init_levels() {
        std::vector<std::unique_ptr<CodingChallenge::ILevelHandler>> solution;

	solution.push_back(std::move(std::unique_ptr<CodingChallenge::ILevelHandler>(new lvl1())));
        solution.push_back(std::move(std::unique_ptr<CodingChallenge::ILevelHandler>(new lvl2())));

        return solution;
}

void repeat_level(std::string& read, CodingChallenge::ILevelHandler& currentLevel, bool& solved) {
    while(!solved && read != "N") {
        std::cout << STR_WRITE_THE_CODE << std::endl;
        
        currentLevel.edit_solution();
        std::cout << STR_CAN_WE_TEST << std::endl;
        std::cin >> read;
        if(read != "N") {
            solved = currentLevel.test_solution();
            if(!solved) {
                std::cout << STR_BAD_SOLUTION << std::endl;
            } else {
                std::cout << STR_SOLVED << std::endl;
            }
            sleep(1);
        }
    }
}

int main() {
    std::vector<std::unique_ptr<CodingChallenge::ILevelHandler>> levels = init_levels(); 
    std::cout << STR_WELCOME << std::endl;

    std::string read;
    int passedLevels = 0;
    while (passedLevels < levels.size() && read != "N") {
        std::cout << STR_NEXT_LEVEL_QUESTION << std::endl;
        std::cin >> read;
	    std::cout <<STR_NUMBER_OF_PASSED_LEVELS << passedLevels << "\n";

        CodingChallenge::ILevelHandler& currentLevel = *(levels[passedLevels]);
        if(read != "N") {
            std:: cout << STR_NEXT_LEVEL << std::endl;
            std::cout << STR_SOLVE_IT << std::endl;

            currentLevel.init_default_solution();
            currentLevel.test_solution();
        }
        bool solved = false;
        repeat_level(read, currentLevel, solved);
        passedLevels++;
    }
    std::cout << STR_THANKS << std::endl;
}


