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

    std::vector<std::map<std::string, size_t>> all_maps;
    all_maps.resize(number_of_threads);

    std::vector<std::vector<std::string>> all_dicts;        
    for (int i = 0; i < number_of_threads - 1; ++i) {
        all_dicts.push_back(std::vector<std::string> (dict.begin() + i*((size_t) (dict.size() / number_of_threads)),
                                                      dict.begin() + (i+1)*((size_t) (dict.size() / number_of_threads))));
    }
    all_dicts.push_back(std::vector<std::string> (dict.begin() + (number_of_threads-2)*((size_t) (dict.size() / number_of_threads)),
                                                  dict.end()));
    std::vector<std::thread> vector_of_threads;
    for (int i = 0; i < number_of_threads-1; ++i) {
        vector_of_threads.emplace_back(counting_words,
                                       std::ref(all_dicts[i]),
                                       std::ref(all_maps[i]));
    }

    counting_words(all_dicts[number_of_threads-1], all_maps[number_of_threads-1]);
    for (auto &thread:vector_of_threads) {
        thread.join();
    }
    merge_all_maps(all_maps);
    //part 5(PRINT):
    print(all_maps[0], "filea.txt", "filen.txt");
}