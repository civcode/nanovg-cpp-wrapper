#pragma once

#include "ci_nanovg.hpp"

#include <GLFW/glfw3.h>

namespace nvg {

class ContextGL : public Context {
public:
  ContextGL(NVGcontext *ptr, Deleter deleter) : Context(ptr, deleter) {}

  Image createImageFromHandle(GLuint textureId, int w, int h, int imageFlags);
};

ContextGL createContextGL(bool antiAlias = true, bool stencilStrokes = false);

}
