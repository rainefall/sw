#pragma once
#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

#include "sw.h"

namespace SouthwestEngine {
    class Shader;

    class Drawable2D {
    protected:
        Drawable2D() { /* you can't instance this class */ };
    public:
        Shader* Shader;
        virtual void Draw() { /* you cannot call this method */ };
    };
}

#endif