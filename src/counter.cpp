#include "counter.hpp"

void preprocessing(std::string &word) {
    int count_bug = 0;
    size_t i = 0;
    while (i < word.length() + count_bug) {
        if (!isalpha(word[i - count_bug])) {
            word.erase(i - count_bug, 1);
            count_bug += 1;
        } else {
            word[i - count_bug] = tolower(word[i - count_bug]);
        }
        i++;
    }
}

void map_word_adder(const std::string &word, std::map<std::string, size_t> &map_of_words) {
    if (word.length() > 0) {
        map_of_words[word] += 1;
    }
}

void counting_words(const std::vector<std::string> &dictionary,
                    std::map<std::string, size_t> &map) {
    std::string word;
    for (int i = 0; i < dictionary.size(); ++i) {
        word = dictionary[i];
        preprocessing(word);
        map_word_adder(word, map);
    }
}

void merge_all_maps(std::vector<std::map<std::string, size_t>> &all_maps) {
    for (size_t i = 1; i < all_maps.size(); ++i) {
        for (auto const&[word, number] : all_maps[i]) {
            all_maps[0][word] += number;
        }
    }
}

void divide_all_dictionaries(std::vector<std::vector<std::string>> &all_dicts,
                             const std::vector<std::string> &dictionary,
                             const int limit) {
    size_t other_words = dictionary.size() - limit * all_dicts.size();
    int one_word = 1;
    for (size_t number_of_dictionary = 0; number_of_dictionary < all_dicts.size(); ++number_of_dictionary) {
        if (other_words < number_of_dictionary + 1)
            other_words = 0;
        for (size_t number_of_word = limit * number_of_dictionary;
             number_of_word < limit * (number_of_dictionary + 1) + one_word;
             ++number_of_word) {
            all_dicts[number_of_dictionary].push_back(dictionary[number_of_word]);
        }
    }
}
