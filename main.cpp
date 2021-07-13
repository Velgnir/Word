#include "files.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>

int main(int argc, char *argv[]) {
    //part 0:
    std::string b; // path to file
    std::string word; // it is using for read text from file
    std::string zero_word;
    int number_of_threads;
    // it is using for correcting work of cycle after deleting some chars from words
    std::vector<std::map<std::string, size_t>> all_maps;
    //part 1(i didn't change it):
    if (argc > 1) {
        b = std::string{argv[1]};
        number_of_threads = (size_t)argv[2];
    }
    else {
        b = "input.txt";
        number_of_threads = 4;
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
    std::map<std::string, size_t> map_for_cloning;
    for (int i = 0; i < number_of_threads; ++i) {
        all_maps.push_back(map_for_cloning);
    }
    std::vector<std::thread> th;
    for (int i = 0; i < number_of_threads; ++i) {
        th.emplace_back(std::thread(counting_words, dict, std::ref(all_maps), (size_t)(dict.size()/number_of_threads), i));
    }
    for (auto &t:th) {
        t.join();
    }
    merge_all_maps(all_maps);
    //part 5(PRINT):
    print(all_maps[0],"filea.txt","filen.txt");
}