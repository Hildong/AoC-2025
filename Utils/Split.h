#pragma once

#include <string>
#include <vector>

void getStringsSplitByDelimiter(const std::string_view &str,
                                std::vector<std::string> &splitUpStringArr,
                                char delimiter) {
    std::string word;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '\n')
            break;

        if (str[i] == delimiter) {
            if (!word.empty()) {
                splitUpStringArr.push_back(word);
                word.clear();
            }
        } else {
            word += str[i];
        }
    }

    if (!word.empty()) {
        splitUpStringArr.push_back(word);
        word.clear();
    }
}
