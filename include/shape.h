#ifndef SHAPES_H
#define SHAPES_H

#include <utility>


#include "color.h"
#include "nanovg.h"
#include "ci_nanovg.hpp"

using std::pair;

class Shape {
public:
    // struct Color {
    //     float r, g, b;
    //     float a;
    // };

    Shape(int x, int y, Color c);

    //pair<int, int> position() const;
    pair<float, float> position() const;
    //Color& color()const;

    static void setup(std::shared_ptr<nvg::Context> pnanovg_);

    void set_position(int x, int y);
    void set_position(float x, float y);

    virtual void render() {};
    virtual void print();

    static void set_nvgContext(NVGcontext *ctx);

//private:
protected:
    // int x_;
    // int y_;
    float x_;
    float y_;
    Color c_;
    static NVGcontext *vg_;
    static std::shared_ptr<nvg::Context> nanovg_;
    
};

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int w, int h, Color c);

    pair<int, int> size() const;
    void set_size(int w, int h);
    void render();
    void print();

private:
    int w_;
    int h_;
};

class Circle : public Shape {
public:
    Circle(int x, int y, int r, Color c);

    int radius() const;
    void set_radius(int r);
    void render();
    void print();

private:
    //int r_;
    float r_;
};

#endif // SHAPES_H
