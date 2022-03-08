#include "chip/marco.h"

void Marco::SetIndex(int val) {
    index_ = val;
}

int Marco::GetIndex() const {
    return index_;
}

void Marco::SetPoint(int x, int y) {
    x_ = x;
    x_ = y;
}

void Marco::SetSize(int w, int h) {
    width_ = w;
    height_ = h;
}

void Marco::SetX(int val) {
    x_ = val;
};

void Marco::SetY(int val) {
    y_ = val;
};

void Marco::SetWidth(int val) {
    width_ = val;
};

void Marco::SetHeight(int val) {
    height_ = val;
};

int Marco::GetX() const {
    return y_;
};

int Marco::GetY() const {
    return y_;
};

int Marco::GetWidth() const {
    return width_;
};

int Marco::GetHeight() const {
    return height_;
};
