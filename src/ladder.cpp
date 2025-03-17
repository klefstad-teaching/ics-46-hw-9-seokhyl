
// bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
// bool is_adjacent(const string& word1, const string& word2);
// vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
// void load_words(set<string> & word_list, const string& file_name);
// void print_word_ladder(const vector<string>& ladder);
// void verify_word_ladder();

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error " << "(" << word1 << ", " << word2 << "): " << msg << endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {

}

bool is_adjacent(const string& word1, const string& word2) {
    if (abs((int)(word1.size()) - int(word2.size())) > 1) return false;
    if (word1.size() == word2.size()) {
        int wordLen = word1.size();
        int diffCount = 0;
        for (int i = 0; i < wordLen; ++i) 
            if (word1[i] != word2[i]) ++diffCount;
        // cout << word1 << ' ' << word2 << ' ' << diffCount << endl;
        return diffCount == 1;
    } else {
        string word1Cpy = word1;
        string word2Cpy = word2;
        if (word1Cpy.size() < word2Cpy.size())
            swap(word1Cpy, word2Cpy); // ensure word1 is longer
        int wordLen = word1Cpy.size();
        int i = 0, j = 0, diffCount = 0;
        while(i < wordLen) {
            if (word1Cpy[i] != word2Cpy[j]) {
                ++diffCount;
                ++i;
                if (diffCount != 1) return false;
                continue;
            }
            ++i;
            ++j;
        }
        return true;
    }
    return false;
}

template <typename T>
void printVec(vector<T>& v) {
    for (T e : v)
        cout << e << ' ';
    cout << endl;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // cout << word_list.size() << endl;
    if (begin_word == end_word) { error(begin_word, end_word, "begin_word and end_word are identical."); return vector<string>{};}

    queue<vector<string>> ladder_queue{};
    ladder_queue.push(vector<string>{begin_word});
    set<string> visited{};
    visited.insert(begin_word);
    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front(); ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.count(word) == 0) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word) {
                        // printVec(new_ladder);
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    // cout << "\nNO PATH\n";
    return vector<string>{}; // not found
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while(in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (string s : ladder)
        cout << s << ' ';
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "./src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // cout << generate_word_ladder("cat", "dog", word_list).size() << endl;
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}