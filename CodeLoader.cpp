
#include "CodeLoader.h"

namespace CodingChallenge {

CodeLoader::CodeLoader(const char* path) {
    CodeLoader::openLibrary(path);
    CodeLoader::loadSymbol();
}

bool CodeLoader::openLibrary(const char* path) {
    handle = dlopen(path, RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
            return false;
        }
        //reset errors
        dlerror();
        return true;
}

bool CodeLoader::loadSymbol() {
        solution = (solution_t) dlsym(handle, "LevelHandler");
        const char *dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol:" << dlsym_error <<'\n';
            dlclose(handle);
            return false;
        }
        return true;
}

int CodeLoader::checkSolution(int input) {
    return solution(input);
}

CodeLoader::~CodeLoader() {
      dlclose(handle);
}

} // ns CodingChallenge