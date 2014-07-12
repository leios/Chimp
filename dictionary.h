/*-------------dictionary.h---------------------------------------------------//
*
*              Charles the Infinite Monkey Poet (chimp)
*
* This is the header file to the dicitonary.cpp to link it to the typewriter
* the purpose of this file is to 
* 
* Peace out!
*-----------------------------------------------------------------------------*/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

using namespace std;

void read_dict(int window, vector<string> possibilities, int i);
void scan_possibilities(vector<string> possibilities, string chimp_word, int i);
void window_check(int window);

#endif
