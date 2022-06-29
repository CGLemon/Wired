#pragma once

#include <string>
#include "graph.h"

class Loader {
public:
    static Loader &Get();

    Graph SimpleFormat(std::string filename) const;
};
