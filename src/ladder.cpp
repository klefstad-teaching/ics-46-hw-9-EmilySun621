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

vector<string> generate_word_ladder(const string& start_word, 
                                    const string& goal_word, 
                                    const set<string>& dictionary) {
    // Convert input words to lowercase directly
    string start_word_lower = start_word;
    string goal_word_lower = goal_word;
    transform(start_word_lower.begin(), start_word_lower.end(), start_word_lower.begin(), ::tolower);
    transform(goal_word_lower.begin(), goal_word_lower.end(), goal_word_lower.begin(), ::tolower);

    // Validate input conditions
    if (start_word_lower == goal_word_lower) {
        error(start_word, goal_word, "Starting and ending words cannot be identical");
        return {};
    }
    if (dictionary.count(goal_word_lower) == 0) {
        error(start_word, goal_word, "Goal word not found in dictionary");
        return {};
    }

    // Use BFS to find the shortest word ladder
    queue<vector<string>> ladders;
    set<string> visited;
    
    ladders.push({start_word_lower});
    visited.insert(start_word_lower);

    while (!ladders.empty()) {
        int current_level_size = ladders.size();
        set<string> level_words;

        for (int i = 0; i < current_level_size; ++i) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            const string& current_word = ladder.back();

            for (const string& candidate : dictionary) {
                if (visited.count(candidate) == 0 && is_adjacent(current_word, candidate)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(candidate);

                    if (candidate == goal_word_lower) {
                        return new_ladder;  // Found the shortest ladder
                    }

                    ladders.push(new_ladder);
                    level_words.insert(candidate);
                }
            }
        }
        // Mark all words from this level as visited
        visited.insert(level_words.begin(), level_words.end());
    }

    return {};  // No ladder found
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