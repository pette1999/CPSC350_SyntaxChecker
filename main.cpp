#include <iostream>
#include "Check.h"

using namespace std;

int main(int argc, char** argv)
{
    string fileName = "";

    if (argc > 1)
    {
        fileName = argv[1];
    }

    Check c(fileName);
    c.pairMatch(c.readFile(fileName), c.openCount);

    while(true)
    {
    	string input = "";
    	cout << "Do you want to analyze another file? Y/N" << endl;
    	cin >> input;

    	if(input == "Y" || input == "y")
    	{
    		cout << "Please enter a filename: ";
    		cin >> input;
    		Check c(input);
    		if (c.checkHasFile())
    		{
    			c.pairMatch(c.readFile(input), c.openCount);
    		}
    		else
    		{
    			continue;
    		}
    	}
    	else
    	{
    		cout << "Thank you and Goodbye" << endl;
    		break;
    	}
    }
}