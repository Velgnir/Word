#include "./inc/files.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

int main(int argc, char *argv[]) {
    //part 0:
    std::string b; // path to file
    std::string word; // it is using for read text from file
    int count_bug;  // it is using for correcting work of cycle after deleting some chars from words
    std::map<std::string, size_t> map_of_words;




    //part 1(i didn't change it):
    if (argc > 1) {
        b = std::string{argv[1]};
    } else {
        b = "../input.txt";

    }
    std::ifstream file(b);//file on the 'b' path
    if (!file) {
        std::cout << "file wasn't open" << std::endl;
        exit(1);
    } else {
        std::cout << "file was open" << std::endl;
    }


    //part 2(we are reading text from file):
    while(file>>word) {
        count_bug = 0;
        for (size_t i = 0; i < word.length() + count_bug; ++i) {
            if (!isalpha(word[i - count_bug])) {
                word.erase(i - count_bug, 1);
                count_bug += 1;
            } else {
                word[i - count_bug] = tolower(word[i - count_bug]);
            }
        }// part 3(we are making map with our words):
        if (word.length() > 0) {

            auto itr = map_of_words.find(word);
            if (itr != map_of_words.end()) {
                map_of_words[word] += 1;
            } else {
                map_of_words.insert(make_pair(word, 1));
            }
        }
    }


    //part 5(PRINT):
    print(map_of_words,"../filea.txt","../filen.txt");
}