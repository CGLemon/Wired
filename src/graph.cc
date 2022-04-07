#include <sstream>
#include <utility>

#include "graph.h"

float NetList::ComputeHPWL() {
    const auto size = nodes.size();

    if (size <= 1) {
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

void Graph::AllocateNodes(size_t n) {
    nodes_.resize(n);
    nodes_.shrink_to_fit();

    for (auto i = size_t{0}; i < n; ++i) {
        nodes_[i]->identity = i;
    }
}

void Graph::BuildNetList(std::initializer_list<size_t> list) {
    net_lists_.emplace_back(std::make_unique<NetList>());
    NetList *list_ptr = net_lists_.back().get();

    for (const size_t val : list) {
        Node *node_ptr = nodes_[val].get();

        list_ptr->nodes.emplace_back(node_ptr);
        node_ptr->net_lists.emplace_back(list_ptr);
    }
}

float Graph::ComputeHPWL(bool recompute = false) {
    hpwl_ = 0.f;

    for (auto &it : net_lists_) {
        if (recompute) {
            hpwl_ += it->ComputeHPWL();
        } else {
            hpwl_ += it->hpwl;
        }
    }
    return hpwl_;
}

float Graph::GetHPWL() const {
    return hpwl_;
}
