// Author: Bashar Al-Saify

// Algorithm
// -----------------------------------------------
// 1. Read the number in the first line.
// 2. Store the first two lines in separate vectors.
// 3. Before starting, we make sure the vectors has same length.
// 4. Rename placeholders in vector B so they are unique from vector A.
// 5. Iterate through and resolve conflicts using Rock vs Clay logic.
// 6. Print the result (replacing any leftover placeholders with "a").
// -------------------------------------------------

// Time complexity
// O(n²)

// Command to run the program
// ----------------------------------
// g++ main.cc < example_file.txt

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool checkPlaceholder(const string &word) {
  if (word.length() > 0 && word[0] == '<')
    return true;
  else
    return false;
}

// Helper function to replace ALL occurrences of 'oldVal' with 'newVal' in a
// vector
void updateVector(vector<string> &words, const string &oldVal,
                  const string &newVal) {
  for (int i = 0; i < words.size(); i++) {
    if (words[i] == oldVal) {
      words[i] = newVal;
    }
  }
}

void algorithm() {
  string lineA;
  string lineB;

  if (!getline(cin, lineA) || !getline(cin, lineB))
    return;

  // Split lines into vectors of words
  vector<string> vecA;
  vector<string> vecB;
  stringstream ssA(lineA), ssB(lineB);
  string word;

  while (ssA >> word) {
    vecA.push_back(word);
  }

  while (ssB >> word) {
    vecB.push_back(word);
  }

  // Check length
  if (vecA.size() != vecB.size()) {
    cout << "-" << endl;
    return;
  }

  // Rename placeholders in vecB so they don't accidentally match vecA.
  for (int i = 0; i < vecB.size(); i++) {
    if (checkPlaceholder(vecB[i])) {
      vecB[i] += "_2";
    }
  }

  for (int i = 0; i < vecA.size(); i++) {
    string wA = vecA[i];
    string wB = vecB[i];

    // If words are already identical, no work needed
    if (wA == wB)
      continue;

    bool aIsPh = checkPlaceholder(wA);
    bool bIsPh = checkPlaceholder(wB);

    // Word vs Word (Different words) -> Impossible
    if (!aIsPh && !bIsPh) {
      cout << "-" << endl;
      return;
    }

    string oldVal, newVal;

    if (aIsPh && !bIsPh) {
      // Case: <placeholder> vs Word -> Placeholder must become Word
      oldVal = wA;
      newVal = wB;
    } else if (!aIsPh && bIsPh) {
      // Case: Word vs <placeholder> -> Placeholder must become Word
      oldVal = wB;
      newVal = wA;
    } else {
      // Case: <placeholder> vs <placeholder> -> Merge them
      oldVal = wA;
      newVal = wB;
    }

    // Update both pattern with the new values
    updateVector(vecA, oldVal, newVal);
    updateVector(vecB, oldVal, newVal);
  }

  for (int i = 0; i < vecA.size(); i++) {
    if (checkPlaceholder(vecA[i])) {
      cout << "a";
    } else {
      cout << vecA[i];
    }

    cout << (i == vecA.size() - 1 ? "" : " ");
  }
  cout << endl;
}

int main() {

  int counter;
  if (cin >> counter) {
    string line;
    getline(cin, line);

    while (counter--) {
      algorithm();
    }
  }
  return 0;
}