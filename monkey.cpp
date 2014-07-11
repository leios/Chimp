/*-------------monkey.cpp-------------------------------------------------------
*
*              Charles, The Infinite Monkey Poet (chimp)
*
* This file is meant to be the random letter generator for Charles. 
*
* But in the end, aren't we all just monkeys typing on the keyboard of life?
*
*-----------------------------------------------------------------------------*/

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

double gen_rand(int window){
srand((unsigned)time(0));
for(unsigned i=0; i<window; ++i){
cout << rand() << endl;}}
