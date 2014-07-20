/*-------------impff.h--------------------------------------------------------//
*
*              Infinite Monkey Poet File Format
*
* This file is meant to be used generally on any file that wishes to use impff
*
*-----------------------------------------------------------------------------*/

#ifndef IMPFF_H
#define IMPFF_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> read_file(const char* filepath);
void call_space();
void read_headers();
void locate_header();
void impwrite();
void impread();

#endif
