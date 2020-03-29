#include <iostream>
#include <fstream>
#include "GenStack.h"

using namespace std;

class Check
{
public:
    Check();
    Check(string filename);

    ifstream inFile;
    int openCount;
    int lineNumberCount;
    string line;
    string fileName;
    string delimiter;
    int* lineNumber;
    GenStack<char> myStack;//create a stack to store all the characters

    string readFile();
    void pairMatch(string arr, int count);
};