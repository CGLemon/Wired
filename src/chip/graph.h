#pragma once

#include <vector>
#include <string>
#include <set>

#include "config.h"
#include "chip/marco.h"

class Graph {
public:
    using Node = Marco;
    using NetList = std::set<int>;


    void Reset(const int w, const int h);
    void PushNode(const Node node);
    void PushNetList(const NetList netlist);

private:
    int width_, height_;

    std::vector<Node> nodes_;
    std::vector<NetList> connections_;
};
