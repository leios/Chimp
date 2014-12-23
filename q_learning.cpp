/*-------------q_learning.cpp-------------------------------------------------//
*
*              Infinite Monkey Poet File Format Test
*
* Purpose: To read in a work of literature, write a dictionary based on that 
*          work, and recreate it with a q-learning algorithm. Why Q-learning?
*          Why not?
*
* To get this code to function appropriately, you will need another file named
* "quote" with some setnence or something that you want to read in. 
*
* The code will output two files, "phrasing.dat" and "out.dat." The former is
* simply a list of the chosen words so you can watch your computer learn. The
* latter is an output of all the Q-matrices... again so you can watch and learn!
*
* Note: To get gnuplot to plot out nice grids, use to following command:
*           set dgrid3d 30,30
*       before:
*           splot "out.dat" u 1:2:3 i 0 w l
*
*-----------------------------------------------------------------------------*/

#include "impff.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>

/*----------------------------------------------------------------------------//
* STRUCTURES AND FUNCTIONS
*-----------------------------------------------------------------------------*/

using namespace std;

struct word_int{
    string word;
    int syl;
};

double update_quality(double current_quality, double max_quality, double gamma, 
                      int reward, double alpha);
double find_max_quality(vector<double> options);
double find_min_quality(vector<double> options);
int make_selection(vector<double> options);


/*----------------------------------------------------------------------------//
* MAIN
* (I apologize, it's super messy)
*-----------------------------------------------------------------------------*/

int main(){

    vector<string>             lines, words, list, l_list;
    vector<int>                syllables;
    string                     line, word;
    int                        number, selection, max_syl = 0;
    ifstream                   book;
    double                     gamma = 0.9, alpha = 0.2, max_quality;
    vector<double>             options;

    book.open("quote");
  
    // First an error message. Why not?
    if (!book){
        cout << "incorrect filepath. Please input the appropriate book!" 
        << endl;
    }

    // Now we need to read in the book. This will read each word as it's own
    // component in the words vector.
    while (book >> line){
        words.push_back(line);
        list.push_back(line);
    }

    words.push_back("NULL");
    list.push_back("NULL");

    // Find number of syllables in each word
    for (int i = 0; i < words.size(); i++){
        if (i != words.size() - 1){
            cout << "how many syllables are in " << words[i] << "?" << endl;
            cin >> number;
            syllables.push_back(number);
        }
        if (i == words.size() - 1){syllables.push_back(0);}
    }

    cout << "This is what you have input:" << endl;

    for (int i = 0; i < words.size(); i++){
        cout << words[i] << '\t' << syllables[i] << endl;
    }

    // Let's go ahead and count the number of syllables
    for (int i = 0; i < syllables.size(); i++){
        max_syl = max_syl + syllables[i];
    }

    cout << "The number of syllables in this phrase is " << max_syl << endl;
    cout << "The following is your array:" << endl;

    // Now we need to return both the words and syllables, so we need a struct
    int count = 0, delay = 0;
    word_int array[max_syl];
    for (int i = 0; i < max_syl; i++){
        if (count - 1 <= 0){
            array[i].word = words[i-delay];
            array[i].syl = syllables[i-delay];
            count = syllables[i-delay];
            cout << array[i].word << '\t' << array[i].syl << endl;
        }
        else{
            array[i].word = "NULL";
            array[i].syl = 0;
            cout << array[i].word << '\t' << array[i].syl << endl;
            count = count - 1;
            delay = delay + 1;
        }

    }


    cout << "Now let's remove repeating words from your action list." << endl;
    int i = 0, ii = 0;

    // Let's remove repeating words.
    while (i < words.size() - 1){
        i++;
        while (ii < words.size()){
            if (i != ii){
                if (words[i] == words[ii]){
                    cout << "found one! It's " << words[ii] << "!" << endl;
                    syllables.erase(syllables.begin() + ii);
                    words.erase(words.begin() + ii);
                }
            }
            ii++;
        }
        ii = 0;
    }

    cout << "Here is your list of 'actions':" << endl;

    for (int i = 0; i < words.size(); i++){
    cout << words[i] << endl;
    }

    cout << "Now to create our rewards table..." << endl;

    // Good. Now we have an array that has all of our words and syllables in it.
    // Now we need to actually implement q-learning.

    // First, we need to define our rewards. The state in this case will be our
    // syllables. The action will be our word choice. 

    int reward[max_syl][words.size()];
    delay = 0;
    for (int i = 0; i < max_syl; i++){
        if (array[i].syl == 0){
            for (int ii = 0; ii < words.size(); ii++){
                if (ii != words.size() - 1){
                    reward[i][ii] = -1;
                }
                if (ii == words.size() - 1){
                    reward[i][ii] = 10;
                }
            }
        delay++;
        }
        else{
            for (int ii = 0; ii < words.size(); ii++){
                if (array[i].word == words[ii]){
                    reward[i][ii] = 10;
                }
                else{
                    reward[i][ii] = -1;
                }
                if (i >= 1){
                    if (array[i- 1 - delay].word == words[ii]){
                        reward[i][ii] = -10;
                        delay = 0;
                    }
                }
            }
        }
    }

    cout << "... and here it is!" << endl;
    for (int i = 0; i < max_syl; i++){
        for(int ii =0; ii < words.size(); ii++){
            cout << reward[i][ii] << '\t';
        }
        cout << endl;
    }
   

    // Now, we have a reward table. Q learning should be a simple iterative 
    // process from here. We need to create an episode, where we go through all
    // of the syllables in the phrase. First, we randomly select actions and
    // determine the quality of each action based on that random selection. We
    // Then update the conditional probability table until the only relevant 
    // choices are the ones in the phrase. 

    // First, let's define our quality table and a few other variables
    double quality[max_syl][words.size()];

    for (int i = 0; i <= list.size(); i++){
        l_list.push_back("NULL_WORD");
        cout << i << endl;
    } 

    cout << "filled initial list with null words" << endl;

    for (int i = 0; i < words.size(); i++){
        options.push_back(0);
        cout << i << endl;
    }

    cout << "filled set all initial quality options to 0" << endl;


    // Now let's make that quality array all 0's to start with
    for (int i = 0; i < max_syl; i++){
        for (int ii = 0; ii < words.size(); ii++){
            quality[i][ii] = 0;
        }
    }

    cout << "Set all quality to 0" << endl;

    cout << "here is your current quality matrix:" << endl;

    for (int i = 0; i < max_syl; i++){
        for(int ii =0; ii < words.size(); ii++){
            cout << quality[i][ii] << '\t';
        }
        cout << endl;
    }


    // let's open a file  or two for writing...
    ofstream output, output_words;
    output.open("out.dat");
    output_words.open("phrasing.dat");
    
    // Alright. Now for the learning...
    for (int k = 0; k < 100; k++){
        for (int i = 0; i < max_syl; i++){
            for (int ii = 0; ii < words.size(); ii++){
                options[ii] = quality[i][ii];
            }
        
            selection = make_selection(options);
            max_quality = find_max_quality(options);
            quality[i][selection] = update_quality(quality[i][selection],
                                                   max_quality, gamma,
                                                   reward[i][selection], alpha);
            l_list[i] = words[selection];
        }
        

        cout << "The updated quality matrix is:" << endl;

        for (int j = 0; j < max_syl; j++){
            for(int jj =0; jj < words.size(); jj++){
                cout << quality[j][jj] << '\t';
            }
            cout << endl;
        }


        // Now let's write this to a file for later...
        for (int j = 0; j < max_syl; j++){
            for(int jj =0; jj < words.size(); jj++){
                output << j << '\t' << jj << '\t' << quality[j][jj] << '\t'
                       << endl;
            }

        }
        output << endl << endl;
        cout << k << endl;

        for (int j = 0; j < l_list.size(); j++){
            output_words << l_list[j] << '\t';
        }
        output_words << endl;

    }
    

    output.close();

}

