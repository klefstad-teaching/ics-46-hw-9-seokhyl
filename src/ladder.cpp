
#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error " << "(" << word1 << ", " << word2 << "): " << msg << endl;
}

int calculate_edit_distance(const std::string& str1, const std::string& str2) {
// https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
    const int m = str1.size();
    const int n = str2.size();
    int d[50][50] = {0};
    // int** d = new int[m+1][n+1];
    
    for (int i = 1; i <= m; ++i) {
        d[i][0] = i;
    }
    for (int j = 1; j <=n; ++j) {
        d[0][j] = j;
    }
    int substitutionCost = 0;
    for(int j=1; j<=n; ++j){
        for(int i=1; i<=m; ++i){
            substitutionCost = str1[i-1] == str2[j-1] ? 0 : 1;
            
            d[i][j] = min(min(d[i-1][j]+1, d[i][j-1]+1), d[i-1][j-1]+substitutionCost);
        }
    }
    // for (int i=0; i<=m; ++i){
    //     for(int j=0; j<=n; ++j) {
    //         cout << d[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    return d[m][n];
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    return calculate_edit_distance(str1, str2) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
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
            if (visited.count(word) == 0 && is_adjacent(last_word, word)) {
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