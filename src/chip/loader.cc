#include <iostream>
#include <fstream>
#include <vector>

#include "chip/loader.h"

Loader &Loader::Get() {
    static Loader l;
    return l;
}

void Loader::FromFile(std::string filename, Graph &graph) {
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Couldn't open the file: " << filename << '.' << std::endl;
        return;
    }

    Parse(file, graph);

    file.close();
}

void Loader::Parse(std::istream &in, Graph &graph) {
    std::string buf;

    // first line
    // 1. the number of cells to be placed.
    // 2. the number of connections between the cells.
    // 3. the number of rows ny upon which the circuit should be placed.
    // 4. the number of columns nx upon which the circuit should be placed.
    int c = 0;
    int l = 0;
    int w = 0;
    int h = 0;
    if (std::getline(in, buf)) {
        auto ss = std::istringstream{buf};
        ss >> c >> l >> w >> h;
        graph.Reset(w, h);
    }

    for (int i = 0; i < c; ++i) {
        graph.PushNode(Graph::Node{}); // allocate enuogh nodes
    }

    while (std::getline(in, buf)) {
        auto ss = std::istringstream{buf};

        int t;
        auto netlist = Graph::NetList{};
        ss >> t; // eat first number

        while (ss >> t) {
            netlist.insert(t);
        }

        graph.PushNetList(netlist);
    }
}
