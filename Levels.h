#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace CodingChallenge {
    
    class ILevel {
    public:
        virtual ~ILevel() {}
        
        virtual std::vector<int> get_inputs() = 0;
        virtual int test(int input) = 0;
    };

    class Level1 : public ILevel {
    public:

        std::vector<int> get_inputs() {
            return {1, 2, 3, 4, 5};
        };

        int test(int input) {
            return input * 10;
        };

    };
    
    class Level2 : public ILevel {
    public:

        std::vector<int> get_inputs() {
            return {5, 4, 3, 2, 1};
        };

        int test(int input) {
            return input + 10;
        };

    };

} // ns CodingChallenge