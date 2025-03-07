#include "ladder.h"
#include <cctype>
#include <algorithm>

void error(string word1, string word2, string msg){
    cerr << "Error: (" << word1 << ", " << word2 << "): " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    bool found_dif = false;
    if (word1.size() == word2.size() + 1 || word1.size() + 1 == word2.size()){
        int i = 0;
        int j = 0;
        while (i < word1.length() && j < word2.length()){
            if (word1[i] == word2[j]){
                ++i;
                ++j;
            }
            else{
                if (found_dif)
                    return false;
                found_dif = true;

                if (word1.size() > word2.size())
                    ++i;
                else
                    ++j;
            }
        }
        return true;
    }
    else if (word1.size() == word2.length()){
        for(int i = 0; i < word1.length(); ++i){
            if (word1[i] != word2[i]){
                if (found_dif)
                    return false;
                found_dif = true;
            }
        }
        return found_dif;
    }
    return false;
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word)
        return vector<string> {begin_word};

    queue<vector<string>> q;
    q.push(vector<string>{begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!q.empty()){
        vector<string> ladder = q.front();
        q.pop();

        for (string word : word_list){
            if (is_adjacent(word, ladder.back())){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    q.push(new_ladder);
                }
            }
        }
    }
    return vector<string> {};
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    string word;
    while (in >> word){
        std::transform(word.begin(), word.end(), word.begin(),
                   [](unsigned char c) { return std::tolower(c); });
        word_list.insert(word);
    }
}
void print_word_ladder(const vector<string>& ladder){
    for (string s : ladder){
        cout << s << ' ';
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
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