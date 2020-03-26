#include <iostream>
#include "Check.h"

using namespace std;

Check::Check()
{
    fileName = "test.txt";
    openCount = 0;
    line = "";

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
    line = "";

    ifstream inFile(fileName); //read the file
    line = "";

    if (!inFile)
    {
        cout << fileName << " does not exist. " << endl;
        exit(1);
    }
}

char* Check::readFile()
{
    //get the number of open brackets
    while(getline(inFile, line))
    {
        for(char c : line)
        {
            if(c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                openCount++;
            }
        }
    }

    inFile.close();

    openDelimiter = new char[openCount];
    int count = 0;

    inFile.open(fileName);

    while (getline(inFile, line))
    {
        for (char c : line)
        {
            if (c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']')
            {
                openDelimiter[count] = c;
                count++;
            }
        }
    }

    inFile.close();
    return openDelimiter;
}

void Check::pairMatch(char* arr, int count)
{
    GenStack<char> myStack(openCount);
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
                cout << "There is a problem" << endl;
                break;
            }

            if(arr[i] == '}' && myStack.peek() == '{')
            {
                myStack.pop();
                continue;
            }
            else if (arr[i] == ')' && myStack.peek() == '(')
            {
                myStack.pop();
                continue;
            }
            else if (arr[i] == ']' && myStack.peek() == '[')
            {
                myStack.pop();
                continue;
            }
            else
            {
                cout << "There is an unmathch here" << endl;
                break;
            }
        }
        if(myStack.isEmpty())
            cout << "Everything is good" << endl;
        else
            cout << "Some symbols never matched" << endl;
    }


}