/*----------------------------------------------------------------------------//
* SUBROUTINES
*-----------------------------------------------------------------------------*/

// Our function to update the quality. It reads in the action and 
double update_quality(double current_quality, double max_quality, double gamma, 
                      int reward, double alpha){
    
    double quality;
    quality = current_quality + alpha * ( reward + gamma * max_quality 
                                       - current_quality );
    return quality;
}

// Function to find the maximum quality
double find_max_quality(vector<double> options){

    double max_quality;
    for (int i = 0; i < options.size(); i++){
        if (i == 0){
            max_quality = options[i];
        }
        else{
            if (options[i] > max_quality){
                max_quality = options[i];
            }
        }
    }

    return max_quality;
}

// Function to find the minimum quality
double find_min_quality(vector<double> options){

    double min_quality;
    for (int i = 0; i < options.size(); i++){
        if (i == 0){
            min_quality = options[i];
        }
        else{
            if (options[i] < min_quality){
                min_quality = options[i];
            }
        }
    }

    return min_quality;
}


// Function to determine next step.
// Uses a Boltzmann action selection routine.
int make_selection(vector<double> options){
    double total_quality = 0, min_quality, total_qual_inv;
    int choice = 0;
    double beta = 1;
    vector<double> bins;

    // sum all qualities via boltzmann thingy
    for (int i = 0; i < options.size(); i++){
        total_quality = total_quality + exp((beta * options[i]));
    }
    total_qual_inv = (1 / total_quality);

    for (int i = 0; i < options.size(); i++){
        if (i == 0){ 
            bins.push_back(exp((beta * options[i])) * total_qual_inv);
        }
        if (i > 0){
            bins.push_back(bins[i-1] + 
                           (exp((beta * options[i])) * total_qual_inv));
        }
    }

    double random_number = ((double) rand() / (RAND_MAX));    
    

    for (int i = 0; i < options.size(); i++){
        if (i < 1){
            if ((random_number >= 0) &&
                (random_number < bins[i])){
                choice = i;
            }
        }
        if (i >=1){
            if ((random_number >= bins[i-1]) &&
                (random_number < bins[i])){
                choice = i;
            }
        }
    }

    return choice;
}
