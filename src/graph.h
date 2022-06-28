#pragma once

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

#include "config.h"

class NetList;

struct Node {
    Node() = default;

    size_t identity;

    float x, y, width, height;

    bool Intersection(Node *a);

    // One node may connect with multiple netlists.
    std::vector<NetList*> net_lists;
};

struct NetList {
    NetList() = default;

    float ComputeHpwl();

    size_t identity;

    // HPWL value
    float hpwl;

    // All nodes contained in netlist.
    std::vector<Node*> nodes;
};

class Graph {
public:
    Graph() = default;

    void AllocateNodeBuffer(size_t n);

    void SetNode(size_t id, float x, float y, float width, float height);

    void BuildNetList(size_t id, std::initializer_list<size_t> list);

    float ComputeHpwl(bool recompute);

    float GetHPWL() const;

    // Move a node and recompute HPWL.
    void MoveNode(int id, float x, float y);

    // Swap two nodes and recompute HPWL.
    void SwapTwoNodes(int id1, int id2);

private:
    float all_hpwl_;

    std::vector<std::unique_ptr<Node>> node_buffer_;

    std::vector<std::unique_ptr<NetList>> net_lists_;
};
