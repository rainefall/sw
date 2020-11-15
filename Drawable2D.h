#pragma once
#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

#include "sw.h"

namespace SouthwestEngine {
    class Shader;

    class Drawable2D {
    protected:
        bool __disposed;
        Drawable2D() { /* you can't instance this class */ };
    public:
        Shader* Shader;
        virtual void Draw() { /* you cannot call this method */ };

		// mark a sprite to be disposed
        virtual void Dispose() { /* you cannot call this method */ };
		// check if this sprite has been disposed
        virtual bool Disposed() { return true; /* you cannot call this method */ };
    };
}

#endif