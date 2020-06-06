#pragma once

#include <iostream>
#include <dlfcn.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace CodingChallenge {

class CodeLoader {
public:
    CodeLoader(const char* path);
     ~CodeLoader();
    int checkSolution(int input);

private:
    bool openLibrary(const char* path);
    bool loadSymbol();

private:
    void* handle = nullptr;
    typedef int (*solution_t)(int);
    solution_t solution;
};

} // ns CodingChallenge