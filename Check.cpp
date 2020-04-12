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
    inQuote = false;
    singleQuote = "'";

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
    inQuote = false;
    singleQuote = "'";

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
    int double_Quote_count = 0;
    int single_Quite_count = 0;
    while(getline(inFile, line))
    {
        for(char c : line)
        {
            if(c == '"')
            {
                double_Quote_count++;
                cout << double_Quote_count << endl;
                if(double_Quote_count % 2 == 0 && single_Quite_count % 2 == 0)
                {
                    inQuote = false;
                    cout << double_Quote_count << endl;
                }
                else
                {
                    inQuote = true;
                }
            }
            else if(c == singleQuote[0])
            {
                single_Quite_count++;
                if(double_Quote_count % 2 == 0 && single_Quite_count % 2 == 0)
                {
                    inQuote = false;
                }
                else
                {
                    inQuote = true;
                }
            }
            else if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                if(inQuote == false)
                {
                    lineNumberCount++; //coutn the delimider
                }
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
            if(c == '"')
            {
                double_Quote_count++;
                cout << double_Quote_count << endl;
                if(double_Quote_count % 2 == 0 && single_Quite_count % 2 == 0)
                {
                    inQuote = false;
                    cout << double_Quote_count << endl;
                }
                else
                {
                    inQuote = true;
                }
            }
            else if(c == singleQuote[0])
            {
                single_Quite_count++;
                if(double_Quote_count % 2 == 0 && single_Quite_count % 2 == 0)
                {
                    inQuote = false;
                }
                else
                {
                    inQuote = true;
                }
            }
            else 
                if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                if(inQuote == false)
                {
                    lineNumber[openCount] = lineCount;
                    openCount++;
                    delimiter += c;
                }
            }
        }
    }
    // cout << delimiter << endl;

    // for(int i=0; i<lineNumberCount; ++i)
    // {
    //     cout << lineNumber[i] << endl;
    // }

    inFile.close();

    return delimiter;
}

void Check::pairMatch(string arr, int count)
{
    GenStack<char> myStack(openCount);
    bool errorEmpty = false;
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
                errorEmpty = true;
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
                errorEmpty = true;
                break;
            }
        }
    }
    if(errorEmpty != true)
    {
        if(myStack.isEmpty()) //if the stack is empty in teh end, then everything is good
            cout << "Everything is good" << endl;
        else
        {
            cout << "Missing " << delimiterLeft << " closng delimiters in the end" << endl;
            string result = "";
            for(int i=0; i<delimiterLeft; ++i)
            {
                char ch = myStack.peek();
                if(ch == '{')
                    result += "} ";
                else if(ch == '(')
                    result += ") ";
                else if(ch == '[')
                    result += "] ";
                myStack.pop();
            }
            cout << "Missing " << result << endl;
        }
    }
}

bool Check::checkHasFile()
{
    return hasFile;
}