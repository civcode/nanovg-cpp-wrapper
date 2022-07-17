#ifndef DRAW_H_
#define DRAW_H_

#include "nanovg.h"
#include "ci_nanovg.hpp"

class Draw {
public:
    Draw(){};

    static void set_nvgContext(NVGcontext *ctx);

    void setup();

    void test();

    //static void init_shapes();

    static void draw();

private:
    static NVGcontext *vg_;
    std::shared_ptr<nvg::Context> nanovg_;
};

#endif // DRAW_H_
