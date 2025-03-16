#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg){
    cout << word1 << word2 << msg << endl;
}


bool edit_distance_within(const string& word1, const string& word2, int d){
    if (abs((int)word1.size()- (int)word2.size()) > d)
        return false;
    if(word1.size() == word2.size()) {
        int diffCount = 0;
        for (size_t i = 0; i < word1.size(); i++) {
            if (word1[i] != word2[i]) {
                diffCount++;
                if (diffCount > d)
                    return false;
            }
        }
        return diffCount <= d;
    }
    const string& shorter = (word1.size() < word2.size()) ? word1 : word2;
    const string& longer  = (word1.size() < word2.size()) ? word2 : word1;
    int i = 0;
    int j = 0;
    bool foundDifference = 0;
    
    while (i < shorter.size() && j < longer.size()) {
        if (shorter[i] == longer[j]) {
            i++;
            j++;
        } else {
            if (foundDifference){
                return false;
            }
            foundDifference = true;
            j++;
        }
    }
    return true;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        error(begin_word, end_word, "Start and end are the same");
        return vector<string>();
    }
    queue<vector<string>> word_ladder;
    vector<string> start;
    start.push_back(begin_word);
    word_ladder.push(start);
    set<string> visited;
    visited.insert(begin_word);
    while(!word_ladder.empty()){
        vector<string> front_ladder = word_ladder.front();
        word_ladder.pop();
        string last_word = front_ladder.back();
        for(const string& word: word_list ){
            if (is_adjacent(last_word, word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string>temp_ladder(front_ladder);
                    temp_ladder.push_back(word);
                    if(word == end_word){
                        return temp_ladder;
                    }
                    word_ladder.push(temp_ladder);
                }
            }
        }
    }
    return vector<string>();
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    string word;
    while (in >> word){
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        cout << "No word ladder found."<< endl;
        return;
    }
    cout << "Word ladder found: ";
    for(auto& word: ladder){
        cout << word << " " ;
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

