#include <iostream>
#include <string>

#include "config.h"
#include "graph.h"

int main(int argc, char **argv) {

    ParseArgs(argc, argv);

    auto fname = kVariablesMap["filename"].as<std::string>();

    Graph graph;

    return 0;
};
