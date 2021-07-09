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

    std::stringstream full_file_text;
    full_file_text << full_file;
    std::vector<std::string> dict;
    //part 2-3
    while(full_file_text>>word){
        dict.push_back(word);
    }
    std::thread t1,t2;
    std::map<std::string, size_t> map2;
    if (dict.size() % 2 == 0) {
        t1 = std::thread(t, dict, &map2, 0, dict.size()/2);
        t2 = std::thread(t, dict, &map_of_words, dict.size()/2, dict.size());
    }
    else{
        t1 = std::thread(t, dict, &map2, 0, (dict.size()-1)/2);
        t2 = std::thread(t, dict, &map_of_words, (dict.size()-1)/2, dict.size());
    }
    t1.join();
    t2.join();
    for (auto words: map2) {
        map_of_words.insert(words);
    }
    //part 5(PRINT):
    print(map_of_words,"filea.txt","filen.txt");
}

