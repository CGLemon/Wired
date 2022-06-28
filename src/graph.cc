#include <sstream>
#include <utility>

#include "graph.h"

bool Node::Intersection(Node *a) {
    float half_w = width/2.f, half_h = height/2.f;

    float vertex0[2] = {x + half_w, y + half_h};
    float vertex1[2] = {x + half_w, y - half_h};
    float vertex2[2] = {x - half_w, y - half_h};
    float vertex3[2] = {x - half_w, y + half_h};


/*
 *
 *    3-----------0
 *    |           |
 *    |           |
 *    |   (x,y)   |
 *    |           |
 *    |           |
 *    2-----------1
 *
 */



    return false;
}

float NetList::ComputeHpwl() {
    const auto size = nodes.size();

    if (size <= 1) {
        // only one (or none) node, can not compute the HPWL
        hpwl = 0.f;
    } else {
        Node* ptr = nodes.front();

        float max_x = ptr->x;
        float min_x = ptr->x;
        float max_y = ptr->y;
        float min_y = ptr->y;

        for (auto i = size_t{1}; i < size; ++i) {
            Node* curr_ptr = nodes[i];

            max_x = std::max(max_x, curr_ptr->x);
            min_x = std::min(min_x, curr_ptr->x);
            max_y = std::max(max_y, curr_ptr->y);
            min_y = std::min(min_y, curr_ptr->y);
        }

        hpwl = (max_x - min_x) + (max_y - min_y);
    }

    return hpwl;
}

void Graph::AllocateNodeBuffer(size_t n) {
    // Allocate enough nodes.
    node_buffer_.resize(n);
    node_buffer_.shrink_to_fit();

    // Clear all status.
    for (auto i = size_t{0}; i < n; ++i) {
        node_buffer_[i]->identity = i;
        node_buffer_[i]->net_lists.clear();
    }
    all_hpwl_ = 0;
}

void Graph::SetNode(size_t id, float x, float y, float width, float height) {
    Node *node_ptr = node_buffer_[id].get();

    node_ptr->x = x;
    node_ptr->y = y;
    node_ptr->width = width;
    node_ptr->height = height;
    node_ptr->net_lists.clear();
}

void Graph::BuildNetList(size_t id, std::initializer_list<size_t> list) {
    net_lists_.emplace_back(std::make_unique<NetList>());

    NetList *list_ptr = net_lists_.back().get();

    // init it
    list_ptr->hpwl = 0.f;
    list_ptr->identity = id;

    for (const size_t val : list) {
        Node *node_ptr = node_buffer_[val].get();

        // link netlist to node
        list_ptr->nodes.emplace_back(node_ptr);

        // link node to netlist
        node_ptr->net_lists.emplace_back(list_ptr);
    }
}

float Graph::ComputeHpwl(bool recompute = false) {
    all_hpwl_ = 0.f;

    for (auto &it : net_lists_) {
        if (recompute) {
            all_hpwl_ += it->ComputeHpwl();
        } else {
            all_hpwl_ += it->hpwl;
        }
    }
    return all_hpwl_;
}

float Graph::GetHPWL() const {
    return all_hpwl_;
}

void Graph::MoveNode(int id, float x, float y) {
    Node *node_ptr = node_buffer_[id].get();

    node_ptr->x = x;
    node_ptr->y = y;

    float hpwl_diff = 0.f;

    // Move a node then recomputing all netlist HPWL
    // which contains the node. 
    for (auto net_list : node_ptr->net_lists) {
        float old_hpwl = net_list->hpwl;
        float new_hpwl = net_list->ComputeHpwl();

        // Now hpwl_diff HPWL difference.
        all_hpwl_ = (new_hpwl-old_hpwl);
    }

    all_hpwl_ += hpwl_diff;
}

void Graph::SwapTwoNodes(int id1, int id2) {
    Node *node_ptr1 = node_buffer_[id1].get();
    Node *node_ptr2 = node_buffer_[id2].get();

    const int x = node_ptr1->x;
    const int y = node_ptr1->y;

    // Move node 1.
    MoveNode(id1, node_ptr2->x, node_ptr2->y);

    // Move node 2.
    MoveNode(id2, x, y);
}
