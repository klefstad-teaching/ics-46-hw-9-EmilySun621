#include "ladder.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << "(" << word1 << "->" << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d){
    if (str1.length()!=str2.length()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < str1.length(); i++){
        if (str1[i] != str2[i]){
            diff_count++;
            if (diff_count > d) return false;
        }
    }
    return diff_count == d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& word1, const string& word2,const set<string>& word_list){
    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladders.empty()){
        int size = ladders.size();
        set<string> current_visited;

        for (int i = 0; i < size; i++){
            vector<string> ladder = ladder.front();
            ladders.pop();
            string last_word = ladder.back();

            if (last_word == end_word){
                return ladder;
            }
            for (const string& word: word_list){
                if (is_adjacent(last_word, word)&& visited)
            }
        }
    }
}