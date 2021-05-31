#include <utility>
#include <fstream>
#include <map>
#include <algorithm>
#pragma once
template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p) {
    return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B, template<class, class, class...> class M, class... Args>
std::multimap<B, A> flip_map(const M<A, B, Args...> &src) {
    std::multimap<B, A> dst;
    transform(src.begin(), src.end(),
                   std::inserter(dst, dst.begin()),
                   flip_pair<A, B>);
    return dst;
}
void print(const std::map<std::string, size_t> &map_of_words, const std::string &output_filename_a,
           const std::string &output_filename_n) {
    std::ofstream outfile_alpha;
    std::ofstream outfile_number;
    outfile_alpha.open(output_filename_a);
    outfile_number.open(output_filename_n);

    for (auto &pair:map_of_words) {
        outfile_alpha << pair.first << "\t" << pair.second << std::endl;
    }

    auto multimap_of_words = flip_map(map_of_words);

    auto it = multimap_of_words.rbegin();
    while (it != multimap_of_words.rend()) {
        outfile_number << (*it).second << "\t" << (*it).first << std::endl;
        ++it;
    }

    outfile_alpha.close();
    outfile_number.close();
}




void preprocessing(std::string *word) {
    int count_bug = 0;
    std::string wordn;
    wordn = *word;
    for (size_t i = 0; i < wordn.length() + count_bug; ++i) {
        if (!isalpha(wordn[i - count_bug])) {
            wordn.erase(i - count_bug, 1);
            count_bug += 1;
        } else {
            wordn[i - count_bug] = tolower(wordn[i - count_bug]);
        }
    }
    *word = wordn;
}


void map_word_adder(std::string word, std::map<std::string, size_t> *map_of_words){
std::map<std::string, size_t> map_of_wordn = *map_of_words;
    if (word.length() > 0) {

       map_of_wordn[word] += 1;
    }
	*map_of_words = map_of_wordn;
}



/*//part 2(we are reading text from file):
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
    }*/