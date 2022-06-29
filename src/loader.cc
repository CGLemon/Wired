#include "loader.h"

#include <fstream>
#include <iostream>

Loader &Loader::Get() {
    static Loader l;
    return l;
}

Graph Loader::SimpleFormat(std::string filename) const {
    // The first line contains 4 values:
    //
    // The number of cells to be placed.
    // The number of connections between the cells.
    // The number of rows ny upon which the circuit should be placed.
    // The number of columns nx upon which the circuit should be placed.

    Graph g;
    int num_cells, num_lists, height, width;


    std::ifstream file(filename);

    if (!file.is_open()) {
        return g;
    }

    file >> num_cells >> num_lists >> height >> width;

    g.SetWH(width, height);
    g.AllocateNodeBuffer(num_cells);

    int x = 0, y = 0;

    for (int i = 0; i < num_cells; ++i) {
        g.SetNode(i, (float)x, (float)y, 0.995f, 0.995f);

        x += 1;
        if (x >= width) {
            x = 0;
            y += 1;
        }
    }

    for (int i = 0; i < num_lists; ++i) {
        // Each line is one netlist.
        //
        // First value is the number of cell.
        // Others are cell's id.
        auto list = std::vector<int>{};
        file >> num_cells;

        for (int id, j = 0; j < num_cells; ++j) {
            file >> id;
            list.emplace_back(id);
        }
        g.InsertNetList(i, list);
    }
    
    file.close();

    return g;
}
