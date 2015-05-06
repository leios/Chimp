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
#include <iterator>

using namespace std;

// This funtion simply reads the dictionary into a vector
vector<string> read_file(const char* dic_path){
    vector<string> line_comp;
    string lines;
    ifstream impfile;
    impfile.open(dic_path);
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

// This function will write line_comp to your dictionary file
void write_file(vector<string> line_comp, const char* dic_path){
    ofstream impfile;
    impfile.open(dic_path);
    for (int i = 0; i < line_comp.size(); i++){
        impfile << line_comp[i] << endl;
    } 

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
// Note: I may need to rewrite this to search each heder for the rhyming word. 
//       More than that, I might want to read in words that do not necessarily
//       have a rhyme (i.e. reading a book).
vector<string> impwrite(string word, int syllables, int type, string rhyme, 
              vector<string> line_comp, vector<string> headers,
              vector<int> line_spacing){

    // First, we need to find which heading in the dictionary the word is under
    int header_num, dictionary_num;

    // Note: Not used to vector.insert command. I am sure there is a more
    // efficient way of doing this
    // Note: the header's vector should be just the rhymes. 
    vector<string>::iterator iter8 = line_comp.begin();
    for (int i = 0; i <= headers.size(); i++){
        if (rhyme == headers[i]){
            header_num = i;
            break;
        }
 
        // Now let's add new headers if the rhyme has never been seen before
        if (i == headers.size()){
            string new_head;
            new_head.append("#," + to_string(syllables) + "," + rhyme);
            headers.push_back(rhyme);
            line_comp.push_back(new_head);
            for (int j = 0; j < syllables; j++){
                line_comp.push_back("\n");
            }
            header_num = headers.size() + 1;
        }
    }
    dictionary_num = line_spacing[header_num];
    
    // Now we need to go into the heading by using the syllables to navigate 
    // down to the appropriate space. If the space is not created yet, 
    // we need to create it! 

    // This should find the spacing in the header and set it as "j"
    // why "j"? Heck if I know, I couldn't think of another variable. 
    string space = line_comp[dictionary_num]
                   .substr(line_comp[dictionary_num].find('#')+2, 1);
    int j = atoi(space.c_str());

    if (syllables > j){
        // Use vector.insert to insert a line at the appropriate position
        line_comp.insert(iter8 + dictionary_num, syllables - j, "\n");

        // Don't forget to change the number of syllables in the header!
        // I think I might have miscounted with the inserts below. Check!
        string line = line_comp[dictionary_num];
        line_comp[dictionary_num].erase(line.find('#')+2, 1);
        line_comp[dictionary_num].insert(line.find('#')+2,to_string(syllables));
        line_comp.erase(iter8 + dictionary_num); 
        line_comp.insert(iter8 + dictionary_num, line);
    }

    // Now we need to locate the end of the line and add a comma, followed by
    // the word we are adding and a number for it's type of speech.
    // I think we should start writing the code for the numbers and letters in
    // the first heading.
    string line = line_comp[dictionary_num + syllables];
    int test = line.find_last_of(',');
    if (test < 0){
        line.append(word + "+" + to_string(type));
    }
    else{
        line.append(", " + word + "+" + to_string(type)); 
    }

    // Now to add it back to the line composition!
    line_comp.erase(iter8 + dictionary_num + syllables);
    line_comp.insert(iter8 + dictionary_num + syllables, line);
    
    // let's just return the vector for now.
    return line_comp;
}

/*
// This function records line_comp into a new file. I decided to separate this
// from impwrite. I might combine them later.    
vector<string> imprecord(vector<int> line_comp, const char* dic_path){

    // Now we need to write the new contents of line_comp to a file...
    // I think we have done this before, so let's scrounge something up!
    ofstream dic;
    dic.open(dic_path);

    // Now let's copy the contents of line_comp to the dic
    copy(line_comp.begin(), line_comp.end(), 
         ostream_iterator<string>(dic, "\n"));
      
}


// If you end up making a mistake and need to remove a header
vector<string> impremove_header(string rhyme, vector<string> line_comp,
                                vector<string> headers, 
                                vector<int> line_spacing){

    // This should be easy. A search and destroy mission.
    // We find the heading and remove it along with all the lines following
    // within syllable range.
    int header_num;
    for (int i = 0; i <= headers.size(); i++){
        if (rhyme == headers[i]){
            header_num = i;
            break;
        }
    }

    int line_num = line_spacing[header_num];

    // find the space each header takes up
    string space = line_comp[line_num]
                   .substr(line_comp[line_num].find('#')+2, 1);

    // I couldn't think of a unique variable name for the number of syllables to
    // remove... so let's just use "j" for now. Deal with it.
    int j = atoi(space.c_str());

    // Now we just have to remove the appropriate components from the vector
    // I think I might be off by one. Check this.
    line_comp.erase(line_comp.begin() + header_num - 1, 
                    line_comp.begin() + header_num + j - 1);
return line_comp;
}

// If you need to transfer the contents of one header to another
vector<string> imptransfer(string rhyme1, string rhyme2,
                           vector<string> line_comp, 
                           vector<string> headers, vector<int> line_spacing){

    // I think the best bet here is to use impwrite to write each syllable line
    // to the appropriate line in the header we want to transfer to and then 
    // use impremove to remove the offensive header. 

return line_comp;
}

// Note: There is / was a "dictionary" reading option. impread will
// replace this function. Also: the purpose of impread is to find a full list of
// possible words for Chimp to pull from when randomly generating letters or 
// words. The output should be a vector or array of the appropriate length.
void impread(){
}
*/
