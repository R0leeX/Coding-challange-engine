#pragma once

#include <iostream>
#include "CodeLoader.h"


namespace CodingChallenge {

class FileLoader {
public:
    FileLoader();
    int loadSolution(std::vector<std::string>& files, int input) const;
    std::vector<std::string> findFiles(const std::string& inputDirectory, const boost::regex& filter) const;
};

} // ns CodingChallenge