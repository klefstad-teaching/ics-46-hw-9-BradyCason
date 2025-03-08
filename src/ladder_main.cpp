#include "ladder.h"

int main(){
    // verify_word_ladder();

    set<string> word_list;
    load_words(word_list, "src/words.txt");
    print_word_ladder(generate_word_ladder("awake", "sleep", word_list));
    
    return 0;
}