#ifndef LAB4_FUNCS_H
#define LAB4_FUNCS_H

#endif //LAB4_FUNCS_H
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"

using namespace ::std;

int getMaxChain(vector<string> &words_list, map<string, int> &max_chain_len);

void getVecWithChain(vector<string> &words_list, map<string, int> &max_chain_len, int &n);
