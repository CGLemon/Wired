#include <sstream>

#include "chip/graph.h"

void Graph::PushNode(const Graph::Node node) {
    nodes_.emplace_back(node);
}

void Graph::PushNetList(const Graph::NetList netlist) {
    connections_.emplace_back(netlist);
}

void Graph::Reset(const int w, const int h) {
    width_ = w;
    height_ = h;

    nodes_.clear();
    connections_.clear();
}
