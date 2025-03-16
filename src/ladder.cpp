#include "ladder.h" 

void error(string word1, string word2, string msg) {
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << "\n";
}

bool edit_distance_within(const string& first_word, const string& second_word, int max_distance) {
    int len1 = first_word.size(), len2 = second_word.size();
    if (abs(len1 - len2) > max_distance) return false;
    
    int diff_count = 0, i = 0, j = 0;
    while (i < len1 || j < len2) {
        if (i < len1 && j < len2 && first_word[i] == second_word[j]) {
            i++; j++;
        } else {
            diff_count++;
            if (diff_count > max_distance) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& start_word, const string& target_word, const set<string>& dictionary) {
    string start_lower = start_word;
    string target_lower = target_word;
    for (char& c : start_lower) c = tolower(c);
    for (char& c : target_lower) c = tolower(c);

    if (start_lower == target_lower) {
        error(start_word, target_word, "Start and end words must be different");
        return {};
    }
    if (!dictionary.count(target_lower)) {
        error(start_word, target_word, "End word not in dictionary");
        return {};
    }
    
    if (!edit_distance_within(start_lower, target_lower, dictionary.size())) {
        return {};
    }

    queue<pair<string, vector<string>>> ladder_queue;
    set<string> visited;
    ladder_queue.push({start_lower, {start_lower}});
    visited.insert(start_lower);
    
    while (!ladder_queue.empty()) {
        int queue_size = ladder_queue.size();
        set<string> words_to_mark; 
        
        for (int i = 0; i < queue_size; i++) {
            auto [current_word, current_ladder] = ladder_queue.front();
            ladder_queue.pop();
            
            for (const auto& word : dictionary) {
                if (is_adjacent(current_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    
                    if (word == target_lower) {
                        return new_ladder;
                    }
                    
                    ladder_queue.push({word, new_ladder});
                    words_to_mark.insert(word);
                }
            }
        }
        visited.insert(words_to_mark.begin(), words_to_mark.end());
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open dictionary file: " + file_name);
    }
    
    string word;
    while (in >> word) {
        for (char& c : word) c = tolower(c);
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << " ";
    cout << "\n";
}



void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(ladder);
}