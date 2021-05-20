#include "./inc/files.hpp"
#include <iostream>
#include <fstream>
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


    //part 2-3
    file>>word;
    preprocessing(&word);
    zero_word = word;
    while(file>>word){
        std::thread t(preprocessing, &word);
        std::thread t2(map_word_adder, zero_word, &map_of_words);

        t.join();
        t2.join();

        zero_word =word;
    }


    //part 5(PRINT):
    print(map_of_words,"../filea.txt","../filen.txt");
}

