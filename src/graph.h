#pragma once

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

#include "config.h"

class NetList;

struct Node {
    Node() = default;

    int identity;

    float x, y, width, height;

    bool Intersections(Node *a);

    // One node may connect with multiple netlists.
    std::vector<NetList*> net_lists;
};

struct NetList {
    NetList() = default;

    float ComputeHpwl();

    int identity;

    // HPWL value
    float hpwl;

    // All nodes contained in netlist.
    std::vector<Node*> nodes;
};

class Graph {
public:
    Graph() = default;

    void AllocateNodeBuffer(int n);
    void SetWH(int w, int h);

    void SetNode(int id, float x, float y, float width, float height);

    void InsertNetList(int id, std::initializer_list<int> list);
    void InsertNetList(int id, std::vector<int> &list);

    float ComputeHpwl(bool recompute);

    // Move a node and recompute HPWL.
    void MoveNode(int id, float x, float y);

    // Swap two nodes and recompute HPWL.
    void SwapTwoNodes(int id1, int id2);

    // Get current HPWL value.
    float GetHPWL() const { return all_hpwl_; }

    // Get graph width.
    float GetWidth() const { return width_; }

    // Get graph height.
    float GetHeight() const { return height_; }

private:
    float all_hpwl_, width_, height_;

    std::vector<std::unique_ptr<Node>> node_buffer_;

    std::vector<std::unique_ptr<NetList>> net_lists_;
};
