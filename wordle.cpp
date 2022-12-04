#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

void dashHelper( // FUNCTION 1
	const std::string& in,
	const std::string& floating,
	const std::set<std::string>& dict,
	// we add 2 more variables below
	set<string>& final,
	int current
	);

void helperFunction( // FUNCTION 2 (MAIN HELPER FUNCTION)
	const std::string& in,
	const std::string& floating,
	const std::set<std::string>& dict,
	// we add 2 more variables below
	set<string>& final,
	int current
	);

std::set<std::string> wordle( // original wordle function
	const std::string& in,
	const std::string& floating,
	const std::set<std::string>& dict)
{
	set<string> allWords;
	helperFunction(in, floating, dict, allWords, 0); // go into the recursive helper
	return allWords;
}


// Define any helper functions here
// dash helper 
void dashHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& final, int current){
	for(char i = 'a'; i <= 'z'; i++){ // now, we take care of the dashes
		string temp2 = floating;
		string temp1 = in;
		temp1[current] = i;
		
		if(string::npos != floating.find(i)){
			temp2.erase(temp2.find(i), 1);
		}
		int curr = current + 1;
		helperFunction(temp1, temp2, dict, final, curr);
	}
}
// main helper function
void helperFunction(const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& final, int current)
{
  int wordLength = in.size();
	
	
	if (current == wordLength){ // if full
		if(floating.size() == 0 && dict.find(in) != dict.end()){ final.insert(in); } // insert in into final
		return; 
	}else{} // actually nothing to be done here

	if (in[current] != '-'){  // if char is a legit letter and not dash 
		int curr = current + 1; // then we just go forward to next 
		helperFunction(in, floating, dict, final, curr); // recursively call function
		return;
	}else{} // actually nothing to be done here

	dashHelper(in, floating, dict, final, current);
}