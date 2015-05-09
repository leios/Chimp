/*-------------imptest.cpp----------------------------------------------------//
*
*              Imp Test
* 
* Purpose: This file is a test for the impff file format for the Chimp project
*
*   Notes: Compile with the following command:
*              g++ impff.cpp imptest.cpp -std=c++11
*
*          If you wish to write multiple components to the dictionary, do not
*          forget to find the headers and spacing again!
*              It might be nice to add this functionality to the impff.cpp file.
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

/*----------------------------------------------------------------------------//
* IMPWRITE / IMPRECORD
*-----------------------------------------------------------------------------*/

    // adding in a single syllable word
    vector<string> line_comp, headers;
    vector<int> spacing;
    line_comp = read_file("testdict.imp");
    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }
    spacing = find_spacing(line_comp);

    headers = read_headers(line_comp);
    cout << "The following are your heading titles:" << endl;
    for ( int i = 0; i < headers.size(); i++){
        cout << headers[i] << endl;
    }

    line_comp = impwrite("hay",1,0,"a",line_comp,headers,spacing);
    //imprecord(line_comp, "testdict.imp");

    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }

    cout << endl << endl;

    // adding in a two syllable word 
    spacing = find_spacing(line_comp);
    headers = read_headers(line_comp);
    cout << "The following are your heading titles:" << endl;
    for ( int i = 0; i < headers.size(); i++){
        cout << headers[i] << endl;
    }

    line_comp = impwrite("partay",2,0,"a",line_comp,headers,spacing);
    //imprecord(line_comp, "testdict.imp");

    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }

    cout << endl << endl;


    // adding in a 3 syllable word
    spacing = find_spacing(line_comp);
    headers = read_headers(line_comp);
    cout << "The following are your heading titles:" << endl;
    for ( int i = 0; i < headers.size(); i++){
        cout << headers[i] << endl;
    }

    line_comp = impwrite("parpartay",3,0,"a",line_comp,headers,spacing);
    //imprecord(line_comp, "testdict.imp");

/*----------------------------------------------------------------------------//
* IMPREMOVE_HEADER
*-----------------------------------------------------------------------------*/
/*
    // impremove_header
    cout << "The following is your dictionary:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }

    spacing = find_spacing(line_comp);
    headers = read_headers(line_comp);

    line_comp = impremove_header("a",line_comp,headers,spacing);

    cout << "The following is your dictionary after removal:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }
*/
/*----------------------------------------------------------------------------//
* IMPTRANSFER
*-----------------------------------------------------------------------------*/

    spacing = find_spacing(line_comp);
    headers = read_headers(line_comp);

    line_comp = imptransfer("a","header",line_comp,headers,spacing);

    cout << "The following is your dictionary after transfer:" << endl;
    for( int i = 0; i < line_comp.size(); i++){
        cout << line_comp[i] << endl;
    }

    return 0;
}
