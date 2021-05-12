#include "./inc/files.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

int main(int argc, char *argv[]) {
    std::string last;
    std::string min;
    std::string max;
    char la1;
    std::string b;
    std::vector<int> sh2;
    std::vector<int> sh1;
    // to make possible terminal arguments.
    if (argc > 1) {
        b = std::string{argv[1]};
    } else {
        b = "./input.txt";
    }
    //
    std::string a;
    std::ifstream file(b);
    if (!file) {
        std::cout << "file wasn't open" << std::endl;
        // The exit here is very important, because the program can not working correctly after this moment.
        exit(1);
    } else {
        std::cout << "file was open" << std::endl;
    }
    while (!file.eof()) {
        getline(file, a);
        last.push_back(' ');
        for (int i = 0; i < a.length(); ++i) {
            la1 = a[i];
            last.push_back(la1);
        }
    }


    std::vector <std::string> sh;
    std::string buf;
    std::stringstream ss(last);

    std::vector <std::string> tokens;
    while (ss >> buf)
        tokens.push_back(buf);







    
std::map<std::string,int> my_map;
int count_of_word;
    for (auto &st:tokens) {
        if(my_map[st])
            count_of_word=my_map[st]+1;
        my_map.insert(make_pair(st,count_of_word));
    }
    print(my_map,"./filea.txt","./filen.txt");
    return 0;
}
