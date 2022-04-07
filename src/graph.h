#pragma once

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

#include "config.h"

class NetList;

class Node {
public:
    Node() = default;

    size_t identity;

    float x, y, width, height;

    std::vector<NetList*> net_lists;
};


class NetList {
public:
    NetList() = default;

    float ComputeHPWL();

    size_t identity;

    float hpwl;

    std::vector<Node*> nodes;
};

class Graph {
public:
    Graph() = default;

    void AllocateNodes(size_t n);

    void BuildNetList(std::initializer_list<size_t> list);

    float ComputeHPWL(bool recompute);

    float GetHPWL() const;

private:
    float hpwl_;

    std::vector<std::unique_ptr<Node>> nodes_;

    std::vector<std::unique_ptr<NetList>> net_lists_;
};
