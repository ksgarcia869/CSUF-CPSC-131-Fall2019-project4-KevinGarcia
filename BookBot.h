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

BookBot::BookBot(const unsigned int seed){
 srand(seed);
}

bool BookBot :: isEndPunctuation(const char character){
  if(character == '.') return true;
  else if(character == '?') return true;
  else if(character == '!') return true;
  else
  return false;
}

void BookBot :: readIn(const std::string & filename){
  std::ifstream textfile(filename);
  std::string word;
  std::string old_word="^";
  while(textfile >> word){
  textfile.ignore();
  sanitize(word);
  std::string punctuation(1, word[word.size() - 1]);
  if(isEndPunctuation(punctuation[0])){
        word = word.substr(0, word.size() - 1);
        markov_chain[old_word].push_back(word);
        markov_chain[word].push_back(punctuation);
        markov_chain[punctuation].push_back("$");
        old_word = "^";
  }
  else{
      markov_chain[old_word].push_back(word);
      old_word = word;
  }
}
}

std::vector<std::string> BookBot :: getValues(const std::string & key){
  return markov_chain[key];
}

std::string BookBot :: generateSentence(){
  std::string sentence;
  std::string token;
  int size = rand() % markov_chain["^"].size();
  token = markov_chain["^"].at(size);
  sentence = token;
  while(token !="$"){
      size = rand() % markov_chain[token].size();
      token = markov_chain[token].at(size);
      if(token == "$"){
        std::string punctuation(1, sentence[sentence.size() - 1]);
        sentence = sentence.substr(0, sentence.size() - 2);
        sentence +=punctuation;
      }
      else{
        sentence += " " + token;
      }
    }

  return sentence;
}
