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
    string line;
    string fileName;
    char* openDelimiter;
    GenStack<char> myStack;//create a stack to store all the characters

    char* readFile();
    void pairMatch(char* arr, int count);
};