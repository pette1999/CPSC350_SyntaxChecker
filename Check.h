#include <iostream>
#include <fstream>
#include "GenStack.h"

using namespace std;

class Check
{
public:
    Check(); //constrctor
    Check(string filename); //overloaded constructor

    ifstream inFile; //read the input file
    int openCount; //count the open delimiter
    int lineNumberCount; // count the line number
    bool hasFile; //check if the file exists
    string line;
    string fileName;
    string delimiter;
    int* lineNumber; //an array to store the line number for each delimider
    GenStack<char> myStack; //create a stack to store all the characters

    bool inQuote;
    string singleQuote;

    string readFile(string filename); //a method to read the file
    void pairMatch(string arr, int count); //method to pair the delimiders
    bool checkHasFile(); 
};