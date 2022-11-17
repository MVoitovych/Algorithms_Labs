#include <iostream>
#include "unordered_map"

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


int main() {

    string hay_bale = "neneedleedleqwefrgterwedQERFWQEFQWFneedle";
    string needle = "needle";

    cout << (boyerMooreHorspoolAlgorithm(hay_bale, needle) ? "match " : "no match") << "\n";


    return 0;
}
