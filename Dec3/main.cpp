#include <iostream>
#include <fstream>

std::string createLargestBatteryBank(const std::string& fileLine, int numOfBatteries) {
    std::string batteryBank = fileLine;
    while (batteryBank.size() > numOfBatteries) {
        bool erased = false;

        for (auto it = batteryBank.begin(); it + 1 != batteryBank.end(); ++it) {
            if (*it < *(it + 1)) {
                batteryBank.erase(it);
                erased = true;
                break;           
            }
        }

        if (!erased) 
            batteryBank.pop_back();
    }
    return batteryBank;
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
    int totalJoltageOutputSmallBank = 0;
    long long totalJoltageOutputLargeBank = 0;

    if (file.is_open())
    {
        std::string fileLine;
        while (getline(file, fileLine))
        {
            std::string smallBatteryBank = createLargestBatteryBank(fileLine, 2);
            std::string largeBatteryBank = createLargestBatteryBank(fileLine, 12);

            totalJoltageOutputSmallBank += std::stoll(smallBatteryBank);
            totalJoltageOutputLargeBank += std::stoll(largeBatteryBank);
        }

        file.close();
    }

    std::cout << "Total joltage output small bank: " << totalJoltageOutputSmallBank << std::endl;
    std::cout << "Total joltage output large bank: " << totalJoltageOutputLargeBank << std::endl;

    return 0;
}
