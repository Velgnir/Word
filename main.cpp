#include "files.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>

void counting_words(const std::vector<std::string>& dictionary, std::vector<std::map<std::string, size_t>> all_maps, const size_t limit){
    std::string word;
    size_t counted_word=0;
    for (size_t j = 0; j < all_maps.size(); ++j) {
        for (size_t i = j*limit; i < (j+1)*limit; ++i) {
            counted_word++;
            word = dictionary[i];
            preprocessing(word);
            map_word_adder(word, all_maps[j]);
            if (counted_word==dictionary.size())
                break;
            else if (counted_word+limit>dictionary.size()){
                for (size_t k = 1; k < counted_word+limit-dictionary.size(); ++k) {
                    word = dictionary[i+k];
                    preprocessing(word);
                    map_word_adder(word, all_maps[j]);
                }
                break;
            }
        }
    }
}

void merge_all_maps(std::vector<std::map<std::string, size_t>> all_maps){
    for (size_t i = 1; i < all_maps.size(); ++i) {
        for (auto const&[word, number] : all_maps[i]) {
            all_maps[0][word] += number;
        }
    }
}

int main(int argc, char *argv[]) {
    //part 0:
    std::string b; // path to file
    std::string word; // it is using for read text from file
    std::string zero_word;
    // it is using for correcting work of cycle after deleting some chars from words
    std::vector<std::map<std::string, size_t>> all_maps;
    size_t number_of_thread = (size_t)argv[2];

    //part 1(i didn't change it):
    if (argc > 1) {
        b = std::string{argv[1]};
    } else {
        b = "input.txt";
    }
    std::ifstream file(b);
    auto full_file = dynamic_cast<std::ostringstream &>(std::ostringstream{} << file.rdbuf()).str();
    if (!file) {
        std::cout << "file wasn't open" << std::endl;
        exit(1);
    } else {
        std::cout << "file was open" << std::endl;
    }

    std::vector<std::string> dict;
    std::stringstream full_file_text;
    full_file_text << full_file;
    while (full_file_text>>word){
       dict.push_back(word);
    }
    std::vector<std::thread> th;
    th.reserve(number_of_thread);
    for (auto &t: th) {
        t = std::thread(counting_words, dict, std::ref(all_maps), dict.size()/number_of_thread);
    }
    for (auto &t:th) {
        t.join();
    }
    merge_all_maps(all_maps);
    //part 5(PRINT):
    print(all_maps[0],"filea.txt","filen.txt");
}

