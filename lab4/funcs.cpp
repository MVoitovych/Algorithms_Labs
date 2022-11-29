#include "funcs.h"

void getVecWithChain(vector<string> &words_list, map<string, int> &max_chain_len, int &n) {
    for (int i = 0; i < n; i++) {
        cin >> words_list[i];
        max_chain_len[words_list[i]] = 1;
    }
    sort(words_list.begin(), words_list.end(), [](string &a, string &b) -> bool {
        return a.length() <= b.length();
    });

    for (string &w: words_list) {
        cout << w << endl;
    }
    cout << "=================\n";
}

int getMaxChain(vector<string> &words_list, map<string, int> &max_chain_len) {
    int max_len = 0;

    for (string &word: words_list) {

        for (int i = 0; i < word.size(); ++i) {
            string next_word = "";
            for (int j = 0; j < word.size(); ++j) {
                if (j != i) next_word += word[j];
            }
            if (max_chain_len[next_word])
                max_chain_len[word] = max(max_chain_len[word], max_chain_len[next_word] + 1);

        }
//        max_len = max(max_len, max_chain_len[word]);
        if (max_len < max_chain_len[word]) {
            max_len = max_chain_len[word];
            cout << word << endl;
        }


    }
    cout << "=================\n";
    return max_len;
}

