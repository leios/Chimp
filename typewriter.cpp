/*-------------typewriter.cpp-------------------------------------------------//
*
*              Charles the Infinite Monkey Poet (chimp)
*
* This is the infinite letter generator for chimp. This should act essentially
* as the code's driver for later additions. I will need a dictionary and a
* monkey, but I think those should be the only other files I will need
*
* NOTE: I would like to add synching functions and commandline parsing. I am 
* unsure of whether I should use BOOST for the latter or not.
* 
* Peace out!
*-----------------------------------------------------------------------------*/
#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>

using namespace std;

int main()
{
  double x_rand;
  int bin_size, i, count;
  ifstream input("wordsEn.txt");
  vector<string> words;
  string inword;
  while (std::getline(input,inword))
  {
      words.push_back(inword);
  }

  for (int i = 0; i<=10 ; i++)
  {
    int num = rand() % words.size();  
    if (num<words.size()){
     std::cout << words[num] << endl;
  }
} 
}
