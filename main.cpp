#include "files.hpp"
#include "counter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>

int main(int argc, char *argv[]) {
    //part 0:
    std::string file_path; // path to file
    int number_of_threads;
    //part 1(i didn't change it):
    if (argc > 1) {
        file_path = std::string{argv[1]};
        number_of_threads = std::stoi(argv[2]);
    } else {
        file_path = "input.txt";
        number_of_threads = 4;
    }
    std::ifstream file(file_path);
    auto full_file = dynamic_cast<std::ostringstream &>(std::ostringstream{} << file.rdbuf()).str();
    if (!file) {
        std::cout << "file wasn't open" << std::endl;
        exit(1);
    } else {
        std::cout << "file was open" << std::endl;
    }

    std::vector<std::string> dict;
    std::string word; // it is using for read text from file
    std::stringstream full_file_text;
    full_file_text << full_file;
    while (full_file_text >> word) {
        dict.push_back(word);
    }
    std::map<std::string, size_t> map_for_cloning;
    std::vector<std::map<std::string, size_t>> all_maps;
    for (int i = 0; i < number_of_threads; ++i) {
        all_maps.push_back(map_for_cloning);
    }

    std::vector<std::vector<std::string>> all_dicts;
    std::vector<std::string> dicionary_for_cloning;
    for (int i = 0; i < number_of_threads; ++i) {
        all_dicts.push_back(dicionary_for_cloning);

    }
    divide_all_dictionaries(all_dicts, dict, (size_t) (dict.size() / number_of_threads));
    std::vector<std::thread> vector_of_threads;
    for (int i = 0; i < number_of_threads; ++i) {
        vector_of_threads.emplace_back(counting_words,
                                       std::ref(all_dicts[i]),
                                       std::ref(all_maps[i]));
    }
    for (auto &thread:vector_of_threads) {
        thread.join();
    }
    merge_all_maps(all_maps);
    //part 5(PRINT):
    print(all_maps[0], "filea.txt", "filen.txt");
}