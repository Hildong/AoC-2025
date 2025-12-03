#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <set>
#include "../Utils/Split.h"

void findDivisitors(int n, std::set<int, std::greater<int>> &divisors) {
    for(int i = 2; i <= n; i++) {
        if(n % i == 0)  
            divisors.insert(i);
    }
}


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <inputfile.extension> \n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    long long invalidIdSum = 0;
    long long invalidIdSumNoRestrictions = 0;

    if (file.is_open())
    {
        std::string fileLine;
        std::vector<std::string> ranges;
        while (getline(file, fileLine))
        {
            getStringsSplitByDelimiter(fileLine, ranges, ',');            
        } 

        for(std::string rangeStr : ranges) {
            std::vector<std::string> rangeContainer;
            getStringsSplitByDelimiter(rangeStr, rangeContainer, '-');
            const long long firstId = std::stoll(rangeContainer.at(0));
            const long long lastId = std::stoll(rangeContainer.at(1));

            for(long long i = firstId; i <= lastId; i++) {
                const std::string strId = std::to_string(i);
                const int sequenceLength = strId.size() / 2;
                if(strId.size() % 2 != 0) continue;

                const std::string firstIdSequence = strId.substr(0, sequenceLength);
                const std::string lastIdSequence = strId.substr(sequenceLength);
                if(firstIdSequence == lastIdSequence) 
                    invalidIdSum += i;
            }
 
            for(long long i = firstId; i <= lastId; i++) {
                std::set<int, std::greater<int>> divisors;
                const std::string strId = std::to_string(i);
                findDivisitors(strId.size(), divisors);

                std::vector<std::string> idSequences;
                for(int divisor : divisors) {
                    if(divisor == strId.size()) {
                        bool allCharsAreSame = std::all_of(strId.begin(), strId.end(), [&strId](char c) {
                                return c == strId[0];
                        });
                        if(allCharsAreSame) {
                            invalidIdSumNoRestrictions += i;
                            break;
                        }
                    } else {
                        const int sequenceLength = strId.size() / divisor;
                        const std::string firstIdSequence = strId.substr(0, sequenceLength);
                        
                        int j = 1;
                        for (; j < divisor; ++j) {
                            if (strId.compare(j * sequenceLength, sequenceLength, firstIdSequence) != 0) 
                                break;
                        }

                        if (j == divisor) {
                            invalidIdSumNoRestrictions += i;
                            break;
                        }
                   }
                }
            }
        }

        file.close();
    }
    std::cout << "Total sum of all invalid ids together is: " << invalidIdSum << std::endl;
    std::cout << "Total sum of all invalid ids with no restriction together is: " << invalidIdSumNoRestrictions << std::endl;
    return 0;
}
