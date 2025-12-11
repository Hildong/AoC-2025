#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include "../Utils/Split.h" 

struct ProductRange {
    ProductRange(std::string &min, std::string &max) : min_(min), max_(max) {};

    std::string min_;
    std::string max_;
};

void mergeRanges(std::vector<ProductRange>& productRanges) {
    if (productRanges.empty())
        return;

    std::sort(productRanges.begin(), productRanges.end(), [](const ProductRange& a, const ProductRange& b) {
        return std::stoll(a.min_) < std::stoll(b.min_);
    });

    for (auto it = productRanges.begin(); it != productRanges.end(); ) {
        auto next = std::next(it);

        if (next != productRanges.end()) {
            const long long itMax = std::stoll(it->max_);
            const long long nextMin = std::stoll(next->min_);
            const long long nextMax = std::stoll(next->max_);

            if (itMax >= nextMin) {
                it->max_ = std::to_string(std::max(itMax, nextMax));
                productRanges.erase(next);  
            } else {
                ++it;  
            }
        } else {
            ++it;  
        }
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
    std::vector<ProductRange> validProductRanges{};
    int numOfFreshProducts = 0;
    long long rangesCombined = 0;

    if (file.is_open())
    {
        std::string fileLine;
        bool readRangeMode = true;
        while (getline(file, fileLine))
        {
            if(readRangeMode) {
                if(fileLine.empty()) {
                    mergeRanges(validProductRanges);
                    readRangeMode = false;
                    continue;
                }

                std::vector<std::string> ranges{};
                getStringsSplitByDelimiter(fileLine, ranges, '-');
                
                validProductRanges.push_back(ProductRange(ranges.at(0), ranges.at(1)));
                continue;
            }

            for(const auto &range : validProductRanges) {
                if(std::stoll(fileLine) >= std::stoll(range.min_) && std::stoll(fileLine) <= std::stoll(range.max_)) {
                    numOfFreshProducts++;
                    break;
                }
            }
        } 

        for(const auto &range : validProductRanges) {
             rangesCombined += std::stoll(range.max_) - std::stoll(range.min_) + 1; 
        }

        file.close();
    }

    std::cout << "Number of fresh products: " << numOfFreshProducts << "\n";
    std::cout << "rangesCombined: " << rangesCombined << "\n";
    return 0;
}
