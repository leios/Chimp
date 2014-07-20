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


void call_space(){
}


void read_headers(){
}


void locate_header(){
}


void impwrite(){
}


void impread(){
}
