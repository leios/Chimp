/*-------------imptest.cpp----------------------------------------------------//
*
*              Imp Test
* 
* Purpose: This file is a test for the impff file format for the Chimp project
*
*   Notes: Compile with the following command:
*              g++ impff.cpp imptest.cpp -std=c++11
*
*-----------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "impff.h"

using namespace std;

int main(){
    vector<string> line_comp, headers;
//    vector<int> spacing;
    line_comp = read_file("testdict.imp");
    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }
//    spacing = find_spacing(line_comp);
    headers = read_headers(line_comp);
    cout << "The following are your heading titles:" << endl;
    for ( int i = 0; i < headers.size(); i++){
        cout << headers[i] << endl;
    }
    return 0;
}
