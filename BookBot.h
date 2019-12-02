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
 srand(seed); //seed the random number generator
}

bool BookBot :: isEndPunctuation(const char character){
  if(character == '.') return true; //return true if the character is a period
  else if(character == '?') return true; //return true if the character is a question mark
  else if(character == '!') return true; //return true if the character is an exclamation mark
  else
  return false; //returns false
}

void BookBot :: readIn(const std::string & filename){
  std::ifstream textfile(filename); //opens the file and closes once the end of the function
  std::string word; //a string word to store in the individual words from the files
  std::string old_word="^"; //a string word to store in the previous word and have "^" it to indicate the start of a sentence
  while(textfile >> word){
  textfile.ignore();
  sanitize(word); //call the sanitize function to remove non-alphabetic characters like dashes, slashes, etc.
  if(isEndPunctuation(word[word.size()-1])){ //if the current word ends with a punctuation
        std::string punctuation(1, word[word.size() - 1]);  //grabs the punctuation of the word and stores it
        word = word.substr(0, word.size() - 1); //removes the punctuation word
        markov_chain[old_word].push_back(word); //searches for the keyword of old_word and either find and push_back the current word without the punctuation or creates a new entry with the old_word as the key entry and push_back the current word without the punctuation
        markov_chain[word].push_back(punctuation); //searches for the keyword of the current word and either find and push_back the punctuation or creates a new entry with the current word as the key entry and push_back the punctuation
        markov_chain[punctuation].push_back("$"); //searches for the key for the specific punctuation and creates a new entry with the punctuation as the key entry and push_back the question mark to indicate the end of a sentence
        old_word = "^"; //set the old_word as "^" to indicate the start of a new sentence
  }
  else{
      markov_chain[old_word].push_back(word); //searches for the keyword of old_word and either find and push_back the current word or creates a new entry with the old_word as the key entry and push_back the current word
      old_word = word; //set the old_word as the current word
  }
}
}

std::vector<std::string> BookBot :: getValues(const std::string & key){
  return markov_chain[key]; //returns the vector of the specific key
}

std::string BookBot :: generateSentence(){
  std::string sentence; //a string sentence to generate the sentence
  std::string token; //a string to hold the key that will add to the sentence and used to search in the map
  int size = rand() % markov_chain["^"].size(); //an int value to hold the random generator between 0 to the size of the key vector
  token = markov_chain["^"].at(size); //gets the random word from the key vector using the random generator number
  sentence = token;
  while(token !="$"){ //a while loop that will stop when the token is "$"
      size = rand() % markov_chain[token].size(); //gets the random word from the key vector using the random generator number
      token = markov_chain[token].at(size); //gets the random word from the key vector using the random generator number
      if(token == "$"){//if the token word is "$"
        std::string punctuation(1, sentence[sentence.size() - 1]); //grabs the punctuation from the sentence
        sentence = sentence.substr(0, sentence.size() - 2); //removes both the punctuation of sentence and the space at the end
        sentence +=punctuation; //adds the punctuation to the sentence without any spacing between it
      }
      else{
        sentence += " " + token; //adds the token word to the sentence string with a space between it
      }
    }

  return sentence; //returns the generated sentence  
}
