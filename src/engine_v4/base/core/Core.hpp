//
// Created by loghin on 25/02/23.
//

#ifndef __C_ENG_CORE_HPP__
#define __C_ENG_CORE_HPP__

namespace engine {

    struct Point {
        int x;
        int y;
    };


    struct PointF {
        float x;
        float y;
    };


    struct Size2D {
        int width;
        int height;
    };


    struct Size2DF {
        float width;
        float size;
    };


    struct Size3D {
        int width;
        int height;
        int depth;
    };


    struct Size3DF {
        float width;
        float size;
        float depth;
    };


    struct Rect2D {
        Point   position;
        Size2D  size;
    };


    struct Rect2DF {
        PointF  position;
        Size2DF size;
    };


    struct Rect3D {
        Point   position;
        Size3D  size;
    };


    struct Rect3DF {
        PointF  position;
        Size3DF size;
    };

}

#endif //__C_ENG_CORE_HPP__
