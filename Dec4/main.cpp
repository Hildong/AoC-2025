#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using Layout = std::vector<std::vector<char>>;

namespace {
const char paperRoll = '@';
}

struct Pos {
    Pos(int y, int x) : y_(y), x_(x) {};
    int x_;
    int y_;
};

bool adjacentPositionsValid(const Layout &layout,
                            Pos &position,
                            const int threshold,
                            const int maxNumOfAdjacentPaperRolls) {
    int adjacentBlockades = 0;
    int startPos = std::floor(sqrt(threshold + 1) / 2);

    for (int y = startPos; y >= std::negate<int>()(startPos); y--) {
        int currentY = y + position.y_;
        if (currentY < 0 || currentY >= layout.size() - 1)
            continue;

        for (int x = startPos; x >= std::negate<int>()(startPos); x--) {
            int currentX = x + position.x_;
            bool xInbounds = currentX >= 0 && currentX <= layout[currentY].size() - 1;
            bool isOwnPosition = currentX == position.x_ && currentY == position.y_;

            if (!xInbounds || isOwnPosition)
                continue;

            if (layout[currentY][currentX] == paperRoll)
                adjacentBlockades++;
        }
    }

    return adjacentBlockades < maxNumOfAdjacentPaperRolls;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile.extension> \n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    Layout layout = {{}};
    std::vector<Pos> positionsToCheck = {};
    int totalToiletRollsMoved = 0;
    int totalToiletRollsMovedMultipleTurns = 0;

    if (file.is_open()) {
        char ch;
        int y = 0;
        int x = 0;
        while (file.get(ch)) {
            if (ch == '\n') {
                y++;
                x = 0;
                layout.push_back({});
                continue;
            }

            layout[y].push_back(ch);
            if (ch == paperRoll) {
                positionsToCheck.push_back({y, x});
            }
            x++;
        }

        file.close();
    }

    for (auto &pos : positionsToCheck) {
        Layout layoutCopy = layout;
        if (adjacentPositionsValid(layoutCopy, pos, 8, 4))
            totalToiletRollsMoved++;
    }

    int toiletRollsMovedThisTurn = 0;
    while (true) {
        Layout updatedLayoutAfterRemoving = layout;
        for (auto it = positionsToCheck.begin(); it != positionsToCheck.end();) {
            Pos &pos = *it;

            if (adjacentPositionsValid(layout, pos, 8, 4)) {
                totalToiletRollsMovedMultipleTurns++;
                updatedLayoutAfterRemoving[pos.y_][pos.x_] = '.';
                it = positionsToCheck.erase(it);
            } else {
                it++;
            }
        }
        if (layout == updatedLayoutAfterRemoving || !positionsToCheck.size())
            break;

        layout = updatedLayoutAfterRemoving;
        toiletRollsMovedThisTurn += totalToiletRollsMovedMultipleTurns;
    }

    std::cout << "Rolls accessed by the forklift: " << totalToiletRollsMoved << std::endl;
    std::cout << "Rolls accessed by the forklift after multiple turns: " << totalToiletRollsMovedMultipleTurns
              << std::endl;
    return 0;
}
