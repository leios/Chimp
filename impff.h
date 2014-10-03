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

vector<int> find_spacing(vector<string> line_comp);

vector<string> read_headers(vector<string> line_comp);

void impwrite(string word, int syllables, int type, string rhyme, 
              vector<string> line_comp, vector<string> headers,
              vector<int> line_spacing);

void imprecord(line_comp, dic_path);

void impread();

#endif
