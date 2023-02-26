#include "draw.h"

#include <iostream>
#include <random>
#include <vector>
#include <execution>

#include "ci_nanovg_gl.hpp"

#include "shape.h"

using std::vector;
using std::cout;
using std::endl;

NVGcontext * Draw::vg_ = nullptr;


void Draw::set_nvgContext(NVGcontext *ctx) {
    vg_ = ctx;
    Shape::set_nvgContext(ctx);
    
}

void Draw::setup() {
    nanovg_ = std::make_shared<nvg::Context>(
        //nvg::createContextGL(nvg::NVG_ANTIALIAS | nvg::NVG_STENCIL_STROKES | nvg::NVG_DEBUG)
        nvg::createContextGL(nvg::NVG_ANTIALIAS | nvg::NVG_DEBUG)
        );

    Shape::setup(nanovg_);

    //int ret = nanovg_->createFont("sans", std::string("../example/Roboto-Regular.ttf"));
    if (nanovg_->createFont("sans", std::string("../dep/nanovg/example/Roboto-Regular.ttf")) != 0) {
        cout << "Text font could not be loaded." << endl;
        exit(0);
    }
}

void Draw::test() {
    auto& vg = *nanovg_;


    vg.beginFrame(480, 480, 1);
    vg.save();

    vg.beginPath();
    vg.circle(60, 60, 5);
    vg.fillColor(nvgRGBAf(1,0,0,1.0));
    vg.fill();
    vg.closePath();
    vg.restore();

    vg.save();
    //vg.moveTo(60, 120);
    vg.translate(80, 120);
    static float rot = 0;
    //vg.rotate(rot);
    rot += 0.1;
    vg.fontSize(25.0);
    vg.fontFace("sans");
    vg.textAlign(NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    //vg.textLetterSpacing(4.0);
    vg.fillColor(nvgRGBAf(1,1,1,1));
    vg.text(0, 0, "test");
    vg.restore();

    vg.endFrame();
}

void Draw::draw() {

    static int n = 500;
    static vector<Circle> circles;

    std::random_device rd;
    std::mt19937 mt(rd());
    //std::uniform_int_distribution<int> rand_pos(50, 350);
    std::uniform_int_distribution<int> rand_pos(195, 205);
    std::uniform_real_distribution<float> rand_col(0, 1);

    if (circles.size() == 0) {
        for (int i=0; i<n; i++) {
            int x = rand_pos(mt);
            int y = rand_pos(mt);
            float r = rand_col(mt);
            float g = rand_col(mt);
            float b = rand_col(mt);
            int rad = 3;
            circles.push_back(Circle(x, y, rad, Color(r,g,b)));
        }  

    }

    if (1) {
        for (auto &c : circles) {
            // std::uniform_int_distribution<int> delta(-1, 1);
            // int dx = delta(mt);
            // int dy = delta(mt);
            std::uniform_real_distribution<float> delta(0, 1);
            float dx = (delta(mt)-0.5)*0.50;
            float dy = (delta(mt)-0.5)*0.50;
            auto [x,y] = c.position();
            c.set_position(x+dx, y+dy);
        }
    } else {
        std::for_each(
            std::execution::par,
            circles.begin(),
            circles.end(),
            [&](auto &&item) {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<int> delta(-1, 1);
                int dx = delta(mt);
                int dy = delta(mt);
                auto [x,y] = item.position();
                item.set_position(x+dx, y+dy);
            }
        );
    }

    for (auto c : circles) {
        //c.print();
        c.render();
    }
}
