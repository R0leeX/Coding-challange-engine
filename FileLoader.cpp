
#include "FileLoader.h"


namespace CodingChallenge {

FileLoader::FileLoader() {
}

std::vector<std::string> FileLoader::findFiles(const std::string& inputDirectory, const boost::regex& filter) const {
    std::vector<std::string> files_found;

    boost::filesystem::directory_iterator end_itr;
    for (boost::filesystem::directory_iterator itr(inputDirectory); itr != end_itr; ++itr) {
        if (!boost::filesystem::is_regular_file(itr->status())) {
            continue;
        }

        boost::smatch match;

        if (!boost::regex_match(itr->path().native(), match, filter)) {
            continue;
        }
        std::string absolutePath = itr->path().native();
        files_found.push_back(absolutePath);
    }
    return files_found;
}

int FileLoader::loadSolution(std::vector<std::string>& files, int input) const {
       const std::string userInputDirectory =  "./";
       int ret = 0;
       for (auto s : files) {
            CodeLoader codeLoader(s.c_str());
            ret = codeLoader.checkSolution(input);
        }
        return ret;
}

}
