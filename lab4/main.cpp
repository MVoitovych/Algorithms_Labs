#include "funcs.h"

using namespace ::std;


int main() {

    freopen("cond.txt", "r", stdin);

    int n;
    cin >> n;

    vector<string> words_list(n);
    map<string, int> max_chain_len;

    getVecWithChain(words_list, max_chain_len, n);

    cout << getMaxChain(words_list, max_chain_len);

    fclose(stdin);
    return 0;
}


