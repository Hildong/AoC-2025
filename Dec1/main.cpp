#include <iostream>
#include <fstream>
#include <functional>

namespace {
    constexpr int MOD = 100;
}

class Dial {
public: 
    Dial(int value) : value_(value) {};

    operator int() const { return value_; }

    friend int operator+(Dial lhs, int rhs) {
         lhs.value_ = (lhs.value_ + rhs) % MOD;
         if(lhs.value_ < 0)
             lhs.value_ += MOD;
         return lhs.value_;
    }

    Dial& operator=(int rhs) {
        value_ = rhs % MOD;
        if (value_ < 0)
            value_ += MOD;
        return *this;
    }

    bool operator==(int rhs) {
        return value_ == rhs;
    }

    bool operator>(int rhs) {
        return value_ > rhs;
    }

    bool operator<(int rhs) {
        return value_ < rhs;
    }

private: 
    int value_;
};

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <inputfile.extension> \n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    int numOfTimesHitZero = 0;
    int numOfTimesPassedZero = 0;
    Dial dial(50); 

    if (file.is_open())
    {
        std::string fileLine;
        while (getline(file, fileLine))
        {
            bool leftTurn = fileLine[0] == 'L';
            int turnRate = std::stoi(fileLine.substr(1));
            numOfTimesPassedZero += turnRate / MOD;

            if(leftTurn) 
                turnRate = std::negate<int>()(turnRate);
            
            int prevDialNum = dial;
            dial = dial + turnRate;
            bool passedZero = (leftTurn && prevDialNum < dial) || (!leftTurn && prevDialNum > dial);

            if(dial == 0) { 
                numOfTimesHitZero++;
                numOfTimesPassedZero++;
            } else if (passedZero && prevDialNum != 0) {
                numOfTimesPassedZero++;
            }
        } 
        file.close();
    }

    std::cout << "Number of times that 0 was hit: " << numOfTimesHitZero << "\n";
    std::cout << "Number of times that 0 was passed: " << numOfTimesPassedZero << std::endl;

    return 0;
}
