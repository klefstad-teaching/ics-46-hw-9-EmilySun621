#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs(int(str1.length()) - int(str2.length())) > d) return false;
    int count = 0;
    for (size_t i = 0; i < min(str1.length(), str2.length()); ++i) {
        if (str1[i] != str2[i]) {
            count++;
            if (count > d) return false;
        }
    }
    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            diff_count++;
            if (diff_count > 1) return false;
        }
    }
    return diff_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladders.empty()) {
        vector<string> ladder = ladders.front();
        ladders.pop();
        string last_word = ladder.back();
        
        if (last_word == end_word) return ladder;
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                ladders.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    string begin_word, end_word;
    cout << "Enter begin word: ";
    cin >> begin_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}
