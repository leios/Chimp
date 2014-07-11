/*-------------monkey.cpp-------------------------------------------------------
*
*              Charles, The Infinite Monkey Poet (chimp)
*
* This file is meant to be the random letter generator for Charles. 
*
* But in the end, aren't we all just monkeys typing on the keyboard of life?
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

void init_rand(){srand((unsigned)time(0));}

void gen_rand(int window, char *s){
    const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    for(int i=0; i < window; i++){
        s[i] =  alphabet[rand() % (sizeof(alphabet) -1)];}

    s[window] = 0;
    cout << s << endl;
}

    
