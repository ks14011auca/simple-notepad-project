#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

inline void sort_word_frequencies(std::vector<std::pair<std::string, int>>& frequencies)
{
    std::sort(frequencies.begin(), frequencies.end(),
        [](const auto& first, const auto& second) {
            if (first.second != second.second) {
                return first.second > second.second;
            }

            return first.first < second.first;
        });
}

#endif // SORT_H