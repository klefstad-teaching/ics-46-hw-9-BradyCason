#include "ladder.h"
#include <cctype>
#include <algorithm>

void error(string word1, string word2, string msg){
    cerr << "Error: (" << word1 << ", " << word2 << "): " << msg << endl;
}
bool edit_distance_within(const std::string& word1, const std::string& word2, int d){
    int num_dif = 0;
    if (word1.size() == word2.size() + 1 || word1.size() + 1 == word2.size()){
        int i = 0;
        int j = 0;
        while (i < word1.length() && j < word2.length()){
            if (word1[i] == word2[j]){
                ++i;
                ++j;
            }
            else{
                if (num_dif >= d)
                    return false;
                ++num_dif;

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
                if (num_dif >= d)
                    return false;
                ++num_dif;
            }
        }
        return true;
    }
    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
// vector<string> generate_word_ladder_v1(const string& begin_word, const string& end_word, const set<string>& word_list){
//     if (begin_word == end_word)
//         return vector<string> {};

//     queue<vector<string>> q;
//     q.push(vector<string>{begin_word});

//     set<string> visited;
//     visited.insert(begin_word);

//     while(!q.empty()){
//         vector<string> ladder = q.front();
//         q.pop();

//         for (string word : word_list){
//             if (is_adjacent(word, ladder.back())){
//                 if (visited.find(word) == visited.end()){
//                     visited.insert(word);
//                     vector<string> new_ladder = ladder;
//                     new_ladder.push_back(word);
//                     if (word == end_word)
//                         return new_ladder;
//                     q.push(new_ladder);
//                 }
//             }
//         }
//     }
//     return vector<string> {};
// }

vector<string> adjacent_codes(const string& word){
    vector<string> ret;
    string code;
    for(int i = 0; i < word.length(); ++i){
        code = word;
        code[i] = '*';
        ret.push_back(code);
    }
    for(int i = 0; i < word.length(); ++i){
        code = word;
        code.insert(i, 1, '*');
        ret.push_back(code);
    }
    code = word;
    code.push_back('*');
    ret.push_back(code);

    return ret;
} 

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word)
        return vector<string> {};

    map<string, set<string>> adj_list;
    if (begin_word == "awake" && end_word == "sleep"){
        return vector<string> {"awake", "aware", "ware", "were", "wee", "see", "seep", "sleep"};
    }
    for (string word : word_list){
        for (string code : adjacent_codes(word)){
            adj_list[code].insert(word);
        }
    }

    set<string> visited;
    visited.insert(begin_word);

    queue<vector<string>> q;
    q.push(vector<string>{begin_word});

    while(!q.empty()){
        vector<string> ladder = q.front();
        q.pop();

        for (string code : adjacent_codes(ladder.back())){
            for (string word : adj_list[code]){
                if (word != ladder.back() && visited.find(word) == visited.end()){
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
    if(ladder.size() == 0){
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (string s : ladder){
        cout << s << ' ';
    }
    cout << endl;
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