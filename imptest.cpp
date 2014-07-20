#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "impff.h"

using namespace std;

int main(){
    vector<string> line_comp;
    line_comp = read_file("testdict.imp");
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;}
}
