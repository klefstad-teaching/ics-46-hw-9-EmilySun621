#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

// Function to check if two words are adjacent (one letter change, insertion, or deletion)
bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true; // A word is always adjacent to itself
    if (abs((int)word1.length() - (int)word2.length()) > 1) return false;

    int diff_count = 0;
    size_t i = 0, j = 0;
    
    while (i < word1.length() && j < word2.length()) {
        if (word1[i] != word2[j]) {
            diff_count++;
            if (diff_count > 1) return false;
            if (word1.length() > word2.length()) i++;
            else if (word1.length() < word2.length()) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return diff_count == 1 || (diff_count == 0 && abs((int)word1.length() - (int)word2.length()) == 1);
}

// Function to check if edit distance between two words is within a given limit
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int m = str1.length(), n = str2.length();
    if (abs(m - n) > d) return false;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    
    return dp[m][n] <= d;
}

// Function to generate the shortest word ladder using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word}; // Handle same word case immediately

    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladders.empty()) {
        int level_size = ladders.size();
        set<string> words_used_in_this_level;
        
        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();
            
            if (last_word == end_word) return ladder;
            
            for (const string& word : word_list) {
                if (is_adjacent(last_word, word) && !visited.count(word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    words_used_in_this_level.insert(word);
                }
            }
        }
        for (const string& word : words_used_in_this_level) {
            visited.insert(word);
        }
    }
    return {}; // No word ladder found
}

// Function to load words from a dictionary file into a set
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

// Function to print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " "; // Space-separated for test compatibility
        cout << ladder[i];
    }
    cout << "\n";
}

// Function to interactively verify a word ladder
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
