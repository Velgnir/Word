#pragma once
#include <utility>
#include <fstream>
#include <map>
#include <algorithm>

void preprocessing(std::string& word);

void map_word_adder(const std::string& word, std::map<std::string, size_t>& map_of_words);

void counting_words(const std::vector<std::string>& dictionary, std::map<std::string, size_t>& map, const size_t limit,const size_t number_of_thread);

void merge_all_maps(std::vector<std::map<std::string, size_t>>& all_maps);