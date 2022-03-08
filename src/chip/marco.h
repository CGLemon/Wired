#pragma once

class Marco {
public:
    Marco() = default;

    void SetIndex(int val);
    int GetIndex() const;

    void SetPoint(int x, int y);
    void SetSize(int w, int h);

    void SetX(int val);
    void SetY(int val);
    void SetWidth(int val);
    void SetHeight(int val);

    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    int index_;

    int x_, y_;

    int width_, height_;
};
