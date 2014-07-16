/*-------------typewriter.cpp-------------------------------------------------//
*
*              Charles the Infinite Monkey Poet (chimp)
*
* This is the infinite letter generator for chimp. This should act essentially
* as the code's driver for later additions. I will need a dictionary and a
* monkey, but I think those should be the only other files I will need
*
* NOTE: I would like to add synching functions and commandline parsing. I am 
* unsure of whether I should use BOOST for the latter or not.
* 
* Peace out!
*-----------------------------------------------------------------------------*/

#include "dictionary.h"
#include "monkey.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){

int window;
string wword;

/*
if(argc > 1){
    window = atoi( argv[1] );}
*/

init_rand();
window = window_check(window);
cout << window << endl;
gen_rand(window, wword);

return 0;
}
