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

// This funtion simply reads the dictionary into a vector
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

// This function finds the spacing between each section of the dictionary
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

// This function finds the headers of each section
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

// This function writes the appropriate word in the appropriate section
// When given the header. This is still a work in progress.
void impwrite(string word, int syllables, int type, string rhyme, 
              vector<string> line_comp, vector<string> headers,
              vector<int> line_spacing){
    // First, we need to find which heading in the dictionary we are under
    int header_num, dictionary_num;

    // Note: Not used to vector.insert command. I am sure there is a more
    // efficient way of doing this
    vector<int>::iterator iter8 = line_comp.begin();

    for (int i = 0; i < headers.size(); i++){
        if (rhyme == headers[i]){
            header_num = i;
            break;
        }
    }
    dictionary_num = line_spacing[header_num];
    
    // Now we need to go into the heading by using the syllables to navigate 
    // down to the appropriate space. If the space is not created yet, 
    // we need to create it! 

    space = line_comp[dictionary_num]
            .substr(line_comp[dictionary_num].find('#')+2, 1);

    j = atoi(space.c_str());
    if (syllables > j){
        // Use vector.insert to insert a line at the appropriate position
        line_comp.insert(iter8 + dictionary_num, syllables - j, "/n")

        // Don't forget to change j!
        // I think I might have miscounted with the inserts below. Check!
        string line = line_comp[dictionary_num];
        line.erase(line.find('#')+2, 1);
        line.insert(line.find('#')+2, syllables);
        line_comp.erase(iter8 + dictionary_num); 
        line_comp.insert(iter8 + dictionary_num, line);
    }
    else{
        continue;
    }

    // Now we need to locate the end of the line and add a comma, followed by
    // the word we are adding and a number for it's type of speech.
    // I think we should start writing the code for the numbers and letters in
    // the first heading.
    string line = line_comp[dictionary_num + syllables];
    int test = line.find_last_of(',');
    if (test < 0){
        line.append(word);
    }
    else{
        line.append(', ' word); 
    }

    // Now to add it back to the line composition!
    line_comp.erase(iter8 + dictionary_num + syllables);
    line_comp.insert(iter8 + dictionary_num + syllables, line);
    
    // let's just return the vector for now.
    return line_comp
}


// This function records line_comp into a new file. I decided to separate this
// from impwrite. I might combine them later.    
void imprecord(line_comp, dic_path){
    // Now we need to write the new contents of line_comp to a file...
    // I think we have dome this before, so let's scrounge something up!
    
      
}


// Note: There is / was a "dictionary" reading option. impread will
// replace this function. Also: the purpose of impread is to find a full list of
// possible words for Chimp to pull from when randomly generating letters or 
// words. The output should be a vector or array of the appropriate length.
void impread(){
}
