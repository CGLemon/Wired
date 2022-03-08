#pragma once

#include <sstream>
#include <string>

#include "chip/graph.h"

class Loader {
public:
    static Loader &Get();

    void FromFile(std::string filename, Graph &graph);

private:
    void Parse(std::istream &in, Graph &graph);

};
