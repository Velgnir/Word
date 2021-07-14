#include "counter.hpp"

void preprocessing(std::string& word) {
    int count_bug = 0;
    for (size_t i = 0; i < word.length() + count_bug; ++i) {
        if (!isalpha(word[i - count_bug])) {
            word.erase(i - count_bug, 1);
            count_bug += 1;
        } else {
            word[i - count_bug] = tolower(word[i - count_bug]);
        }
    }
}


void map_word_adder(const std::string& word, std::map<std::string, size_t>& map_of_words){
    if (word.length() > 0) {
        map_of_words[word] += 1;
    }
}

void counting_words(const std::vector<std::string>& dictionary, std::vector<std::map<std::string, size_t>>& all_maps, const size_t limit,const size_t number_of_thread){
    std::string word;
    size_t other_words = 0;
    if (number_of_thread == all_maps.size()-1)
        other_words = dictionary.size()-((number_of_thread+1)*limit);
    for (int i = number_of_thread*limit; i < (number_of_thread+1)*limit+other_words; ++i) {
        word = dictionary[i];
        preprocessing(word);
        map_word_adder(word, all_maps[number_of_thread]);
        if (i==dictionary.size()-1)
            break;
    }
}

void merge_all_maps(std::vector<std::map<std::string, size_t>>& all_maps){
    for (size_t i = 1; i < all_maps.size(); ++i) {
        for (auto const&[word, number] : all_maps[i]) {
            all_maps[0][word] += number;
        }
    }
}
