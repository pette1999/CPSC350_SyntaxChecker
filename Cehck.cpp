#include <iostream>
#include <fstream>
#include "Check.h"
using namespace std;

Check::Check()
{
    fileName = "test.txt"; //default text file 
    openCount = 0;
    delimiter = "";
    lineNumberCount = 0;
    hasFile = true;

    ifstream inFile(fileName); //read the file
    line = "";

    if (!inFile)
    {
        hasFile = false;
        cout << fileName << " does not exist. " << endl; //if the file does not exist, set hasFile to false
    }
}

Check::Check(string filename)
{
    fileName = filename;
    openCount = 0;
    delimiter = "";
    lineNumberCount = 0;
    hasFile = true;

    ifstream inFile(fileName); //read the file
    line = "";

    if (!inFile)
    {
        hasFile = false;
        cout << fileName << " does not exist. " << endl;
    }
}

string Check::readFile(string filename)
{
    fileName = filename;
    inFile.open(fileName);
    while(getline(inFile, line))
    {
        for(char c : line)
        {
            if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                lineNumberCount++; //coutn the delimider
            }
        }
    }
    inFile.close();

    lineNumber = new int[lineNumberCount]; //create am array to store line number

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
            myStack.push(arr[i]); //we push all the open delimider to the stack
        }
        else if (arr[i] == '}' || arr[i] == ')' || arr[i] == ']')
        {
            if(myStack.isEmpty()) //check if the stack is empty
            {
                char t = ' ';
                if(arr[i] == '}')
                    t = '{';
                else if(arr[i] == ')')
                    t = '(';
                else if(arr[i] == ']')
                    t = '[';
                cout << "Missing an open delimiter " << t << " at LINE " << lineNumber[i] << endl;
                break;
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
                char t = ' ';
                if(myStack.peek() == '{')
                    t = '}';
                else if(myStack.peek() == '(')
                    t = ')';
                else if(myStack.peek() == '[')
                    t = ']';
                cout << "There is an unmathch at line " << lineNumber[i] << endl;
                cout << "Should be " << t << " instead of " << arr[i] << endl;
                break;
            }
        }
    }
    if(myStack.isEmpty()) //if the stack is empty in teh end, then everything is good
        cout << "Everything is good" << endl;
    else
        cout << "Missing " << delimiterLeft << " closng delimiters in the end" << endl;
}

bool Check::checkHasFile()
{
    return hasFile;
}