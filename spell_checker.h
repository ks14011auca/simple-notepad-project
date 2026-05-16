#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <utility>
#include <vector>

class spell_checker {
public:
    bool load(const std::string& path)
    {
        std::ifstream file(path);
        if (!file) {
            return false;
        }

        words.clear();

        std::string word;
        while (file >> word) {
            word = clean_word(word);
            if (!word.empty()) {
                words.insert(word);
            }
        }

        return !words.empty();
    }

    [[nodiscard]] bool is_loaded() const
    {
        return !words.empty();
    }

    [[nodiscard]] bool is_misspelled(const std::string& text) const
    {
        const auto word = clean_word(text);
        return !word.empty() && !ignored_words.contains(word) && !words.contains(word);
    }

    void ignore_word(const std::string& text)
    {
        const auto word = clean_word(text);
        if (!word.empty()) {
            ignored_words.insert(word);
        }
    }

    [[nodiscard]] std::vector<std::string> suggestions(const std::string& text,
        const std::size_t limit = 5) const
    {
        const auto word = clean_word(text);
        std::vector<std::pair<int, std::string>> candidates;

        if (word.empty()) {
            return {};
        }

        for (const auto& candidate : words) {
            if (candidate.empty()) {
                continue;
            }

            if (candidate.front() != word.front()) {
                continue;
            }

            const auto length_difference = std::abs(
                static_cast<int>(candidate.size()) - static_cast<int>(word.size()));

            if (length_difference > 2) {
                continue;
            }

            const int distance = edit_distance(word, candidate, 2);
            if (distance <= 2) {
                candidates.emplace_back(distance, candidate);
            }
        }

        std::sort(candidates.begin(), candidates.end(),
            [](const auto& left, const auto& right) {
                if (left.first != right.first) {
                    return left.first < right.first;
                }

                return left.second < right.second;
            });

        std::vector<std::string> result;
        for (const auto& [distance, candidate] : candidates) {
            result.push_back(candidate);

            if (result.size() == limit) {
                break;
            }
        }

        return result;
    }

    [[nodiscard]] static std::string clean_word(const std::string& text)
    {
        std::string result;

        for (const unsigned char c : text) {
            if (std::isalpha(c)) {
                result.push_back(static_cast<char>(std::tolower(c)));
            }
        }

        return result;
    }

private:
    [[nodiscard]] static int edit_distance(const std::string& left,
        const std::string& right, const int max_distance)
    {
        std::vector<int> previous(right.size() + 1);
        std::vector<int> current(right.size() + 1);

        for (std::size_t j = 0; j <= right.size(); ++j) {
            previous[j] = static_cast<int>(j);
        }

        for (std::size_t i = 1; i <= left.size(); ++i) {
            current[0] = static_cast<int>(i);
            int best_in_row = current[0];

            for (std::size_t j = 1; j <= right.size(); ++j) {
                const int cost = left[i - 1] == right[j - 1] ? 0 : 1;

                current[j] = std::min({
                    previous[j] + 1,
                    current[j - 1] + 1,
                    previous[j - 1] + cost,
                });

                best_in_row = std::min(best_in_row, current[j]);
            }

            if (best_in_row > max_distance) {
                return max_distance + 1;
            }

            std::swap(previous, current);
        }

        return previous[right.size()];
    }

    std::set<std::string> words;
    std::set<std::string> ignored_words;
};

#endif // SPELL_CHECKER_H