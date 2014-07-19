/*-------------monkey.cpp-------------------------------------------------------
*
*              Charles, The Infinite Monkey Poet (chimp)
*
* This file is meant to be the random letter generator for Charles. 
*
* But in the end, aren't we all just monkeys typing on the keyboard of life?
*
*-----------------------------------------------------------------------------*/

#include "dictionary.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void init_rand(){srand((unsigned)time(0));}

void gen_rand(int window, string wword){
    const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz";
    string check, test;

    for(int i = 0; i < 10000; i++){
    wword = alphabet[rand() % (sizeof(alphabet) -1)];
    check.append(wword);
    dict_check(check);    
    if(check.size() == window){
        check.erase(0,1);}
    }
}

