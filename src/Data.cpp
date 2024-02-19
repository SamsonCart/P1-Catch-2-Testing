#include "Data.h"

Data::Data(const string& cmd, const string& followUp) : command(cmd), followUpData(followUp) {}

string Data::getCommand() const {
    return command;
}

string Data::getFollowUpData() const {
    return followUpData;
}
