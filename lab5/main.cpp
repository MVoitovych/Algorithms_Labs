#include <iostream>
#include <unordered_map>
#include <ctime>

using namespace ::std;

bool boyerMooreHorspoolAlgorithm(string &hay_bale, string &needle) {

    int needle_len = (int) needle.size() - 1;
    int hay_bale_len = (int) hay_bale.size();

    unordered_map<char, int> stop_table;
    stop_table[needle[needle_len]] = needle_len + 1;

    for (int i = 1; i <= needle_len; ++i) {
        char current_char = needle[needle_len - i];

        if (!stop_table[current_char] || stop_table[current_char] > i)
            stop_table[current_char] = i;
    }

    for (int hay_idx = needle_len; hay_idx < hay_bale_len;) {

        for (int needle_idx = 0; needle_idx <= needle_len + 1; ++needle_idx) {

            if (needle_idx > needle_len) return true;

            char current_char = hay_bale[hay_idx];
            int step = stop_table[current_char] ? stop_table[current_char] : needle_len + 1;

            if (hay_bale[hay_idx - needle_idx] == needle[needle_len - needle_idx]) continue;

            hay_idx += step;
            break;
        }

    }
    return false;

}

void test(string &hay_bale, string &needle, bool(*func)(string &, string &)) {
    clock_t start = clock();
    bool match = func(hay_bale, needle);
    cout << (match ? "match " : "no match") << "\n";
    clock_t end = clock();
    cout << ((double) (end - start)) / CLOCKS_PER_SEC << " seconds\n============================\n";
}

void getStrings(string &hay_bale, string &needle) {
    getline(cin, hay_bale);
    getline(cin, needle);

    cout << hay_bale.size() << " bale size\n";
    cout << needle.size() << " needle size\n";
}


int main() {

    freopen("cond.txt", "r", stdin);

    string hay_bale, needle;
    
    cout << "BAD variant O(M*N) \n";
    getStrings(hay_bale, needle);
    test(hay_bale, needle, &boyerMooreHorspoolAlgorithm);

    cout << "GOOD variant O(M/N) \n";
    getStrings(hay_bale, needle);
    test(hay_bale, needle, &boyerMooreHorspoolAlgorithm);

    cout << "Random generated text variant O(M/E) where E = number of possible characters\n";
    getStrings(hay_bale, needle);
    test(hay_bale, needle, &boyerMooreHorspoolAlgorithm);


    return 0;
}
