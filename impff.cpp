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
#include "impff.h"

using namespace std;

/*----------------------------------------------------------------------------//
* READ / WRITE
*-----------------------------------------------------------------------------*/

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
void imprecord(vector<string> line_comp, const char* dic_path){
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
        // cout << spacing[j] << ", ";
        head = line_comp[spacing[j]].substr(
            line_comp[spacing[j]].find('#')+4,
            line_comp[spacing[j]].size() - line_comp[spacing[j]].find('#')+4);
        headers.push_back(head);}
    // cout << endl;
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
    int headers_before = headers.size();
    for (int i = 0; i <= headers_before; i++){
        if (i < headers_before){
            if (rhyme == headers[i]){
                header_num = i;
                break;
            }
        }
 
        // Now let's add new headers if the rhyme has never been seen before
        else{
            string new_head = "#,";
            new_head.append(to_string(syllables+1) + "," + rhyme);
            headers.push_back(new_head);
            line_comp.push_back(new_head);
            for (int j = 0; j < syllables; j++){
                line_comp.push_back("EMPTY");
            }
            header_num = i;
        }
    }

    // dictionary_num is the position of the chosen header in line_comp
    dictionary_num = line_spacing[header_num];
    
    // Now we need to go into the heading by using the syllables to navigate 
    // down to the appropriate space. If the space is not created yet, 
    // we need to create it! 

    // This should find the spacing in the header and set it as "j"
    // Why "j"? Heck if I know, I couldn't think of another variable. 
    string space = line_comp[dictionary_num]
                   .substr(line_comp[dictionary_num].find('#')+2, 1);
    int j = (atoi(space.c_str()) - 1);

    if (syllables > j){
        // Use vector.insert to insert a line at the appropriate position
        line_comp.insert(line_comp.begin() + dictionary_num + j + 1, 
                         syllables - j,"EMPTY");

        // Don't forget to change the number of syllables in the header!
        // I think I might have miscounted with the inserts below. Check!
        string line = line_comp[dictionary_num];
        line_comp[dictionary_num].erase(line.find('#')+2, 1);
        line_comp[dictionary_num].insert(line.find('#')+2,
                                         to_string(syllables + 1));
    }


    // Now we need to locate the end of the line and add a comma, followed by
    // the word we are adding and a number for it's type of speech.
    // I think we should start writing the code for the numbers and letters in
    // the first heading.
    string line = line_comp[dictionary_num + syllables];

    int test = line.find_last_of(',');

    if (test < 0){
        line = word + "+" + to_string(type) + ",";
    }
    else{
        line.append(word + "+" + to_string(type) + ","); 
    }

    // Now to add it back to the line composition!

    line_comp.erase(line_comp.begin() + dictionary_num + syllables);
    line_comp.insert(line_comp.begin() + dictionary_num + syllables, line);

    
    // let's just return the vector for now.
    return line_comp;
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
    line_comp.erase(line_comp.begin() + line_num, 
                    line_comp.begin() + line_num + j);

    return line_comp;
}

// If you need to transfer the contents of one header to another
// NOTE: Tranferring 1 onto 2
//       This follows logic of impwrite and impremove header, check there for
//       comments!
vector<string> imptransfer(string rhyme1, string rhyme2,
                           vector<string> line_comp, 
                           vector<string> headers, vector<int> line_spacing){

    // I think the best bet here is to use impwrite to write each syllable line
    // to the appropriate line in the header we want to transfer to and then 
    // use impremove_header to remove the offensive header. 

    // Finding information on rhyme1
    int header1_num, line1_num;
    for (int i = 0; i <= headers.size(); i++){
        if (rhyme1 == headers[i]){
            header1_num = i;
            break;
        }
    }

    line1_num = line_spacing[header1_num];

    string space1 = line_comp[line1_num]
                    .substr(line_comp[line1_num].find('#')+2, 1);

    int j1 = atoi(space1.c_str());

    // Finding information on rhyme2
    int header2_num, line2_num;
    for (int i = 0; i <= headers.size(); i++){
        if (rhyme2 == headers[i]){
            header2_num = i;
            break;
        }
    }

    line2_num = line_spacing[header2_num];

    string space2 = line_comp[line2_num]
                    .substr(line_comp[line2_num].find('#')+2, 1);

    int j2 = atoi(space2.c_str());

    // We need to add extra rows if j1 > j2
    if (j1 > j2){
        int jdiff = j1 - j2;
        // Check to make sure this is inserting at the right position.
        line_comp.insert(line_comp.begin() + line2_num + j2 - 1, jdiff,
                         "EMPTY");
    }

    // Now, we just need to copy the contents of rhyme1 to rhyme2...
    // again, check these to make sure it is aligned properly.
    for (int i = 0; i < (j1 - 1); i++){
        line_comp[line2_num + 1 + i].append("," + line_comp[line1_num + 1 + i]);
    }

   line_comp = impremove_header(rhyme1,line_comp,headers,line_spacing); 


return line_comp;
}


// Note: There is / was a "dictionary" reading option. impread will
// replace this function. Also: the purpose of impread is to find a full list of
// possible words for Chimp to pull from when randomly generating letters or 
// words. The output should be a vector or array of the appropriate length.
vector<word> impread(string rhyme, int syllables, int type,
                       vector <string> line_comp, vector<string> headers,
                       vector<int> line_spacing){

    vector<word> possibilities;
    word element;
    // Following the logic of impwrite, we need to find the line number of the
    // rhyme for the word. Note that not all words will have a rhyme.
    if (rhyme != "NONE"){

        int header_num;
        for (int i = 0; i <= headers.size(); i++){
            if (rhyme == headers[i]){
                header_num = i;
                break;
            }
        }

        int line_num = line_spacing[header_num];

        // Now we need to sort by syllables and type. Note that type will be
        // (-1) if no type is specified.

        string line = line_comp[line_num + syllables];
        int comma,plus;
        while (line.size() > 1){
            element.rhyme = rhyme;

            comma = line.find(",");
            plus = line.find("+");
            element.id = line.substr(0,plus);
            element.type = atoi((line.substr(plus + 1,comma)).c_str());


            // Filter by type
            if (type < 0){
                possibilities.push_back(element);
            }
            else{
                if (element.type == type){
                    possibilities.push_back(element);
                }
            }

            line = line.substr(comma+1,line.size() - comma);
        }

    }

    // Now we need to go through the rest of line_comp (no rhyme).
    else{

        // We need to go through and create a vector of lines, each with the
        // appropriate number of syllables. Note that any number of syllables
        // under the syllable number required is also possible.

        vector <string> lines;
        int count = 1,ieff = 1;
        for (int i = 0; i < line_comp.size(); i++){

            if (ieff <= syllables){
                lines.push_back(line_comp[i]);
            }

            ieff += 1;

            if (ieff > line_spacing[count]){
                ieff -= line_spacing[count];
                count += 1;
            }
        }


        int comma,plus;
        for (int i = 0; i < lines.size(); i++){

            while (lines[i].size() > 1){
                element.rhyme = rhyme;

                comma = lines[i].find(",");
                plus = lines[i].find("+");
                element.id = lines[i].substr(0,plus);
                element.type = atoi((lines[i].substr(plus + 1,comma)).c_str());


                // Filter by type
                if (type < 0){
                    possibilities.push_back(element);
                }
                else{
                    if (element.type == type){
                        possibilities.push_back(element);
                    }
                }

                lines[i] = lines[i].substr(comma+1,lines[i].size() - comma);
            }

        }
    }

    return possibilities;
}
