#pragma once
#include <utility>
#include <fstream>
#include <map>
#include <algorithm>

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
void print(const std::map<std::string, size_t> &map_of_words,
           const std::string &output_filename_a,
           const std::string &output_filename_n);

void preprocessing(std::string& word);

void map_word_adder(const std::string word, std::map<std::string, size_t>& map_of_words);