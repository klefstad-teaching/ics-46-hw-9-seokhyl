
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error " << "(" << word1 << ", " << word2 << "): " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int str1Size = str1.size();
    int str2Size = str2.size();
    if (abs(str1Size - str2Size) > d) { return false; }

    int diffCnt=0, i=0, j=0;
    while(i<str1Size && j<str2Size) {
        if(str1[i] != str2[j]) {
            ++diffCnt;
            if (diffCnt > d) { return false; }
            if (str1Size > str2Size) ++i;
            else if (str1Size > str2Size) ++j;
            else { ++i; ++j; }
        } else { ++i; ++j; }
    }
    diffCnt += str1Size - i + str2Size - j;
    return diffCnt <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) { return {};}

    queue<vector<string>> ladder_queue{};
    set<string> visited{};
    ladder_queue.push(vector<string>{begin_word});
    visited.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front(); ladder_queue.pop();
        string last_word = ladder.back();
        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {}; // not found
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while(in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        error("","","No word ladder found.");
        return;
    }

    cout << "Word ladder found: ";
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



