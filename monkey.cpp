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
//        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string check, test;
/*    
    for(int i=0; i < window; i++){
        s[i] =  alphabet[rand() % (sizeof(alphabet) -1)];}

    s[window] = 0;
    cout << s << endl;
*/
//I need to pull s[i's] into strings and chack against the dictionary.
//and then move the window forward if it exceeds it's limit
    for(int i = 0; i < 1000; i++){
    wword = alphabet[rand() % (sizeof(alphabet) -1)];
    check.append(wword);
    dict_check(check);    
//    cout << check << endl;
    if(check.size() == window){
        check.erase(0,1);}
    }

        
}

    
