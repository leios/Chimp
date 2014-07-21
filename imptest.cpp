#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "impff.h"

using namespace std;

int main(){
    vector<string> line_comp, headers;
    line_comp = read_file("testdict.imp");
    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;}
    headers = read_headers(line_comp);
    cout << "The following are your heading titles:" << endl;
    for ( int i = 0; i < headers.size(); i++){
        cout << headers[i] << endl;}

}
