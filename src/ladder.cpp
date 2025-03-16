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
    if (start_word == target_word) return {};
    if (!dictionary.count(target_word)) return {};
    
    queue<vector<string>> queue_ladders;
    set<string> explored_words;
    queue_ladders.push({start_word});
    explored_words.insert(start_word);
    
    while (!queue_ladders.empty()) {
        auto current_path = queue_ladders.front(); queue_ladders.pop();
        string last_word = current_path.back();
        
        for (const auto& word : dictionary) {
            if (is_adjacent(last_word, word) && explored_words.insert(word).second) {
                vector<string> new_path = current_path;
                new_path.push_back(word);
                
                if (word == target_word) return new_path;
                queue_ladders.push(new_path);
            }
        }
    }
    return {};
}



void load_words(set<string>& dictionary, const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << file_path << "\n";
        return;
    }
    string word;
    while (getline(file, word)) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary.insert(word);
    }
    file.close();
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
    cout << " ";
    cout << "\n";
}



void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(ladder);
}