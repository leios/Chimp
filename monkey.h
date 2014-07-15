/*-------------monkey.h-------------------------------------------------------
*
*              Charles, The Infinite Monkey Poet (chimp)
*
* This is meant to pass functions between the monkey.cpp and typewriter.cpp
*
* Nothing fancy
*
*-----------------------------------------------------------------------------*/

#ifndef MONKEY_H
#define MONKEY_H

#include <string>

using namespace std;

void init_rand();
void gen_rand(int window, char *s);

#endif
