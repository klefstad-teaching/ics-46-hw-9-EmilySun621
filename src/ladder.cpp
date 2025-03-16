#include "ladder.h" 

void error(string word1, string word2, string msg) {
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << "\n";
}


bool edit_distance_within(const string& str1, const string& str2, int max_diff) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > max_diff) {
        return false;
    }
    int pos1 = 0, pos2 = 0, differences = 0;
    while (pos1 < len1 || pos2 < len2) {

        if (differences > max_diff) {
            return false;
        }

        if (pos1 < len1 && pos2 < len2) {
            if (str1[pos1] == str2[pos1]) {
                pos1++;
                pos2++;
            } else {
                differences++;
                if (len1 > len2) pos1++;      // Extra char in str1
                else if (len2 > len1) pos2++; // Extra char in str2
                else { pos1++; pos2++; }      // Substitution
            }
        }
        else {
            differences += (len1 - pos1) + (len2 - pos2);
            break;
        }
    }

    return differences <= max_diff;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& start_word, 
                                 const string& goal_word, 
                                 const set<string>& dictionary) {

    string start = start_word;
    string goal = goal_word;
    for (char& letter : start) letter = tolower(letter);
    for (char& letter : goal) letter = tolower(letter);


    if (start == goal) {
        error(start_word, goal_word, "Starting and ending words cannot be identical");
        return {};
    }

    if (dictionary.find(goal) == dictionary.end()) {
        error(start_word, goal_word, "Goal word not found in dictionary");
        return {};
    }

 
    queue<vector<string>> chain_queue;
    set<string> explored_words;
    
    chain_queue.push({start});


    while (!chain_queue.empty()) {
        int level_size = chain_queue.size();
        set<string> words_to_track;

        // Process each chain at current level
        for (int count = 0; count < level_size; count++) {
            vector<string> current_chain = chain_queue.front();
            chain_queue.pop();
            string current_end = current_chain.back();

            // Check each dictionary word
            for (const string& next_word : dictionary) {
                if (is_adjacent(current_end, next_word) && 
                    explored_words.find(next_word) == explored_words.end()) {
                    vector<string> extended_chain = current_chain;
                    extended_chain.push_back(next_word);

                    if (next_word == goal) {
                        return extended_chain;
                    }
                    
                    chain_queue.push(extended_chain);
                    words_to_track.insert(next_word);
                }
            }
        }
        // Update explored words after level is complete
        explored_words.insert(words_to_track.begin(), words_to_track.end());
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