// Author: Bashar Al-Saify

// Algorithm
// -----------------------------------------------
//  1. Read the words until empty line.
//  2. Store the words in dictionary (map).
//  3. Continue reading where we stoped earlier.
//  4. Look up the words in the dictionary (map).
//  5. If word found -> print the the value.
//  6. If not found -> print "eh".
// ------------------------------------------------

// Command to run the program
// ----------------------------------
// g++ main.cc < example_file.txt

#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

string line;
string key;
string value;
map<string, string> dictionary;

int main() {

  // Read the words and create dictionary -> Stop if empty line reach.
  while (getline(cin, line) && !line.empty()) {
    stringstream ss(line);
    ss >> value >> key;
    dictionary[key] = value;
  }

  // Continue reading from where we stoped (empty line) -> Lookup the words and
  // print if found
  while (getline(cin, line)) {
    auto value = dictionary.find(line);
    if (value != dictionary.end()) {
      cout << value->second << "\n";
    } else {
      cout << "eh" << "\n";
    }
  }

  return 0;
}