#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void error(string start_word, string target_word, string message) {
    cerr << "Error: " << message << " (" << start_word << " -> " << target_word << ")\n";
}

bool edit_distance_within(const string& first_word, const string& second_word, int max_distance) {
    if (abs((int)first_word.size() - (int)second_word.size()) > max_distance) return false;
    int difference_count = 0;
    for (size_t i = 0, j = 0; i < first_word.size() && j < second_word.size(); i++, j++) {
        if (first_word[i] != second_word[j] && ++difference_count > max_distance) return false;
    }
    return true;
}

bool is_adjacent(const string& first_word, const string& second_word) {
    return edit_distance_within(first_word, second_word, 1);
}

vector<string> generate_word_ladder(const string& start_word, const string& target_word, const set<string>& dictionary) {
    if (start_word == target_word) return {start_word};
    if (!dictionary.count(target_word)) return {};
    
    queue<vector<string>> ladder_queue;
    set<string> seen_words = {start_word};
    ladder_queue.push({start_word});
    
    while (!ladder_queue.empty()) {
        auto current_ladder = ladder_queue.front(); ladder_queue.pop();
        for (const auto& word : dictionary) {
            if (is_adjacent(current_ladder.back(), word) && seen_words.insert(word).second) {
                auto new_ladder = current_ladder;
                new_ladder.push_back(word);
                if (word == target_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string>& dictionary, const string& file_path) {
    ifstream file_input(file_path);
    for (string word; file_input >> word;) dictionary.insert(word);
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
    set<string> dictionary;
    load_words(dictionary, "words.txt");
    print_word_ladder(generate_word_ladder("cat", "dog", dictionary));
}
