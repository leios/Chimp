/*-------------dictionary.cpp-------------------------------------------------//
*
*              Charles the Infinite Monkey Poet (chimp)
*
* The purpose of this file is to parse the output of the typwriter into 
* appropriate words based on another file, "dictionary.dat." I have yet to
* determine the optimum format for this file.
*
* I am working on it!
*
*-----------------------------------------------------------------------------*/


#include "dictionary.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void read_dict(int window, vector<string> possibilities, int i){
    ifstream dictionary;
    dictionary.open("dictionary.dat");
    while(i != dictionary.eof()){
        std::string words;
        getline(dictionary,words);
        if (words.size() <= window){
            possibilities.push_back(words);}}
}
            
        
//void window_check(int window, char *s){
    


