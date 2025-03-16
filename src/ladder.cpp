#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")\n";
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) return false;
    int diff_count = 0;
    for (size_t i = 0, j = 0; i < str1.size() && j < str2.size(); i++, j++) {
        if (str1[i] != str2[j] && ++diff_count > d) return false;
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};
    if (!word_list.count(end_word)) return {};
    
    queue<vector<string>> ladders;
    set<string> visited = {begin_word};
    ladders.push({begin_word});
    
    while (!ladders.empty()) {
        auto ladder = ladders.front(); ladders.pop();
        for (const auto& word : word_list) {
            if (is_adjacent(ladder.back(), word) && visited.insert(word).second) {
                auto new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                ladders.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word;) word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ladder[i];
    }
    cout << "\n";
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    print_word_ladder(generate_word_ladder("cat", "dog", word_list));
}
