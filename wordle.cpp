 // For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void combinations(std::string in, std::string floating, std::string &current, std::set<std::string> &words, const std::set<std::string> &dict);
void checkValid(std::string floating, std::set<std::string> &words);
bool validHelper(std::string floating, std::string word, bool* check);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::string in_ = in; //make copies so our helper functions can work
  std::string floating_ = floating; 
    // Add your code here
    std::set<std::string> possibleWords;
    if (in.empty()){return possibleWords;}
    //pass thru fxn that generates all possible combis
    std::string current = ""; //create empty string to pass thru function
    combinations(in_, floating_,current, possibleWords, dict);
    //pass thru fxn that checks which words are valid.
    //std::set<std::string>::iterator it = possibleWords.begin();
    /*/while (it!= possibleWords.end()){
      // eliminates all invalid words first before we pass our floating characters through
      if (dict.find(*it)==dict.end()){
        possibleWords.erase(it++);
        continue;
      }
      ++it;
    } /*/
    //cout << floating_ << endl;
    checkValid(floating_, possibleWords);
    return possibleWords;

}

void combinations (std::string in, std::string floating, std::string &current, std::set<std::string> &words, const std::set<std::string> &dict)
{
  int blanks=0;
  for (unsigned int i=0; i<in.size();i++){
    if (in[i]=='-'){++blanks;}
  }
  if(blanks<floating.size()){return;}
  char currentInput = in[0];
  in.erase(0,1); //removes first value in string

  if(currentInput=='\0'){
    if(dict.find(current) != dict.end()){
      words.insert(current);
    }
    return;
  }

  else if(currentInput== '-'){
    for (unsigned int i =0; i< floating.size(); i++){
      std::string nCurrent = current + floating[i];
      std::string newFloating = floating;
      newFloating.erase(i,1);
      combinations(in,newFloating, nCurrent, words, dict);
    }
    
    for(int i =0; i<26; i++){
      if(floating.find((char)(i+97)) !=std::string::npos ){continue;}
      //this will add all 26 possible letters to current, then find 
      //possible combinations of the word for each letter
      std::string newCurrent = current+(char)(i+97);
      /*if (floating.find((char)(i+97)) !=std::string::npos){ 
        std::string newFloating = floating;
        newFloating.erase(floating.find((char)(i+97)));
        combinations(in,newFloating, newCurrent, words, dict);
      } */
      combinations(in, floating, newCurrent, words, dict);
    }
  }
  else{
    current += currentInput;
    /*if (floating.find(currentInput) !=std::string::npos){ 
        std::string newFloating = floating;
        newFloating.erase(floating.find(currentInput));
        combinations(in,newFloating, current, words, dict);
      }*/

    combinations(in, floating, current, words, dict);

  }

}

void checkValid(std::string floating, std::set<std::string> &words){
  //char currentInput= floating[0];
  //floating.erase(0,1);
  if (floating == ""){
    return;
  }
  std::set<std::string>::iterator it = words.begin();
  while (it!=words.end()){
    bool* check = new bool[(*it).size()]();
    if(!validHelper(floating, *it, check)){
      words.erase(it++);
      delete [] check;
      continue; 
    }
    ++it;
    delete [] check;
  }
  //checkValid(floating, words, dict);
  //maybe we loop thru all words first, deleting invalid choices, then we perform valid helper to check for duplicates 
}

bool validHelper(std::string floating, std::string word, bool* check){ 
  //checks if letter is in word, and if the letter has been "seen" before.
  char currentInput= floating[0];
  if(currentInput == '\0'){return true;}
  floating.erase(0,1);
  if (word.find(currentInput) == std::string::npos){return false;}
  for (unsigned int i =0; i<word.size();i++){
    if(word[i]==currentInput && check[i]==false){
      check[i]=true;
      return validHelper(floating,word,check);
      break;
    }
  }
  return false;
}
// Define any helper functions here
