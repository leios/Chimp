/*-------------impff.cpp------------------------------------------------------//
*
*              Infinite Monkey Poet File Format (impff)
*
* This file contains information about reading imp files, which can store data
* in an n-dimensional way. I do not guarantee the efficiency of this file 
* format. It will probably be incredibly slow.
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

vector<string> read_file(const char* filepath){
    vector<string> line_comp;
    string lines;
    ifstream impfile;
    impfile.open(filepath);
    if (!impfile){
        cout << "incorrect filepath. Please input the appropriate imp file." 
        << endl;
    }

    while(impfile >> lines){
        line_comp.push_back(lines);
    }

    return line_comp;
    impfile.close();
}

vector<int> find_spacing(vector<string> line_comp){
    vector<int> line_spacing;
    string space = line_comp[0].substr(line_comp[0].find('#')+2, 1);
    int i = atoi(space.c_str());
    line_spacing.push_back(0);
    line_spacing.push_back(i);
    while (i < line_comp.size()){
        space = line_comp[i].substr(line_comp[i].find('#')+2, 1);
        i = i + atoi(space.c_str());
        line_spacing.push_back(i);}
    return line_spacing;
}

vector<string> read_headers(vector<string> line_comp){
    vector<string> headers;
    vector<int> spacing;
    string head;
    spacing = find_spacing(line_comp);
    for ( int j = 0; j < spacing.size() - 1; j++){
        cout << spacing[j] << ", ";
        head = line_comp[spacing[j]].substr(
            line_comp[spacing[j]].find('#')+4,
            line_comp[spacing[j]].size() - line_comp[spacing[j]].find('#')+4);
        headers.push_back(head);}
    cout << endl;
    return headers;
}


void impwrite(string word, int syllables, int type, string rhyme, 
              vector<string> line_comp, vector<string> headers){
    
}


void impread(){
}
