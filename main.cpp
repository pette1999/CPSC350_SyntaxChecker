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
    c.pairMatch(c.readFile(), c.openCount);
}