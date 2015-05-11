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

struct word{
    string id,rhyme;
    int type;
};

vector<string> read_file(const char* dic_path);

void imprecord(vector<string> line_comp, const char* dic_path);

vector<int> find_spacing(vector<string> line_comp);

vector<string> read_headers(vector<string> line_comp);

vector<string> impwrite(string word, int syllables, int type, string rhyme, 
              vector<string> line_comp, vector<string> headers,
              vector<int> line_spacing);

vector<string> impremove_header(string rhyme, vector<string> line_comp,
                                vector<string> headers, 
                                vector<int> line_spacing);

vector<string> imptransfer(string rhyme1, string rhyme2,
                           vector<string> line_comp, 
                           vector<string> headers, vector<int> line_spacing);

// Returns a vector of words so we can easily find the rhyme header for the next
// line. It's better this way.
vector<word> impread(string rhyme, int syllables, int type,
                       vector <string> line_comp, vector<string> headers,
                       vector<int> line_spacing);

void bookread(const char* text);

#endif
