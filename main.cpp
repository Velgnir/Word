#include "files.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>

void counting_words(const std::vector<std::string>& dictionary, std::map<std::string, size_t>& map, const size_t limit1, const size_t limit2){
    std::string word;
    for (size_t i = limit1; i < limit2; ++i) {
        word = dictionary[i];
        preprocessing(word);
        map[word]+=1;
    }
}

void merge_2_maps(std::map<std::string, size_t>& map1, const std::map<std::string, size_t>& map2){
    for( auto const& [word, number] : map2){
        map1[word]+=number;
    }
}

int main(int argc, char *argv[]) {
    //part 0:
    std::string b; // path to file
    std::string word; // it is using for read text from file
    std::string zero_word;
    // it is using for correcting work of cycle after deleting some chars from words
    std::map<std::string, size_t> map_of_words;

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
    std::map<std::string, size_t> map_of_second_part;
    std::stringstream full_file_text;
    full_file_text << full_file;
    while (full_file_text>>word){
       dict.push_back(word);
    }
    std::thread t1,t2;
    if (dict.size() % 2 == 0) {
        t1 = std::thread(counting_words, dict, map_of_words, 0, dict.size()/2);
        t2 = std::thread(counting_words, dict, map_of_second_part, dict.size()/2, dict.size());
    }
    else{
        t1 = std::thread(counting_words, dict, map_of_words, 0, (dict.size()-1)/2);
        t2 = std::thread(counting_words, dict, map_of_second_part, (dict.size()-1)/2, dict.size());
    }
    t1.join();
    t2.join();
    merge_2_maps(map_of_words, map_of_second_part);
    //part 5(PRINT):
    print(map_of_words,"filea.txt","filen.txt");
}

