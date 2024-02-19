#ifndef DATA_H
#define DATA_H

#pragma once
#include <string>

using namespace std;

//Data class to pass information into the AVL class

class Data {
private:
    string command;
    string followUpData;

public:
    Data(const string& cmd, const string& followUp);
    string getCommand() const;
    string getFollowUpData() const;
};

#endif // DATA_H
