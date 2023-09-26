#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <string> 
#include <vector>

std::ifstream inputFile;
std::string line;

char findBestWord(std::list<std::string> dictionaryWords, std::string word, std::string incorrectWords) {


    for (auto it = dictionaryWords.begin(); it != dictionaryWords.end();) {
        std::string currentWord = *it;
        int currentWordSize = currentWord.length() - 1; //some reason wrong size?
        

        if (currentWordSize != word.length()){
            //std::cout << "removed small : " << currentWord << std::endl;
            it = dictionaryWords.erase(it);
        }else{
            bool possibleWord = true;
            for (int i = 0; i < word.length(); i++) {
                //make sure banned word is not in list
                if (incorrectWords.find(currentWord[i]) != std::string::npos) {
                    possibleWord = false;
                    break;
                }

                //if it is a _ ignore it as could be anything
                if (word[i] != '_'){
                    if (currentWord[i] != word[i]){
                        possibleWord = false;
                    }

                }
            }

            if (possibleWord == false){
                it = dictionaryWords.erase(it);
            }else{
                ++it;
            }

        }

    }

    for (auto const &i: dictionaryWords) {
        //std::cout << i << std::endl;
    }


    //get most used letter
    std::vector<int> letterCounts(26, 0);
    for (const std::string& word : dictionaryWords) {
        for (char c : word) {
            if (std::islower(c)) {
                letterCounts[c - 'a']++;
            }
        }
    }

    char mostFrequentLetter = '_';
    int maxCount = 0;

    for (int i = 0; i < 26; ++i) {
        //make sure word is not already done
        if (word.find('a' + i) == std::string::npos) {
            if (letterCounts[i] > maxCount) {
                maxCount = letterCounts[i];
                mostFrequentLetter = 'a' + i;
            }
        }

    }

    std::cout << "letter to guess: " << mostFrequentLetter << std::endl;
    //std::cout << "Count: " << maxCount << std::endl;

    return mostFrequentLetter;

}

int main() {
    std::cout << "loading word list" << std::endl;
    
    inputFile.open("wordlist.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Return an error code
    }

    std::list<std::string> dictionaryWords = {};

    while (std::getline(inputFile, line)) {
        dictionaryWords.push_front(line);
    }

    std::cout << "loaded " << dictionaryWords.size() << " words" << std::endl;

    //std::string currentWords = "i__n"; 

    //to use the ai enter in word and words already used here, use _ for not known
    std::string word = "";
    std::string incorrectWords = "";
    char mostCommonLetter = '_';

    while (true){
        std::cout << std::endl;
        std::cout << "Type word state (make all lowercase & unkown is underscore): "; // Type a number and press enter
        std::cin >> word;

        if (mostCommonLetter != '_'){
            if (word.find(mostCommonLetter) == std::string::npos) {
                std::cout << mostCommonLetter << " not used, adding to incorrect words list" << std::endl;
                incorrectWords.push_back(mostCommonLetter);

            }
        }

        if (word.find('_') == std::string::npos) {
            std::cout << "congrats you won!" << std::endl;
            return 0;
        }

        mostCommonLetter = findBestWord(dictionaryWords, word, incorrectWords);

        if (mostCommonLetter == '_'){
            std::cout << "no words left to guess, game over :(" << std::endl;
            return 0;
        }
    }





}
//todo
//multi word support
//make sure input size is same after inputting new word

//         g++ main.cpp -O2 -o builds/hangManAi && x86_64-w64-mingw32-g++ main.cpp -O2 -o builds/hangManAi-64x && i686-w64-mingw32-g++ main.cpp -O2 -o builds/hangManAi-86x


//linux test : g++ main.cpp -O2 -o hangManAi && ./hangManAi
