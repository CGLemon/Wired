#include <iostream>
#include <string>

#include "config.h"
#include "chip/loader.h"
#include "chip/graph.h"

int main(int argc, char **argv) {

    ParseArgs(argc, argv);

    auto fname = kVariablesMap["filename"].as<std::string>();

    Graph graph;
    Loader::Get().FromFile(fname, graph);

    return 0;
};
