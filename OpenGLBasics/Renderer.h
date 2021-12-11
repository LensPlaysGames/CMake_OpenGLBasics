#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <map>
#include <set>

#include "Camera.h"
#include "Object.h"
#include "Scene.h"

class Renderer {
public:
    void DrawScene(Scene scene);
};

#endif