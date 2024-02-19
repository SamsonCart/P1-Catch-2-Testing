#include <iostream>
#include <sstream>
#include "AVL.h"

using namespace std;

int main() {
    AVLTree tree;

    //read first line to determine the number of commands
    string line;
    getline(cin, line);
    int numOfCommands = stoi(line);

    // Vector of DataItems to save and iterate through later
    vector<Data> dataItems;

    for(int i = 0; i < numOfCommands; i++)
    {
        //read the first full line and declare variables
        getline(cin, line);
        istringstream in(line);
        string command, followUpData;

        //Use istringstream to parse the line
        in >> command;
        getline(in, followUpData);

        //emplace variables onto the back of the dataItems vector for later reference
        dataItems.emplace_back(command, followUpData);
    }

    // Execute actions on the tree
    tree.ReviewCommands(dataItems, numOfCommands);

    return 0;
}
