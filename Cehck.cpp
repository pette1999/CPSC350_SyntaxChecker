#include <iostream>
#include <fstream>
#include "Check.h"
using namespace std;

Check::Check()
{
    fileName = "test.txt";
    openCount = 0;
    delimiter = "";
    lineNumberCount = 0;

    ifstream inFile(fileName); //read the file
    line = "";

    if (!inFile)
    {
        cout << fileName << " does not exist. " << endl;
        exit(1);
    }
}

Check::Check(string filename)
{
    fileName = filename;
    openCount = 0;
    delimiter = "";
    lineNumberCount = 0;

    ifstream inFile(fileName); //read the file
    line = "";

    if (!inFile)
    {
        cout << fileName << " does not exist. " << endl;
        exit(1);
    }
}

string Check::readFile()
{
    inFile.open(fileName);
    while(getline(inFile, line))
    {
        for(char c : line)
        {
            if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                lineNumberCount++;
            }
        }
    }
    inFile.close();

    lineNumber = new int[lineNumberCount];

    inFile.open(fileName);
    int lineCount = 0;
    //get the number of open brackets
    while(getline(inFile, line))
    {
        lineCount++;
        for(char c : line)
        {
            if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                lineNumber[openCount] = lineCount;
                openCount++;
                delimiter += c;
            }
        }
    }
    cout << delimiter << endl;

    for(int i=0; i<lineNumberCount; ++i)
    {
        cout << lineNumber[i] << endl;
    }

    inFile.close();

    // openDelimiter = new char[openCount];
    // int count = 0;

    // // initilize the array
    // for(int i = 0; i < openCount; ++i)
    // {
    //     openDelimiter[i] = delimiter[i];
    // }

    // inFile.close();
    // return openDelimiter;
    return delimiter;
}

void Check::pairMatch(string arr, int count)
{
    GenStack<char> myStack(openCount);
    int delimiterLeft = openCount;

    for(int i = 0; i < openCount; ++i)
    {
        if (arr[i] == '{' || arr[i] == '(' || arr[i] == '[')
        {
            myStack.push(arr[i]);
        }
        else if (arr[i] == '}' || arr[i] == ')' || arr[i] == ']')
        {
            if(myStack.isEmpty())
            {
                cout << "Missing an open delimiter at LINE " << lineNumber[i] << endl;
                exit(1);
            }

            if(arr[i] == '}' && myStack.peek() == '{')
            {
                myStack.pop();
                delimiterLeft -= 2;
                continue;
            }
            else if (arr[i] == ')' && myStack.peek() == '(')
            {
                myStack.pop();
                delimiterLeft -= 2;
                continue;
            }
            else if (arr[i] == ']' && myStack.peek() == '[')
            {
                myStack.pop();
                delimiterLeft -= 2;
                continue;
            }
            else
            {
                cout << "There is an unmathch at line " << lineNumber[i] << endl;
                exit(1);
            }
        }
    }
    if(myStack.isEmpty())
        cout << "Everything is good" << endl;
    else
        cout << "Missing " << delimiterLeft << " closng delimiters in the end" << endl;
}