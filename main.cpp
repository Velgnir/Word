#include "files.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>

void counting_words(const std::vector<std::string>& dictionary, std::vector<std::map<std::string, size_t>> all_maps, const size_t limit,const size_t number_of_thread){
    std::string word;
    size_t other_words = 0;
    if (number_of_thread == all_maps.size()-1)
        other_words = dictionary.size()-((number_of_thread+1)*limit);
    for (int i = number_of_thread*limit; i < (number_of_thread+1)*limit+other_words; ++i) {
        word = dictionary[i];
        preprocessing(word);
        all_maps[number_of_thread][word] += 1;
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
    size_t number_of_threads;
    // it is using for correcting work of cycle after deleting some chars from words
    std::vector<std::map<std::string, size_t>> all_maps;
    //part 1(i didn't change it):
    if (argc > 1) {
        b = std::string{argv[1]};
        size_t number_of_threads = (size_t)argv[2];
    }
    else {
        b = "input.txt";
        size_t number_of_threads = 4;
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
    th.reserve(number_of_threads);
    for (int i = 0; i < number_of_threads; ++i) {
        th[i] = std::thread(counting_words, dict, std::ref(all_maps), (size_t)(dict.size()/number_of_threads), i);
    }
    for (auto &t:th) {
        t.join();
    }
    merge_all_maps(all_maps);
    //part 5(PRINT):
    print(all_maps[0],"filea.txt","filen.txt");
}

