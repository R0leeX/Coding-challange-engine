#pragma once

#include <iostream>
#include <iomanip>

#include "constants.h"
#include "FileLoader.h"
#include "Levels.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace CodingChallenge {

class ILevelHandler {
public:
    virtual ~ILevelHandler() {}

    virtual void edit_solution() = 0;
    virtual void make_shared_object(const std::string file) = 0;
    virtual bool test_solution() = 0;
    virtual void init_default_solution() = 0;
};

template<class TLevel>
class LevelHandler final : public ILevelHandler {
    public:
    LevelHandler() = default;
    
    void edit_solution() {
        std::string cmd = "xterm -geometry 93x31+600+500 -e 'nano " + base + "solution.cpp '";
        system(cmd.c_str());
    }

    void make_shared_object(const std::string file) {
            const std::string compile_command = "gcc -std=c++11 -fPIC "+ file + " -c -o " + base + solution_object;
            const std::string make_share_object_command = "gcc -shared " + base + solution_object + " -o " + base + solution_shared_object;
            system(compile_command.c_str());
            system(make_share_object_command.c_str());
        }

    bool test_solution() {
            bool solved = true;
            const FileLoader fileLoader;
            std::vector<std::string> files;
            
            files = fileLoader.findFiles(base,  boost::regex(".*solution.*.cpp"));
            for(auto file: files)
                make_shared_object(file);
            
            print_expected_result();
            check_inputs(solved, fileLoader);

            return solved;
        }

    void init_default_solution() {
        std::string clear_solution_command = "cp default_solution.source solution.cpp";
        system(clear_solution_command.c_str());   
    }

    private:
        void print_expected_result() {
            std::cout << std::setfill(' ');
            std::cout << std::left;
            std::cout << std::string(10, ' ') << "Input";
            std::cout << std::string(10, ' ') << "Expected Output";
            std::cout << std::string(5, ' ') << "Your Output" << std::endl;
        }

        void check_inputs(bool& solved, const FileLoader& fileLoader) {
            std::vector<std::string> solutions;
            solutions = fileLoader.findFiles(base,  boost::regex(".*solution.*.so"));
            
            TLevel current_Level;
            std::vector<int> test_inputs = current_Level.get_inputs();
            for (auto input : test_inputs) {
                int expected = current_Level.test(input);
                int result = fileLoader.loadSolution(solutions, input);

                check_result(solved, input, expected, result);

            }
        }

        void check_result(bool& solved, int input, int expected, int result) {
            bool match = expected == result;
            std::cout << match << std::string(9, ' ');
            std::ostringstream ss;
            ss << input;
            std::cout << std::setw(15) << ss.str();

            std::cout << std::setw(20) << expected;
            std::cout << result << std::endl;
            
            if (!match) {
                solved = false;
            }
        }
};

} // ns CodingChallenge