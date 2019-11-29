#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <iostream>

#include "sanitize.h"

class BookBot {
private:
    std::map<std::string, std::vector<std::string>> markov_chain;

public:
    BookBot(const unsigned int seed);

    void readIn(const std::string & filename);
    bool isEndPunctuation(const char character);
    std::vector<std::string> getValues(const std::string & key);
    std::string generateSentence();
};
