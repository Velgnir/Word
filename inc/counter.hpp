#pragma once

#include <utility>
#include <fstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <thread>

void preprocessing(std::string &word);

void map_word_adder(const std::string &word, std::map<std::string, size_t> &map_of_words);

void counting_words(const std::vector<std::string> &dictionary, std::map<std::string, size_t> &map);

void merge_all_maps(std::vector<std::map<std::string, size_t>> &all_maps);

void divide_all_dictionaries(std::vector<std::vector<std::string>> &all_dicts,
                             const std::vector<std::string> &dictionary,
                             const int limit);